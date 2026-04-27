#include <Arduino.h>
#include "sys/distance.h"
#include "sys/motor.h"
#include "sys/maze.h"

// Goal is always the 2x2 center zone of the 16x16 maze (rule 3.3).
// Start is cell (0,0), mouse must be placed facing EAST.

static bool maze_solved = false;

void setup()
{
    Serial.begin(115200);
    setup_distance();
    setup_motor();

    Serial.println("Place mouse in corner cell (0,0) facing EAST. Starting in 3 seconds...");
    vTaskDelay(3000 / portTICK_PERIOD_MS);

    maze_init();
}

void loop()
{
    if (!maze_solved)
        maze_solved = maze_step();
}


// --- motor test mode (uncomment to use instead of maze loop) ---
// Drives forward one grid cell, pauses, then repeats.
// Watch encoder counts on Serial to verify straight-line travel.
// void setup()
// {
//     Serial.begin(115200);
//     setup_motor();
//     setup_distance();  // required — proceed_forward() uses IR sensors for aversion
//     Serial.println("Motor test: driving forward one cell every 2 seconds.");
//     vTaskDelay(3000 / portTICK_PERIOD_MS);
// }

// void loop()
// {
//     int32_t before = get_right_encoder_count();
//     proceed_forward(GRID_SPACING);
//     int32_t after = get_right_encoder_count();
//     Serial.printf("counts R: %ld  L: %ld  delta: %ld\n",
//         get_right_encoder_count(), get_left_encoder_count(), after - before);
//     vTaskDelay(2000 / portTICK_PERIOD_MS);
// }

//--- sensor debug mode (uncomment to use instead of maze loop) ---
// void setup()
// {
//     Serial.begin(115200);
//     setup_distance();
//     vTaskDelay(3000 / portTICK_PERIOD_MS);
//     Serial.println("Sensor values in mm.");
//     Serial.println("F_R\tF_L\tL\tR");
// }

// void loop()
// {
//     Serial.printf("%d\t%d\t%d\t%d\n",
//         forwardDistance(), forwardLeftDistance(),
//         leftDistance(), rightDistance());
//     delay(200);
// }
