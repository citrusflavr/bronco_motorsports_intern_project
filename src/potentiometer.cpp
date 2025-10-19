#include "../include/potentiometer.h" 

// Linearly maps potentiometer movement to
// motor movement 

// ADC 4095 = Most Left
// ADC 0    = Most Right
long potentiometer_raw_to_motor_count(
    int   raw_adc,
    int   adc_max,
    float motor_endpoint_left,
    float motor_endpoint_right
)
{
    float potentiometer_moved_percent;
    long  motor_counts;

    potentiometer_moved_percent = (float)raw_adc/ (float)adc_max; // normalization

    
    if (potentiometer_moved_percent < 0.0f)
        potentiometer_moved_percent = 0.0f;
    if (potentiometer_moved_percent > 1.0f)
        potentiometer_moved_percent = 1.0f;

   // linear interpolation
   motor_counts = (long)(motor_endpoint_right + (motor_endpoint_left - motor_endpoint_right) * potentiometer_moved_percent);
   
   return motor_counts;
}