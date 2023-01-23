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

    //prehandshake
    double ticks_Left_preHandshake      = 0;
    double ticks_Right_preHandshake     = 0;
    double total_ticks_r_preHandshake   = 0;
    double total_ticks_l_preHandshake   = 0;

    

    //encoder testing
    int counter = 0;
    int uL = 0;
    int uR = 0;
    bool debug = false;

   
    while (true) {

        vTaskDelay(200);

        encoderTicks Ticks_preHandshake = encoder_get_ticks_since_last_time();
        ticks_Left_preHandshake = -(double)Ticks_preHandshake.left;
        ticks_Right_preHandshake = -(double)Ticks_preHandshake.right;
        total_ticks_r_preHandshake = total_ticks_r_preHandshake+ticks_Right_preHandshake;
        total_ticks_l_preHandshake = total_ticks_l_preHandshake+ticks_Left_preHandshake;

        if (debug){
            //TICKS
            printf("\r\nTicks Left: %f Ticks Right: %f\n\r",(float)ticks_Left_preHandshake,(float)ticks_Right_preHandshake);
            // printf("\r\n total ticks R: %f \n\r",total_ticks_r_preHandshake);
            // printf("\r\n total ticks L:  %f \n\r",total_ticks_l_preHandshake);
   
            //GYRO VALUES
            printf("\r\n gyroX: %f gyroY: %f gyroZ: %f\n\r",(float)gyro_x,(float)gyro_y,(float)gyro_z);
            printf("\r\n accelX: %f accelY: %f accelZ: %f\n\r",(float)accel_x,(float)accel_y,(float)accel_z);
            
        }
            counter+=1;
            
            // Encoder test sequence  
            if (counter<10){
                uL = 15;
                uR = 15;
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
                vMotorMovementSwitch(uL,uR);
                motor_brake();
            }
                    
    }
} 



