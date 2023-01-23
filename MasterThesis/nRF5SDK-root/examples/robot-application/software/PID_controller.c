#include "PID_controller.h"

#include <math.h> 
#include <stdlib.h>
#include <stdio.h>
#include "nrf_log.h"
#include "functions.h"

double PID_controller(PID_parameters* pid, double reference, double measurement, double delta_t)
{

    //Find error 
    double error    = reference - measurement; 
    return PID_controller_with_error_as_input(pid, error, reference, measurement, delta_t);

}

double PID_controller_with_error_as_input(PID_parameters* pid, double error, double reference, double measurement, double delta_t)
{
    NRF_LOG_INFO("Error: " NRF_LOG_FLOAT_MARKER " \n\r", NRF_LOG_FLOAT(error));
    //Add error to integral
    pid->error_integral  += error;
    
    //Prevent integral windup
    //if((pid->error_integral > 0 && error < 0) || (pid->error_integral < 0 && error > 0) ) pid->error_integral = 0;
    if(pid->error_integral > pid->integral_boundary) pid->error_integral = pid->integral_boundary;
    else if(pid->error_integral < -pid->integral_boundary) pid->error_integral = -pid->integral_boundary;



    //PID
    double  output = 0;
    switch(pid->derivative_select){
        case ERROR:
            output = pid->K_P * error  +  (pid->error_integral * pid->K_I  * delta_t)  + ( pid->K_D * (error - pid->error_previous)) / delta_t;
            break;
        case MEASUREMENT:
            output = pid->K_P * error  +  (pid->error_integral * pid->K_I  * delta_t)  + ( pid->K_D * (error - pid->error_previous)) / delta_t;
            break;  
    }
    
    pid->measurement_previous = measurement;
    pid->error_previous  =  error;


    //Limit output
    double output_limited = output;
    if(output  >  pid->max_output ) output_limited  = pid->max_output ;
    else if(output  < -pid->max_output ) output_limited  = -pid->max_output ;
    else output_limited = output;

    pid->error_previous = output_limited ; //_limited;
    pid->reference_previous = reference;

    //Stop if output is close to zero
    //if(abs(output_limited) < pid->min_output) output_limited = 0;

    return output_limited;
}