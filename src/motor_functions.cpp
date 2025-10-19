#include "../include/motor_functions.h"

long motor_init(
    const int ENABLE,
    const int MODE0,
    const int MODE1,
    const int MODE2,
    const int total_steps_per_full_rev,
    const int resolution 
)
{
    pinMode(ENABLE, OUTPUT);
    pinMode(MODE0,  OUTPUT);
    pinMode(MODE1,  OUTPUT);
    pinMode(MODE2,  OUTPUT);

    // Start the motor
    digitalWrite(ENABLE, LOW);


    if (resolution == FULL)
    {
        digitalWrite(MODE0, LOW);
        digitalWrite(MODE1, LOW);
        digitalWrite(MODE2, LOW);

        return (long)total_steps_per_full_rev * 1.0f;
    }
    else if (resolution == HALF)
    {
        digitalWrite(MODE0, HIGH);
        digitalWrite(MODE1, LOW);
        digitalWrite(MODE2, LOW);

        return (long)total_steps_per_full_rev * 2.0f;
    }
    else if (resolution == QUARTER)
    {
        digitalWrite(MODE0, LOW);
        digitalWrite(MODE1, HIGH);
        digitalWrite(MODE2, LOW);

        return (long)total_steps_per_full_rev * 4.0f;
    }
    else if (resolution == EIGHTH)
    {
        digitalWrite(MODE0, HIGH);
        digitalWrite(MODE1, HIGH);
        digitalWrite(MODE2, LOW);

        return (long)total_steps_per_full_rev * 8.0f;
    }
    else if (resolution == THIRTYSECOND)
    {
        digitalWrite(MODE0, HIGH);
        digitalWrite(MODE1, HIGH);
        digitalWrite(MODE2, HIGH);

        return (long)total_steps_per_full_rev * 32.0f;
    }
    else
    {
        digitalWrite(MODE0, LOW);
        digitalWrite(MODE1, LOW);
        digitalWrite(MODE2, LOW);

        return (long)total_steps_per_full_rev * 1.0f;
    }
}


float get_motor_position_percentage(
    float motor_most_left_count,
    float motor_most_right_count,
    float motor_current_pos_count
)
{
    float brake_bias_bar_percent;

    if (motor_most_right_count < motor_most_left_count)
    {
        float temp = motor_most_right_count;

        motor_most_right_count = motor_most_left_count;
        motor_most_left_count  = temp;
    }

    if (motor_current_pos_count < motor_most_left_count)
        motor_current_pos_count = motor_most_left_count;
    if (motor_current_pos_count > motor_most_right_count)
        motor_current_pos_count = motor_most_right_count;


    // Linear Interpolation 
    // Most left  = 100%
    // Most right = 0%
    brake_bias_bar_percent = 100.0f * (1.0 - ((double)(motor_current_pos_count - motor_most_left_count) / (double)(motor_most_right_count - motor_most_left_count)));

    return brake_bias_bar_percent;
}