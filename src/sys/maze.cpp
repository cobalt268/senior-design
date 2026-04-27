#include "maze.h"
#include "distance.h"
#include "motor.h"
#include <string.h>
#include <Arduino.h>

// ---- grid state -------------------------------------------------------
static CellState cells[MAZE_SIZE][MAZE_SIZE];   // [row][col], row 0 = north edge
static uint8_t   mouse_col, mouse_row;
static Direction heading;

// Row / column delta for each direction (index = Direction enum value)
static const int8_t dr[4] = { -1,  0,  1,  0 };  // N, E, S, W
static const int8_t dc[4] = {  0,  1,  0, -1 };

// ---- flood-fill -------------------------------------------------------
// BFS from all four center goal cells simultaneously; assigns distance values
// respecting known walls. All goal cells start at distance 0.
static void flood(void)
{
    // Reset all distances
    for (int r = 0; r < MAZE_SIZE; r++)
        for (int c = 0; c < MAZE_SIZE; c++)
            cells[r][c].distance = 255;

    // BFS queue — uint16_t indices so tail never overflows at 256 entries
    uint8_t  q_col[MAZE_SIZE * MAZE_SIZE];
    uint8_t  q_row[MAZE_SIZE * MAZE_SIZE];
    uint16_t head = 0, tail = 0;

    // Seed all four center cells at distance 0 (rule 3.3: 2x2 goal zone)
    for (int r = GOAL_MIN; r <= GOAL_MAX; r++)
    {
        for (int c = GOAL_MIN; c <= GOAL_MAX; c++)
        {
            cells[r][c].distance = 0;
            q_row[tail] = (uint8_t)r;
            q_col[tail] = (uint8_t)c;
            tail++;
        }
    }

    while (head != tail)
    {
        uint8_t c = q_col[head];
        uint8_t r = q_row[head];
        head++;

        uint8_t next_dist = cells[r][c].distance + 1;

        for (int d = 0; d < 4; d++)
        {
            // Do not cross known walls
            if (cells[r][c].walls & (1 << d)) continue;

            int8_t nr = (int8_t)r + dr[d];
            int8_t nc = (int8_t)c + dc[d];

            // Stay in bounds
            if (nr < 0 || nr >= MAZE_SIZE || nc < 0 || nc >= MAZE_SIZE) continue;

            // Only enqueue if we found a shorter path
            if (cells[nr][nc].distance > next_dist)
            {
                cells[nr][nc].distance = next_dist;
                q_col[tail] = (uint8_t)nc;
                q_row[tail] = (uint8_t)nr;
                tail++;
            }
        }
    }
}

// ---- wall sensing -----------------------------------------------------
// Reads the three sensors (front, left side, right side) relative to the
// current heading and marks any detected walls on the grid.
// Walls are mirrored to the adjacent cell's opposite face.
// Returns true if any previously unknown wall was found.
static bool sense_walls(void)
{
    bool new_wall = false;
    uint8_t r = mouse_row, c = mouse_col;

    // Map sensor positions to absolute directions given current heading
    int fwd   = (int)heading;
    int left  = ((int)heading + 3) % 4;
    int right = ((int)heading + 1) % 4;

    bool wall_fwd   = (forwardDistance()     < WALL_THRESHOLD)
                   || (forwardLeftDistance() < WALL_THRESHOLD);
    bool wall_left  = (leftDistance()        < WALL_THRESHOLD);
    bool wall_right = (rightDistance()       < WALL_THRESHOLD);

    // Record a wall on this cell (and mirror to neighbor) if not already known
    auto record = [&](int dir) {
        if (!(cells[r][c].walls & (1 << dir)))
        {
            cells[r][c].walls |= (uint8_t)(1 << dir);
            new_wall = true;

            int8_t nr = (int8_t)r + dr[dir];
            int8_t nc = (int8_t)c + dc[dir];
            if (nr >= 0 && nr < MAZE_SIZE && nc >= 0 && nc < MAZE_SIZE)
                cells[nr][nc].walls |= (uint8_t)(1 << ((dir + 2) % 4));
        }
    };

    if (wall_fwd)   record(fwd);
    if (wall_left)  record(left);
    if (wall_right) record(right);

    return new_wall;
}

