#pragma once

#include <Arduino.h>
#include <EncoderTool.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>


#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "../lib/TeensyStep4-main/src/teensystep4.h"
#include <Adafruit_FRAM_I2C.h>


#include "types.h" 


// MCU Config
#define __BAUD_RATE 9600


// Analog Config
#define ADC_RESOLUTION 12
#define ADC_MAX_VALUE  ((1 << ADC_RESOLUTION) - 1)
#define PWM_MAX_VALUE  ADC_MAX_VALUE


// Potentiometer Config
#define __POTENTIOMETER_PIN 14


// Display Config
#define __DISPLAY_WIDTH  240 // adafruit.com/product/4383
#define __DISPLAY_HEIGHT 135 // adafruit.com/product/4383


// Display Pins
#define __TFT_ChipSelect  10
#define __TFT_DataCommand 9
#define __TFT_Reset       8
#define __TFT_Light       23


// Motor Driver Config
#define __STEP      3
#define __DIRECTION 4
#define __ENABLE    6
#define __MODE0     28
#define __MODE1     29
#define __VREF      36 
#define __STL_MODE  22
#define __TRQ_CNT   15
#define __STL_REP   24


// Encoder Config 
#define __ENCODER_CHANNEL_A      0
#define __ENCODER_CHANNEL_B      1
#define __ENCODER_COUNTS_PER_REV 4000


// Motor Config
#define __MOTOR_STEPS_PER_REV 200               // 1.8* per step in max resolution, should probably rename this to be more clear that this is total steps in FULL resolution 
#define __STEP_RESOLUTION     THIRTYSECOND
#define __GEAR_RATIO          1.0f

#define __CALIBRATION_RPM 50
#define __CALIBRATION_SPS lround(__CALIBRATION_RPM * (__STEP_RESOLUTION * __MOTOR_STEPS_PER_REV) / 60)
#define __RPM             750
#define __SPS             lround(__RPM * (__STEP_RESOLUTION * __MOTOR_STEPS_PER_REV) / 60)


// FRAM Config
#define __FRAM_ENDPOINT_LEFT_ADDR  0x00
#define __FRAM_ENDPOINT_RIGHT_ADDR 0x04
#define __FRAM_MAGIC_ADDR          0x10