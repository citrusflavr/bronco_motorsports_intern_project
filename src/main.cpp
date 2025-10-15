#include <Arduino.h>
#include "../.pio/libdeps/teensy41/Adafruit GFX Library/Adafruit_GFX.h"
#include "../.pio/libdeps/teensy41/Adafruit ST7735 and ST7789 Library/Adafruit_ST7789.h"

// MCU Config
#define BAUD_RATE 9600

// Display Config
#define DISPLAY_WIDTH  240 // adafruit.com/product/4383
#define DISPLAY_HEIGHT 135 // adafruit.com/product/4383

// Hardware SPI Pins
#define TFT_ChipSelect  10
#define TFT_DataCommand 9
#define TFT_Reset       8

Adafruit_ST7789 display = Adafruit_ST7789(
  TFT_ChipSelect,
  TFT_DataCommand,
  TFT_Reset
);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(BAUD_RATE);

  display.init  (DISPLAY_HEIGHT, DISPLAY_WIDTH);
  Serial.println("Display Initialized");

  display.fillScreen(ST77XX_YELLOW);

}

void loop() 
{
  // put your main code here, to run repeatedly:
}


// TODO: 
// Software calibration of the physical bar position
// Software wire up the POTENTIOMETER to the MCU 
// Software wire up the MOTOR CONTROLLER to the MCU
// Software wire up the ENCODER to the MCU
// use TEENSYSTEP to communicate with the motoro controller from the MCU

// assume 1:1 linear
// project done
