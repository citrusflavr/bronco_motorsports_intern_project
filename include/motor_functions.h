#pragma once

#include <Arduino.h>
#include <EncoderTool.h>


long DRV8434ARGER_set_steps_per_revolution(
    const int   MODE0,
    const int   MODE1,
    const int   total_steps_per_full_rev,
    const float resolution 
);


float get_motor_position_percentage(
    float motor_most_left_count,
    float motor_most_right_count,
    float motor_current_pos_count
);


inline void start_motor(int ENABLE_PIN)
{
    pinMode(ENABLE_PIN, OUTPUT);
}


inline float encoder_velocity(int encoder_count, float delta_time)
{
    return (float)encoder_count / delta_time;
}


inline int position_difference(int target_count_pos, int current_count_pos)
{
    return target_count_pos - current_count_pos;
}


inline void set_pwm_duty_cycle(int PWM_pin, float percentage)
{
    float PWM_duty_pct;
    int   PWM_duty_count;

    if (percentage < 0.0f)
        percentage = 0.0f;
    if (percentage > 100.0f)
        percentage = 100.0f;

    
    PWM_duty_pct   = percentage / 100.0f;
    PWM_duty_count = lroundf(PWM_duty_pct * PWM_MAX_VALUE);

    analogWrite(PWM_pin, PWM_duty_count);
}

void set_motor_driver_VREF_via_percentage          (int PWM_pin, float percentage);
void set_driver_motor_stall_sensitivity_percentage (int TRQ_CNT_PWM_pin, float percentage);