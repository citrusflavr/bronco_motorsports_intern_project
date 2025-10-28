#include "../include/motor_calibration.h"
#include "../include/motor_functions.h"


boolean calibrate_motor_endpoints(
    TS4::Stepper* motor,
    EncoderTool::Encoder* encoder,
    MOTOR_COUNT_ENDPOINTS* motor_endpoints
)
{
    int iteration_limit = 100000;
    int iteration_count = 0;
    set_motor_driver_VREF_via_percentage(__VREF, 20.0f);
    
    motor->setMaxSpeed     (__CALIBRATION_SPS);
    motor->setAcceleration (400000);

    for(iteration_count = 0; iteration_count < iteration_limit; iteration_count++) 
    {
        if (digitalRead(__STL_REP) == HIGH)
        {
            motor->moveRelAsync(25);
            motor_endpoints->most_count_left = encoder->getValue();

            encoder->setValue    (0);
            motor  ->setPosition (0);
            break;
        }

        motor->moveRelAsync(-50);
    }

    if (iteration_count == (iteration_limit - 1))
        return false;

    
    for (iteration_count = 0; iteration_count < iteration_limit; iteration_count++)
    {
        if (digitalRead(__STL_REP) == HIGH)
        {
            motor->moveRelAsync(-25);
            motor_endpoints->most_count_right = encoder->getValue();
            break;
        }

        motor->moveRelAsync(50);
    }

    if (iteration_count == (iteration_limit - 1))
        return false;



    return true;
}