#ifndef MAZE_H
#define MAZE_H

#include <stdint.h>
#include <stdbool.h>

#define MAZE_SIZE       16    // official competition maze is 16x16 cells
#define GRID_SPACING    180   // mm between cell centers (18 cm per rule 3.1)
#define WALL_THRESHOLD  160   // mm below which a wall is detected

// 2x2 goal zone at the center of the maze (rule 3.3)
// For a 16x16 grid these are rows/cols 7 and 8 (0-indexed)
#define GOAL_MIN  (MAZE_SIZE / 2 - 1)   // 7
#define GOAL_MAX  (MAZE_SIZE / 2)        // 8

// Cardinal directions — also used as heading value
typedef enum { NORTH = 0, EAST = 1, SOUTH = 2, WEST = 3 } Direction;

// Wall bitmask bits (1 << direction)
#define WALL_N  (1 << NORTH)   // 0x01
#define WALL_E  (1 << EAST)    // 0x02
#define WALL_S  (1 << SOUTH)   // 0x04
#define WALL_W  (1 << WEST)    // 0x08

typedef struct {
    uint8_t  walls;     // bitmask of known walls (WALL_N | WALL_E | WALL_S | WALL_W)
    uint8_t  distance;  // flood-fill distance to goal zone; 255 = unreachable
} CellState;

// Initialize the maze solver. Mouse starts at cell (0, 0) facing EAST.
// The goal is always the 2x2 center zone per competition rules.
void maze_init(void);

// Execute one maze step. Returns true when the goal zone is reached.
bool maze_step(void);

#endif
