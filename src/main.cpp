#include "../include/config.h"
#include "display_functions.h"
#include "motor_functions.h"
#include "motor_calibration.h"
#include "potentiometer.h"


// Motor Config and Initialization
TS4::Stepper motor(                                          
  __STEP, 
  __DIRECTION
);

// Random Global Declarations
EncoderTool::Encoder  encoder;
MOTOR_COUNT_ENDPOINTS motor_endpoints;
Adafruit_FRAM_I2C     fram;

long    STEPS_PER_REVOLUTION;
long    last_potentiometer_reading_count;
long    potentiometer_reading_count;
uint8_t fram_buffer       [4];
uint8_t fram_magic_buffer [2];


// Display declaration and definition because for some reason you
// can't do this in setup()
Adafruit_ST7789 display = Adafruit_ST7789(
  __TFT_ChipSelect,
  __TFT_DataCommand,
  __TFT_Reset
);


void setup() 
{
  Serial.begin(__BAUD_RATE);


  analogReadResolution (ADC_RESOLUTION);
  analogReadAveraging  (4);


  // Begin TeensyStep4
  TS4::begin();


  // Begin EncoderTool
  encoder.begin(
    __ENCODER_CHANNEL_B,
    __ENCODER_CHANNEL_B
  );


  // Begin FRAM
  fram = Adafruit_FRAM_I2C();
  if (!fram.begin())
  {
    Serial.println("I2C FRAM not found. Check connection?");
    Serial.println("System not entirely dependant on the FRAM, but still aborting because why not.");
    exit(-1);
  }


  // what the fuck am i doing?
  STEPS_PER_REVOLUTION = DRV8434ARGER_set_steps_per_revolution(
    __MODE0,
    __MODE1,
    __MOTOR_STEPS_PER_REV, // part of motor, not driver
    __STEP_RESOLUTION
  );


  // Start motor
  start_motor(__ENABLE);


  // Enable Motor Driver Stall Detection
  pinMode      (__STL_REP, INPUT_PULLUP);
  pinMode      (__STL_MODE, OUTPUT);
  digitalWrite (__STL_MODE, HIGH);
  set_driver_motor_stall_sensitivity_percentage(__TRQ_CNT, 50.0f);

  
  // Check for new FRAM device
  if (fram.read(__FRAM_MAGIC_ADDR, fram_magic_buffer, 2))
  {
    // Not reliable, but will work. Always a chance that these magic numbers exist in a
    // FRAM device that does not have its first 8 bytes from 0x00 initialized.
    if (fram_magic_buffer[0] != 0x69 && fram_magic_buffer[1] != 0x67)
    {
      Serial.println("New FRAM device detected. Initializing it now.");
      
      uint8_t temp_buffer[2] = {0x69, 0x67};
      fram.write(0x10, temp_buffer, 2);

      uint8_t zero_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
      fram.write(0x00, zero_buffer, 8);
    }
  }
  else
  {
    Serial.println("Failed to check validity of FRAM device. Critical error, aborting.");
    exit(-1);
  }


  // Initialize motor endpoint structure
  if (fram.read(__FRAM_ENDPOINT_LEFT_ADDR, fram_buffer, 4))
  {
    memcpy(
      &motor_endpoints.most_count_left,
      fram_buffer,
      4
    );
  }
  else
  {
    Serial.println("FRAM read failed for left motor endpoint. Non-critical error. Proceeding.");
    motor_endpoints.most_count_left = 0.0f;
  }

  if (fram.read(__FRAM_ENDPOINT_RIGHT_ADDR, fram_buffer, 4))
  {
    memcpy(
      &motor_endpoints.most_count_right,
      fram_buffer,
      4
    );
  }
  else
  {
    Serial.println("FRAM read failed for right motor endpoint. Non-critical error. Proceeding.");
    motor_endpoints.most_count_right = 0.0f; 
  }


  // Calibrate motor endpoints, and then write to FRAM to save.
  if (!calibrate_motor_endpoints(
    &motor,
    &encoder,
    &motor_endpoints
  ))
  {
    Serial.print("Calibration Failed. System not safe to use.");
    exit(-1);
  }
  else
  {
    memcpy(
      fram_buffer,
      &motor_endpoints.most_count_left,
      4
    );
    
    if(!fram.write(__FRAM_ENDPOINT_LEFT_ADDR, fram_buffer, 4))
    {
      Serial.println("Failed to write to FRAM most left endpoint ADDR. Non-critical error. Proceeding.");
    }

    memcpy(
      fram_buffer,
      &motor_endpoints.most_count_right,
      4
    );
  
    if(!fram.write(__FRAM_ENDPOINT_RIGHT_ADDR, fram_buffer, 4))
    {
      Serial.println("Failed to write to FRAM most right endpoint ADDR. Non-critical error. Proceeding.");
    }
  }

  // tune. assuming 1:1 gear ratio, 1/32 step resolution, 24V driver supply, 1.0 A limit
  set_motor_driver_VREF_via_percentage(__VREF, 100.0f);
  motor.setMaxSpeed     (__SPS);  // RPM is set in config.h; .setMaxSpeed expects steps per second
  motor.setAcceleration (400000);


  // Initialize and turn on TFT Display
  display.init             (__DISPLAY_HEIGHT, __DISPLAY_WIDTH);
  enable_display_backlight (__TFT_Light);
  display.fillScreen       (ST77XX_YELLOW);
  Serial.println           ("Display Initialized");


  // Ugh
  potentiometer_reading_count      = 0.0f;
  last_potentiometer_reading_count = 0.0f;
}


void loop() 
{
  long   target_steps; 
  float  motor_position_percentage;
  String brake_bias_bar_pos_string;


  potentiometer_reading_count = potentiometer_raw_to_motor_count(
    analogRead(__POTENTIOMETER_PIN),
    ADC_MAX_VALUE,                                
    motor_endpoints.most_count_left,
    motor_endpoints.most_count_right 
  );

  if (!(abs(potentiometer_reading_count - last_potentiometer_reading_count) < 20))
  {
    target_steps = lround(
      (double) potentiometer_reading_count * 
      ((double) __MOTOR_STEPS_PER_REV * (double) __STEP_RESOLUTION * (double) __GEAR_RATIO) /
      (double) __ENCODER_COUNTS_PER_REV
    );


    if (target_steps < motor_endpoints.most_count_left)
      target_steps = motor_endpoints.most_count_left;
    else if (target_steps < motor_endpoints.most_count_right)
      target_steps = motor_endpoints.most_count_right;


    motor.moveAbsAsync(target_steps);


    motor_position_percentage = get_motor_position_percentage(
      motor_endpoints.most_count_left,
      motor_endpoints.most_count_right,
      encoder.getValue()
    );


    brake_bias_bar_pos_string = formatted_brake_bar_position(
      motor_position_percentage
    );


    flush_string_to_auto_centered_coords(
      &display,
      brake_bias_bar_pos_string
    );

    last_potentiometer_reading_count = potentiometer_reading_count;
  }
}

