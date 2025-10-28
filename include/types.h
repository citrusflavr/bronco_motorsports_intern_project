#pragma once

#include <stdint.h>

typedef struct display_coordinates
{
    int16_t x;
    int16_t y;
} DISPLAY_COORDINATES;


typedef struct motor_count
{
    float most_count_left;
    float most_count_right;
} MOTOR_COUNT_ENDPOINTS;


constexpr float FULL         = 1.0f;
constexpr float HALF         = 0.5f;
constexpr float QUARTER      = 0.25f;
constexpr float EIGHTH       = 0.125f;
constexpr float SIXTEENTH    = 0.0625f;
constexpr float THIRTYSECOND = 0.03125f;