// ---- rotation helper --------------------------------------------------
// Rotates the mouse to face the given absolute direction and updates heading.
static void face_direction(Direction target)
{
    int diff = ((int)target - (int)heading + 4) % 4;
    if      (diff == 1) rotate_right();
    else if (diff == 2) rotate_180();
    else if (diff == 3) rotate_left();
    // diff == 0: already facing the right way
    heading = target;
}

// ---- move forward one cell --------------------------------------------
static void step_forward(void)
{
    proceed_forward(GRID_SPACING);
    mouse_row = (uint8_t)((int8_t)mouse_row + dr[(int)heading]);
    mouse_col = (uint8_t)((int8_t)mouse_col + dc[(int)heading]);
}

// ---- goal check -------------------------------------------------------
static bool at_goal(void)
{
    return (mouse_col >= GOAL_MIN && mouse_col <= GOAL_MAX &&
            mouse_row >= GOAL_MIN && mouse_row <= GOAL_MAX);
}

// ---- public API -------------------------------------------------------

void maze_init(void)
{
    memset(cells, 0, sizeof(cells));

    // Set all distances to unreachable until flood runs
    for (int r = 0; r < MAZE_SIZE; r++)
        for (int c = 0; c < MAZE_SIZE; c++)
            cells[r][c].distance = 255;

    // Outer border walls — the physical maze boundary (rule 3.1)
    for (int i = 0; i < MAZE_SIZE; i++)
    {
        cells[0][i].walls             |= WALL_N;
        cells[MAZE_SIZE - 1][i].walls  |= WALL_S;
        cells[i][0].walls             |= WALL_W;
        cells[i][MAZE_SIZE - 1].walls  |= WALL_E;
    }

    // Mouse starts at top-left corner (0, 0) facing EAST (rule 3.3)
    mouse_col = 0;
    mouse_row = 0;
    heading   = EAST;

    // Initial flood with only border walls known
    flood();

    Serial.printf("[maze] init: goal zone=(%d-%d, %d-%d) start=(0,0) heading=EAST\n",
                  GOAL_MIN, GOAL_MAX, GOAL_MIN, GOAL_MAX);
}

bool maze_step(void)
{
    // Sense walls at current cell; re-flood if new wall discovered
    if (sense_walls())
    {
        flood();
        Serial.printf("[maze] reflood at (%d,%d)\n", mouse_col, mouse_row);
    }

    // Goal reached — any cell in the 2x2 center zone counts (rule 3.3)
    if (at_goal())
    {
        Serial.println("[maze] GOAL REACHED");
        return true;
    }

    // Find the open neighbor with the lowest flood-fill distance
    uint8_t best_dist = 255;
    Direction best_dir = NORTH;
    bool found = false;

    for (int d = 0; d < 4; d++)
    {
        if (cells[mouse_row][mouse_col].walls & (1 << d)) continue;

        int8_t nr = (int8_t)mouse_row + dr[d];
        int8_t nc = (int8_t)mouse_col + dc[d];
        if (nr < 0 || nr >= MAZE_SIZE || nc < 0 || nc >= MAZE_SIZE) continue;

        if (cells[nr][nc].distance < best_dist)
        {
            best_dist = cells[nr][nc].distance;
            best_dir  = (Direction)d;
            found     = true;
        }
    }

    if (!found)
    {
        // Surrounded by walls — should never happen in a valid maze
        Serial.println("[maze] ERROR: no open neighbor");
        return false;
    }

    Serial.printf("[maze] (%d,%d) dist=%d -> dir=%d\n",
                  mouse_col, mouse_row,
                  cells[mouse_row][mouse_col].distance, (int)best_dir);

    face_direction(best_dir);
    step_forward();
    return false;
}
