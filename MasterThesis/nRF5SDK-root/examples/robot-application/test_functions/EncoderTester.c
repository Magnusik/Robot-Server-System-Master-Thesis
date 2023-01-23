#include "defines.h"
#include "encoder_with_counter.h"
#include "freeRTOS.h"
#include "functions.h"
#include "math.h"
#include "motor.h"
#include "nrf_log.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "ControllerTask.h"
#include "globals.h"
#include "PID.h"
//encoderTicks encoder;

void Encoder_tester(void *pvParameters) {
    NRF_LOG_INFO("Enter encoder test");
    //for (int t=0;t<122;t++){
    TickType_t xLastWakeTime = xTaskGetTickCount();
    float vLeft;
    float vRight;
    PID_params PID_params_left_motor;
    PID_params PID_params_right_motor;
    double left_motor_reference, right_motor_reference;
    double left_motor_speed, right_motor_speed;  //For digital low pass filter 
    left_motor_reference = right_motor_reference = 0.2;
    left_motor_speed = right_motor_speed = 0;
    /* Task init */
    int t = 0;
    init_PID(&PID_params_left_motor,MOTOR_SPEED_CTRL_TASK_DELAY_TIME/1000.0,0.3,75,150,0.0005);
    init_PID(&PID_params_right_motor,MOTOR_SPEED_CTRL_TASK_DELAY_TIME/1000.0,0.03,75,150,0.0005);
    while(true){
        vTaskDelayUntil(&xLastWakeTime,100);
        t += 1;
        if (t == 500) {
            left_motor_reference = right_motor_reference = 0;
        }
        encoderTicks ticks = encoder_with_counter_get_ticks_since_last_time();
        vLeft = 10*ticks.left*WHEEL_FACTOR_MM/1000.0;
        vRight = 10*ticks.right*WHEEL_FACTOR_MM/1000.0;
        left_motor_speed = vLeft;
        right_motor_speed= vRight;


        double left_u;
        if(left_motor_reference != 0)
        {

                controller_PID(&PID_params_left_motor,left_motor_reference,left_motor_speed,100);
                left_u = PID_params_left_motor.u[0];  

        }
        else
        {
            left_u = 0;
        }
                
        double right_u;
        if(right_motor_reference != 0)
        {
                controller_PID(&PID_params_right_motor,right_motor_reference,right_motor_speed,100);
                right_u = PID_params_right_motor.u[0];          
        }
        else
        {
            right_u = 0;
        }

        vMotorMovementSwitch(left_u,right_u);
        //printf("\n%f %f %f %f %f %f", PID_params_left_motor.e[0],PID_params_left_motor.e[1],PID_params_left_motor.e[1],PID_params_right_motor.e[0],PID_params_right_motor.e[1],PID_params_right_motor.e[1]);
        printf("\n%f %f %f %f %f %f",left_motor_reference,right_motor_reference,left_motor_speed,right_motor_speed, left_u, right_u);
    }
}