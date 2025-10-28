#include "../include/motor_functions.h"
#include "../include/config.h"

#include <Arduino.h>
#include "types.h"


long DRV8434ARGER_set_steps_per_revolution(
    const int   MODE0,
    const int   MODE1,
    const int   total_steps_per_full_rev,
    const float resolution 
)
{
    pinMode(MODE0,  OUTPUT);
    pinMode(MODE1,  OUTPUT);


    if (resolution == FULL)
    {
        digitalWrite(MODE0, LOW);
        digitalWrite(MODE1, LOW);

        return (long)total_steps_per_full_rev * 1.0f;
    }
    else if (resolution == HALF)
    {
        pinMode      (MODE0, INPUT);
        digitalWrite (MODE1, LOW);

        return (long)total_steps_per_full_rev * 2.0f;
    }
    else if (resolution == QUARTER)
    {
        digitalWrite(MODE0, LOW);
        digitalWrite(MODE1, HIGH);

        return (long)total_steps_per_full_rev * 4.0f;
    }
    else if (resolution == EIGHTH)
    {
        digitalWrite(MODE0, HIGH);
        digitalWrite(MODE1, HIGH);

        return (long)total_steps_per_full_rev * 8.0f;
    }
    else if (resolution == THIRTYSECOND)
    {
        digitalWrite (MODE0, LOW);
        pinMode      (MODE1, INPUT);

        return (long)total_steps_per_full_rev * 32.0f;
    }
    else
    {
        digitalWrite(MODE0, LOW);
        digitalWrite(MODE1, LOW);

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


void set_motor_driver_VREF_via_percentage(int PWM_pin, float percentage)
{
    set_pwm_duty_cycle(PWM_pin, percentage);
}


void set_driver_motor_stall_sensitivity_percentage(int TRQ_CNT_PWM_pin, float percentage) 
{
    set_pwm_duty_cycle(TRQ_CNT_PWM_pin, percentage);
}

