#pragma once


long motor_init(
    const int ENABLE,
    const int MODE0,
    const int MODE1,
    const int MODE2,
    const int total_steps_per_full_rev,
    const int resolution 
);


float get_motor_position_percentage(
    float motor_most_left_count,
    float motor_most_right_count,
    float motor_current_pos_count
);