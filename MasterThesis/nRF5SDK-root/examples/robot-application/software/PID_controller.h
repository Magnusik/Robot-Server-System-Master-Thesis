/************************************************************************/
// File:            PID_controller.h                                    //
// Author:          Eivind Jølsgard                                     //
// Purpose:         Controlling the motor speed based on encoder reading//
//                                                                      //
/************************************************************************/

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef enum{
    ERROR,
    MEASUREMENT
} DERIVATIVE_SELECT;

typedef struct PID_parameters_t
{
    double K_P;
    double K_I;
    double K_D;

    double integral_boundary;


    double measurement_previous; 
    double error_previous;
    double error_integral;
    
    double output_previous;
    double max_output; 
    double min_output;

    double reference_previous;

    DERIVATIVE_SELECT derivative_select;

} PID_parameters;

double PID_controller(PID_parameters* pid, double reference, double measurement, double delta_t);

double PID_controller_with_error_as_input(PID_parameters* pid, double error, double reference, double measurement, double delta_t);



#endif //PID_CONTROLLER_H