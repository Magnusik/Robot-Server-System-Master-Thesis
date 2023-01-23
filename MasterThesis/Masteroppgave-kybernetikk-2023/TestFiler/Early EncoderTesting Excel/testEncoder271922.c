#include "api_task.h"

#include "api.h"

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

void vApiTask(void *arg){
    vServo_setAngle(0);

    struct sCartesian Setpoint = {0, 0};
    // int16_t x_coordinates[2] = {10, 10}; //, 5, 0};
    // int16_t y_coordinates[2] = {0, 0};//, 0, 0};

    double gX_hat = 0.0;
    double gY_hat = 0.0;
    double gTheta_hat = 0.0;
    double gLeft = 0.0;
    double gRight = 0.0;
    double leftU = 0.0;
    double rightU = 0.0;
    double ticks_Left = 0;
    double ticks_Right = 0;
    uint8_t robotMovement = moveStop;
    
    double setpoint_x_temp = 0;
    double setpoint_y_temp = 0;
    bool new_setpoint_command = false;
    double xHatInit = 0;
    double yHatInit = 0;
    double thetaHatInit = 0;
    float total_ticks_r=0;
    float total_ticks_l=0;
    
    //prehandshake
    double ticks_Left_preHandshake      = 0;
    double ticks_Right_preHandshake     = 0;
    double total_ticks_r_preHandshake   = 0;
    double total_ticks_l_preHandshake   = 0;

    //encoder testing
    int counter = 0;
    int uL = 0;
    int uR = 0;
    bool debug = true;
    // bool active_command_exists = true;

        // for (int i = 0; i < 2; i ++) {
        //     Setpoint.x = x_coordinates[i];
        //     Setpoint.y = y_coordinates[i];
            NRF_LOG_INFO("\n\nActive setpoint: X = "NRF_LOG_FLOAT_MARKER", Y = "NRF_LOG_FLOAT_MARKER"\n\n",NRF_LOG_FLOAT(Setpoint.x), NRF_LOG_FLOAT(Setpoint.y));
    // while (active_command_exists) {
    while (true) {
        vTaskDelay(200);
        double X_hat = gX_hat;
        double Y_hat = gY_hat;
        double Theta_hat = gTheta_hat;

        // Read IMU data iff Kalman is enabled
        IMU_reading_t gyro;
        IMU_reading_t accel;
        IMU_read();
        gyro = IMU_getGyro();
        accel = IMU_getAccel();

        double gyro_x = gyro.x; 
        double gyro_y = gyro.y; 
        double gyro_z = gyro.z; 
        double accel_x = accel.x;
        double accel_y = accel.y; 
        double accel_z = accel.z;


        if(!gHandshook){
            counter +=1;
            encoderTicks Ticks_preHandshake = encoder_get_ticks_since_last_time();
            ticks_Left_preHandshake = -(double)Ticks_preHandshake.left;
            ticks_Right_preHandshake = -(double)Ticks_preHandshake.right;
            total_ticks_r_preHandshake = total_ticks_r_preHandshake+(float)(ticks_Right_preHandshake);
            total_ticks_l_preHandshake = total_ticks_l_preHandshake+(float)(ticks_Left_preHandshake);

            // Matlab generated C code
            
            api((double)Setpoint.x, (double)Setpoint.y, new_setpoint_command,
            ticks_Left_preHandshake,ticks_Right_preHandshake,
            gyro_x, gyro_y, gyro_z,
            accel_x, accel_y, accel_z,
            X_hat, Y_hat,Theta_hat,
            xHatInit, yHatInit, thetaHatInit,
            &gX_hat, &gY_hat, &gTheta_hat,
            &gLeft, &gRight, &leftU, &rightU);


            if (debug){
            //TICKS
            // printf("\r\nTicks Left: %f Ticks Right: %f\n\r",(float)ticks_Left_preHandshake,(float)ticks_Right_preHandshake);
            // printf("\r\n total ticks R: %f \n\r",total_ticks_r_preHandshake);
            // printf("\r\n total ticks L:  %f \n\r",total_ticks_l_preHandshake);

            //INPUT
            // printf("\r\nuL: %i uR: %i\n\r",uL,uR);
            
            //SETPOINT
            // printf("\r\n Setpoint: x %f y %f \n\r",(float)Setpoint.x, (float)Setpoint.y);
            // printf("\r\n New Setpoint Command %d \n\r", new_setpoint_command);
            
            //GLOBAL STATES
            //printf("\r\n gXhat: %f gYhat: %f gTheta: %f\n\r",(float)gX_hat,(float)gY_hat,(float)gTheta_hat);
            
            //INIT VALUES
            //printf("\r\n xHatInit: %f yHatInit: %f thetaHatInit: %f\n\r",(float)xHatInit,(float)yHatInit,(float)thetaHatInit);
            
            //GYRO VALUES
            // printf("\r\n gyroX: %f gyroY: %f gyroZ: %f\n\r",(float)gyro_x,(float)gyro_y,(float)gyro_z);
            // printf("\r\n accelX: %f accelY: %f accelZ: %f\n\r",(float)accel_x,(float)accel_y,(float)accel_z);
            
            }

            if (counter<10){
                uL = 15;
                uR = 15;
                robotMovement = moveForward;
                vMotorMovementSwitch(uL,uR);
                printf("\r\nTicks Left: %f Ticks Right: %f\n\r",(float)ticks_Left_preHandshake,(float)ticks_Right_preHandshake);
            }
            else if (counter>9 && counter<15){
                if (counter==10){
                
                
                printf("\r\n total ticks R: %f \n\r",total_ticks_r_preHandshake);
                printf("\r\n total ticks L:  %f \n\r",total_ticks_l_preHandshake);
                }
                uL = -15;
                uR = 15;
                robotMovement = moveForward;
                vMotorMovementSwitch(uL,uR);
                printf("\r\nTicks Left: %f Ticks Right: %f\n\r",(float)ticks_Left_preHandshake,(float)ticks_Right_preHandshake);

            }

            else{
                if (counter==15){
                printf("\r\n Total ticks R: %f \n\r",total_ticks_r_preHandshake);
                printf("\r\n Total ticks L:  %f \n\r",total_ticks_l_preHandshake);
                }
                uL = 0;
                uR = 0;
                robotMovement = moveStop;
                vMotorMovementSwitch(uL,uR);
                motor_brake();
            }
            
        }        


        if (gHandshook) {
            setpoint_x_temp = (double)Setpoint.x;  
            setpoint_y_temp = (double)Setpoint.y;
            if (xQueueReceive(poseControllerQ, &Setpoint, 0) == pdTRUE) {
            NRF_LOG_INFO("\n\nNew setpoint: X = "NRF_LOG_FLOAT_MARKER", Y = "NRF_LOG_FLOAT_MARKER"\n\n",NRF_LOG_FLOAT(Setpoint.x), NRF_LOG_FLOAT(Setpoint.y));
            }
            

            if ((double)Setpoint.x != setpoint_x_temp || (double)Setpoint.y != setpoint_y_temp){ // remember if the command is new
                new_setpoint_command = true;
                xHatInit = gX_hat;
                yHatInit = gY_hat;
                thetaHatInit = gTheta_hat;
                printf("\r\nnew command received\n\r");
            }
            else{
                new_setpoint_command = false;
            }
            //vTaskDelay(100);
            taskYIELD();
            //printf("%f",(float)Setpoint.x);
            //printf("%f",(float)gyro_x);

            //update encoder values
            encoderTicks Ticks = encoder_get_ticks_since_last_time();
            ticks_Left = -(double)Ticks.left;
            ticks_Right = -(double)Ticks.right;

            
            total_ticks_r = total_ticks_r+(float)(ticks_Right);
            total_ticks_l = total_ticks_l+(float)(ticks_Left);


            // Matlab generated C code
            
            api((double)Setpoint.x, (double)Setpoint.y, new_setpoint_command,
            ticks_Left,ticks_Right,
            gyro_x, gyro_y, gyro_z,
            accel_x, accel_y, accel_z,
            X_hat, Y_hat,Theta_hat,
            xHatInit, yHatInit, thetaHatInit,
            &gX_hat, &gY_hat, &gTheta_hat,
            &gLeft, &gRight, &leftU, &rightU);

            if (debug){
            //TICKS
            // printf("\r\nTicks Left: %f Ticks Right: %f\n\r",(float)ticks_Left,(float)ticks_Right);
            // printf("\r\n total ticks R: %f \n\r",total_ticks_r);
            // printf("\r\n total ticks L:  %f \n\r",total_ticks_l);

            //INPUT
            // printf("\r\nuL: %i uR: %i\n\r",uL,uR);
            
            //SETPOINT
            // printf("\r\n Setpoint: x %f y %f \n\r",(float)Setpoint.x, (float)Setpoint.y);
            // printf("\r\n New Setpoint Command %d \n\r", new_setpoint_command);
            
            //GLOBAL STATES
            // printf("\r\n gXhat: %f gYhat: %f gTheta: %f\n\r",(float)gX_hat,(float)gY_hat,(float)gTheta_hat);
            
            //Init Values
            //printf("\r\n xHatInit: %f yHatInit: %f thetaHatInit: %f\n\r",(float)xHatInit,(float)yHatInit,(float)thetaHatInit);
            
            //Gyro Values
            // printf("\r\n gyroX: %f gyroY: %f gyroZ: %f\n\r",(float)gyro_x,(float)gyro_y,(float)gyro_z);
            // printf("\r\n accelX: %f accelY: %f accelZ: %f\n\r",(float)accel_x,(float)accel_y,(float)accel_z);
            

            rightU = 0;
            leftU = 0;
            }



            //vTaskDelay(100);
           
            // Cast to int before sending to motor
            int uR = (int)rightU;
            int uL = (int)leftU;


			xSemaphoreTake(xPoseMutex, 15);
            set_position_estimate_heading(gTheta_hat);					// previously: gTheta_hat = kf_state.heading;  replaced with: gTheta_hat = gyroSum;
            set_position_estimate_x(gX_hat/1000); // convert from mm to m
            set_position_estimate_y(gY_hat/1000); // convert from mm to m
            xSemaphoreGive(xPoseMutex);

            if (gTheta_hat != 0) {
                // NRF_LOG_INFO("\n\ntheta estimate:"NRF_LOG_FLOAT_MARKER"\n\n",NRF_LOG_FLOAT(gTheta_hat));
            } 
            // NRF_LOG_INFO("estimates[mm] X, Y = %d, %d",gX_hat,gY_hat);
            
            
            if (checkForCollision() == true){ 
                motor_brake();
                robotMovement = moveStop;
                xQueueSend(scanStatusQ,&robotMovement,0);
                printf("\r\n Testing collision block\n\r");   
            }
            else{
                robotMovement = moveForward; // Lowest value for a movement. To stop scanning
                xQueueSend(scanStatusQ,&robotMovement,0);
                vMotorMovementSwitch(uL,uR);
                taskYIELD();
                if(uL == 0 && uR == 0){
                    robotMovement = moveStop;
                    motor_brake();
                    xQueueSend(scanStatusQ,&robotMovement,0);
                    // re-initializing estimates to avoid drifting
/*                     xSemaphoreTake(xPoseMutex, 15);
			        gX_hat = (Setpoint.x)*10; // convert from cm to mm
                    set_position_estimate_x(gX_hat/1000); // convert from mm to m
			        gY_hat = (Setpoint.y)*10; // convert from cm to mm
                    set_position_estimate_y(gY_hat/1000); // convert from mm to m
                    xSemaphoreGive(xPoseMutex);   */ 
                    // break;
                    NRF_LOG_INFO("\n\noutput for both motors is zero\n\n");
                    // active_command_exists = false;
                }
            }
            // if ((Setpoint.x - X_hat) < 0.02) active_command_exists = false;
        } //endif (gHandshook)
    }
        // }
    // vTaskPrioritySet(handle_api, 1);
} 



