#include "../include/config.h"


// Motor Config and Initialization
Stepper motor(                                          // This is hot ass. This code is hot ass.
  __STEP, 
  __DIRECTION
);

Encoder encoder(
  __ENCODER_CHANNEL_A,
  __ENCODER_CHANNEL_B
);

StepControl motor_controller;


const long  STEPS_PER_REVOLUTION = motor_init(
  __ENABLE,
  __MODE0,
  __MODE1,
  __MODE2,
  __MOTOR_STEPS_PER_REV,
  __STEP_RESOLUTION 
);


// Display Initialization
Adafruit_ST7789 display = Adafruit_ST7789(
  __TFT_ChipSelect,
  __TFT_DataCommand,
  __TFT_Reset
);


// NOTE: THIS IS PLACEHOLDER. THIS IS PLACEHOLDER.
float motor_left_endpoint  = 0.0f;
float motor_right_endpoint = 0.0f;


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(__BAUD_RATE);

  // tune. assuming 1:1 gear ratio, 1/32 step resolution, 24V driver supply, 1.0 A limit
  motor.setMaxSpeed     (80000);  // ~750 RPM @ 1/32 step resolution
  motor.setAcceleration (400000);

  analogReadResolution (12);
  analogReadAveraging  (4);


  display.init   (__DISPLAY_HEIGHT, __DISPLAY_WIDTH);
  Serial.println ("Display Initialized");

  display.fillScreen(ST77XX_YELLOW);

}


void loop() 
{
  // yes, this is prone to jittering. yes, this is a POC. yes, im lazy to cache. 

  long   potentiometer_reading_count;
  long   target_steps; 
  float  motor_position_percentage;
  String brake_bias_bar_pos_string;


  potentiometer_reading_count = 0.0f;

  potentiometer_reading_count = potentiometer_raw_to_motor_count(
    analogRead(__POTENTIOMETER_PIN),
    4095,                                 // ADC Max Resolution Value at 12 Bits
    motor_left_endpoint,
    motor_right_endpoint 
  );

  target_steps = lround(
    (double) potentiometer_reading_count * 
    ((double) __MOTOR_STEPS_PER_REV * (double) __STEP_RESOLUTION * (double) __GEAR_RATIO) /
    (double) __ENCODER_COUNTS_PER_REV
  );


  motor.setTargetAbs(target_steps);

  motor_controller.move(motor);

  motor_position_percentage = get_motor_position_percentage(
    motor_left_endpoint,
    motor_right_endpoint,
    encoder.read()
  );

  brake_bias_bar_pos_string = formatted_brake_bar_position(
    motor_position_percentage
  );

  flush_string_to_auto_centered_coords(
    &display,
    brake_bias_bar_pos_string
  );
}


// TODO: 
// Software calibration of the physical bar position

// Read encoder for count values
// Encoder is really only used for calibration as we move the motor via abs. pos. oh and motor pos %. 
