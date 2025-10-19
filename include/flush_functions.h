#pragma once

String formatted_brake_bias         (float front_brake_bias);
String formatted_brake_bar_position (float brake_bar_position);


DISPLAY_COORDINATES compute_centered_coordinates(
    Adafruit_ST7789* display,
    String           text
);

void flush_string_to_coords(
    Adafruit_ST7789* display,
    int16_t          x,
    int16_t          y,
    String           input_string
);

void flush_string_to_auto_centered_coords(
    Adafruit_ST7789* display,
    String           input_string
);