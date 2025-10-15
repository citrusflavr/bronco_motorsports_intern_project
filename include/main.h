#pragma once

#include <Arduino.h>
#include <stdio.h>


typedef struct display_coordinates
{
    int16_t x;
    int16_t y;
} DISPLAY_COORDINATES;


typedef struct motor_count
{
    int16_t most_count_left;
    int16_t most_count_right;
} MOTOR_COUNT_ENDPOINTS;