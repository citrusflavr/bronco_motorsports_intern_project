#pragma once

#include <Arduino.h>
#include <Encoder.h>
#include <stdio.h>
#include <stdint.h>


#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "../lib/TeensyStep4-main/src/teensystep4.h"
#include <Adafruit_FRAM_I2C.h>


#include "types.h" 


// MCU Config
#define __BAUD_RATE 9600


// Potentiometer Config
#define __POTENTIOMETER_PIN A0


// Display Config
#define __DISPLAY_WIDTH  240 // adafruit.com/product/4383
#define __DISPLAY_HEIGHT 135 // adafruit.com/product/4383


// Display Hardware SPI Pins
#define __TFT_ChipSelect  10
#define __TFT_DataCommand 9
#define __TFT_Reset       8


// Motor Controller Config
#define __STEP      2
#define __DIRECTION 3
#define __ENABLE    4
#define __MODE0     5
#define __MODE1     6
#define __MODE2     7


// Encoder Config AKA Logic Level Converter Config because  
// Encoder -> Differential Line Receiver -> Logic Level Shift from 5V to 3.3V -> Teensy 4.1
#define __ENCODER_CHANNEL_A      23
#define __ENCODER_CHANNEL_B      22
#define __ENCODER_COUNTS_PER_REV 4000

#define __MOTOR_STEPS_PER_REV 200               // 1.8* per step in max resolution 
#define __STEP_RESOLUTION     THIRTYSECOND

#define __GEAR_RATIO 1.0f