/************************************************************************/
// File:            MotorSpeedControllerTask.h                          //
// Author:          Eivind Jølsgard                                     //
// Purpose:         Controlling the motor speed based on encoder reading//
//                                                                      //
/************************************************************************/

#ifndef MOTOR_SPEED_CONTROLLER_TASK_H
#define MOTOR_SPEED_CONTROLLER_TASK_H

#include <stdint.h>

#include "globals.h"

/**
 * @brief Motor speed controller task
 *
 * @param[in] pvParameters
 */
void vMotorSpeedControllerTask(void *pvParameters);

/**
 * @brief motor PID controller based on current speed and reference speed
 *
 * @param[in] left_motor_reference Left motor speed reference
  *
 * @param[in] right_motor_reference Left motor speed reference
 *
 * @param[in] left_motor_speed Left motor speed 
 *
 * @param[in] right_motor_speed Right motor speed 
 *
 * @param[in] delta_t_ms Time in millisecond since last time the controller was scheduled
 */
void motorSpeedController(int32_t left_motor_reference, int32_t right_motor_reference, int32_t left_motor_speed, int32_t right_motor_speed, uint32_t delta_t_ms);

/**
 * @brief Set motor speed reference
 *
 * @param[in] left_motor Left motor speed reference
 *
 * @param[in] right_motor Right motor speed reference
 * */
void setMotorSpeedReference(int32_t left_motor, int32_t right_motor);








#endif /* MOTOR_SPEED_CONTROLLER_TASK_H */