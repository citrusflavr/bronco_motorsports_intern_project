#include <Arduino.h>
#include <stdint.h>
#include "../.pio/libdeps/teensy41/Adafruit GFX Library/Adafruit_GFX.h"
#include "../.pio/libdeps/teensy41/Adafruit ST7735 and ST7789 Library/Adafruit_ST7789.h"
#include "../include/main.h"

String formatted_brake_bias(float front_brake_bias)
{
    char front_bb_buffer[10];
    char rear_bb_buffer [10];

    float rear_brake_bias = 100.0f - front_brake_bias;

    dtostrf(
        front_brake_bias,
        0,
        1,
        front_bb_buffer
    );

    dtostrf(
        rear_brake_bias,
        0,
        1,
        rear_bb_buffer
    );

    String formatted_bb_string = 
        String(front_bb_buffer) + "% BF / " + String(rear_bb_buffer) + "% BB";

    return formatted_bb_string;
}


String formatted_brake_bar_position(float brake_bar_position)
{
    char bar_pos_buffer[5];

    dtostrf(
        brake_bar_position,
        0,
        1,
        bar_pos_buffer
    );

    String formatted_brake_bar_position =
        String(bar_pos_buffer) + "%";

    return formatted_brake_bar_position;
}


DISPLAY_COORDINATES compute_centered_coordinates(
    Adafruit_ST7789* display,
    String           text
)
{
    int16_t x_offset;
    int16_t y_offset;
    
    uint16_t string_width;
    uint16_t string_height;

    int16_t centered_x;
    int16_t centered_y;

    DISPLAY_COORDINATES centered_coordinates;

    display->getTextBounds(
        text,
        0,
        0,
        &x_offset,
        &y_offset,
        &string_width,
        &string_height
    );

   centered_x = (display->width()  - string_width);
   centered_y = (display->height() - string_height);

   centered_coordinates.x = centered_x;
   centered_coordinates.y = centered_y;

   return centered_coordinates;
};


// Yes, these following functions sets font size to 3 without any notice to the callee.
// Yes, this is bad practice and misleading.
// No, I do not care.
void flush_string_to_coords(
    Adafruit_ST7789* display,
    int16_t          x,
    int16_t          y,
    String           input_string
)
{
    display->setTextSize (3);
    display->setTextColor(ST77XX_BLACK);
    display->setCursor   (x, y);
    display->print       (input_string);
}


void flush_string_to_auto_centered_coords(
    Adafruit_ST7789* display,
    String           input_string
)
{
    DISPLAY_COORDINATES centered_coordinates;

    display->setTextSize (3);
    display->setTextColor(ST77XX_BLACK);

    centered_coordinates = compute_centered_coordinates(display, input_string);
    display->setCursor(
        centered_coordinates.x,
        centered_coordinates.y
    );

    display->print(input_string);
}
