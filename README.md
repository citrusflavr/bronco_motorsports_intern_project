# bronco_motorsports_intern_project

# current implemented features (not tested)
- read from adafruit FRAM for motor count endpoints
- write to adafruit FRAM for motor count endpoints
- software calibration of motor count endpoints
- potentiometer controls motor
- displays mechanical position of brake bias bar on a little adafruit SPI screen
- compiles!

# dependencies
- teensy4.1 for TeensyStep4
- teensy4.1 for EncoderTool
- adafruit ST78xx display
- adafruit fram

# things todo
- certain things uses controller (software) count, while others use encoder (mechanical) count. naming scheme not clear. improve naming.

- refactor fram related code to another file
- make potentiometer's adc to count function wiring agonistic (wtf does this mean? 10/28/25)

- most important: review for logic bugs