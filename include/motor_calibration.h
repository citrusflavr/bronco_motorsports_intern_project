#pragma once

#include <Arduino.h>
#include "config.h"
#include "types.h"


boolean calibrate_mechanical_motor_endpoints(
    TS4::Stepper         * motor,
    EncoderTool::Encoder * encoder,
    MOTOR_COUNT_ENDPOINTS* mechanical_motor_endpoints
);