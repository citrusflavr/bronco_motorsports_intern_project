#include <Arduino.h>
#include "../include/main.h"


// Most Left  = 100%
// Most Right = 0%
float calculate_percentage_from_motor_count(MOTOR_COUNT_ENDPOINTS endpoints, float current_motor_count)
{
    float percentage;

    // Linear interpolation, if x_1 was most right and x_2 was most left
    percentage = 100 * ((endpoints.most_count_right - current_motor_count) / (endpoints.most_count_right - endpoints.most_count_left));

    if (percentage < 0.0f)
        percentage = 0.0f;
    if (percentage > 100.0f)
        percentage = 100.0f;

    return percentage;
}
