#pragma once


long potentiometer_raw_to_motor_count(
    int   raw_adc,
    int   adc_max,
    float motor_endpoint_left,
    float motor_endpoint_right
);