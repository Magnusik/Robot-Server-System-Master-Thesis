#include "ControllerApiTask.h"

#include "defines.h"
#include "nrf_log.h"
#include "FreeRTOS.h"
#include "functions.h"
#include "queue.h"
#include "semphr.h"

#include "server_communication.h"
#include "globals.h"
#include "ICM_20948.h"
#include "servo.h"
#include "robot_config.h"
#include "encoder.h"

#include "positionEstimate.h"

#include "motor.h"
#include "../drivers/display.h"
#include <stdio.h>

void vControllerApiTask(void *arg){

    //Constants
    #define COMPLETE 0
    #define GYRO_MIN 0.25

    vServo_setAngle(0);

    struct sCartesian Setpoint = {0, 0};
    double gX_hat = 0.0;
    double gY_hat = 0.0;
    double gTheta_hat = 0.0;
    double leftU = 0.0;
    double rightU = 0.0;
    uint8_t robotMovement = moveStop;

    //Wheel encoder
    double ticks_Left     = 0;
    double ticks_Right     = 0;
    double total_ticks_r   = 0;
    double total_ticks_l   = 0;

    //new controllerApi
    double turning=1;
    double setpointX = 0;
    double setpointY = 0;
    double newCommand = 1;
    double xprev = 0;
    double yprev = 0;
    double thetaprev = 0;
    double distanceDriven =0;
    double waitingCommand =0;
    double ddInitX = 0;
    double ddInitY = 0;
    gTheta_hat = thetaprev;
    double thetaIntegralError = 0;
    double thetaError = 0;

    //IMU calibration
    bool calibration = 1;
    TickType_t ticks_since_startup = xTaskGetTickCount();
    double offsetGyroX = 0;
    double offsetGyroY = 0;
    double offsetGyroZ = 0;
    double gyroAngleZ =0;
    double delta_theta_gyro =0;
    double sample_diff_gyro_z =0;
    double gyro_z_prev=0;


    //init test parameters
    int uL = 0;
    int uR = 0;
    float time_since_startup = 0;


    while (true) {

        //vTaskDelay(200);
        taskYIELD();
        TickType_t ticks_since_startup_prev = ticks_since_startup;
        ticks_since_startup = xTaskGetTickCount();
		float delta_t = (ticks_since_startup - ticks_since_startup_prev)*1.0 / configTICK_RATE_HZ;
        time_since_startup = time_since_startup+delta_t;

        //Read IMU data 
        IMU_reading_t gyro;
        // IMU_reading_t accel;
        IMU_read();
        gyro = IMU_getGyro();
        double gyro_x = gyro.x-offsetGyroX; 
        double gyro_y = gyro.y-offsetGyroY; 
        double gyro_z = gyro.z-offsetGyroZ;

        if (calibration){
            vTaskDelay(400);
            IMU_read();
            gyro = IMU_getGyro();
            offsetGyroX = gyro.x;
            offsetGyroY = gyro.y;
            offsetGyroZ = gyro.z;
            calibration = COMPLETE; 
        }

        delta_theta_gyro = gyro_z*delta_t;
        
        if(!calibration && IMU_new_data() && (gyro_z>GYRO_MIN || gyro_z<-GYRO_MIN )){
            gyroAngleZ=gyroAngleZ+delta_theta_gyro;
    
        }
        
        gyro_z_prev =gyro_z;
        //double accel_x = accel.x;
        // accel = IMU_getAccel();
        // double accel_y = accel.y; 
        // double accel_z = accel.z;


        if (xQueueReceive(poseControllerQ, &Setpoint, 0) == pdTRUE) {
            //New command has been received
            newCommand=true;
        }

            
        encoderTicks Ticks = encoder_get_ticks_since_last_time();
        ticks_Left = -(double)Ticks.left;
        ticks_Right = -(double)Ticks.right;
        total_ticks_r = total_ticks_r+ticks_Right;
        total_ticks_l = total_ticks_l+ticks_Left;

        // 
        if (newCommand){
        turning = 1;
        setpointX = Setpoint.x;
        setpointY = Setpoint.y;
        waitingCommand = 0;
        newCommand = 0;
        ddInitX = gX_hat;
        ddInitY = gY_hat;
        thetaIntegralError=0;  
        }
        //vTaskDelay(100);
            
            
        //MATLAB generated function

        controller_api(setpointX, setpointY,  newCommand,
                &waitingCommand, ticks_Left, ticks_Right,
                &distanceDriven, &turning, xprev,
                yprev, thetaprev, ddInitX,
                ddInitY, delta_theta_gyro,
                &thetaIntegralError, delta_t,&thetaError,
                &gX_hat, &gY_hat, &gTheta_hat,
                &leftU, &rightU);

        
        // temp values of global states
        xprev     = gX_hat;
        yprev     = gY_hat;
        thetaprev = gTheta_hat;

        uL = (int)leftU;
        uR = (int)rightU;

        vMotorMovementSwitch(uL,uR);
        taskYIELD();

        xSemaphoreTake(xPoseMutex, 15);
        set_position_estimate_heading(gTheta_hat);					
        set_position_estimate_x(gX_hat/1000); // convert from mm to m
        set_position_estimate_y(gY_hat/1000); // convert from mm to m
        xSemaphoreGive(xPoseMutex);
        taskYIELD();
        if (checkForCollision() == true){ 
                motor_brake();
                robotMovement = moveStop;
                xQueueSend(scanStatusQ,&robotMovement,0);
                printf("\r\n Testing collision block\n\r");   
        }

        else{
            robotMovement = moveForward; // Lowest value for a movement. To stop scanning
            xQueueSend(scanStatusQ,&robotMovement,0);
        }

    }
}



