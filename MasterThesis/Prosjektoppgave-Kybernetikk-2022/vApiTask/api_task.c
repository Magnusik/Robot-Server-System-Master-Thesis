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
    // double gLeft = 0.0;
    // double gRight = 0.0;
    double leftU = 0.0;
    double rightU = 0.0;
    // double ticks_Left = 0;
    // double ticks_Right = 0;
    uint8_t robotMovement = moveStop;
    
    // double setpoint_x_temp = 0;
    // double setpoint_y_temp = 0;
    // bool new_setpoint_command = false;
    // double xHatInit = 0;
    // double yHatInit = 0;
    // double thetaHatInit = 0;
    // float total_ticks_r=0;
    // float total_ticks_l=0;
    
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


    //new api
  double turning=1;
  double setpointX = 0;
  double setpointY = 0;
  double newCommand = 1;
  double xprev = 0;
  double yprev = 0;
  double thetaprev = 0;
  double distanceDriven =0;
  double waitingCommand =0;
  gTheta_hat = thetaprev;
   
  //uncomment for square test

  int squareTestInterval = 20;
  double xarrayPos[4*squareTestInterval];
  double yarrayPos[4*squareTestInterval];

  double xWaypoint1 = 300;
  double yWaypoint1 = 0;

  double xWaypoint2 = 300;
  double yWaypoint2 = 300;
  
  double xWaypoint3 = 0;
  double yWaypoint3 = 300;

  double xWaypoint4 = 0;
  double yWaypoint4 = 0;

  double xWaypoint  = xWaypoint1;
  double yWaypoint = yWaypoint1;


// uncomment for straight line test

// double xWaypoint = 1000;
// double yWaypoint = 0;
// int lineTestInterval = 20;
// double xarrayPos[lineTestInterval];
// double yarrayPos[lineTestInterval];

    while (true) {

        vTaskDelay(200);
        //TickType_t ticks_since_startup_prev = ticks_since_startup;
        // double X_hat = gX_hat;
        // double Y_hat = gY_hat;
        // double Theta_hat = gTheta_hat;

        //Read IMU data iff Kalman is enabled
        //IMU_reading_t gyro;
        // IMU_reading_t accel;
        // IMU_read();
        //gyro = IMU_getGyro();
        // accel = IMU_getAccel();

        // double gyro_x = gyro.x; 
        // double gyro_y = gyro.y; 
        // double gyro_z = gyro.z; 
        // double accel_x = accel.x;
        // double accel_y = accel.y; 
        // double accel_z = accel.z;

            if (debug){
            //TICKS
            //printf("\r\nTicks Left: %f Ticks Right: %f\n\r",(float)ticks_Left_preHandshake,(float)ticks_Right_preHandshake);
            //printf("\r\n total ticks R: %f \n\r",total_ticks_r_preHandshake);
            //printf("\r\n total ticks L:  %f \n\r",total_ticks_l_preHandshake);

            //INPUT
            //printf("\r\nuL: %f uR: %f\n\r",(float)leftU,(float)rightU);
            
            //SETPOINT
            // printf("\r\n Setpoint: x %f y %f \n\r",(float)Setpoint.x, (float)Setpoint.y);
            // printf("\r\n New Setpoint Command %d \n\r", new_setpoint_command);

            //distance driven between setpoint commands
            //printf("\r\n Distance driven : %f \n\r",(float)distanceDriven);
            // printf("\r\n waitingcommand : %f \n\r",(float)waitingCommand);
            // printf("\r\n turning: %f \n\r",(float)turning);
            
            //GLOBAL STATES
            //double radToDeg = 180/3.14;
            //printf("\r\n %f %f %f\n\r",gX_hat,(float)gY_hat,(float)radToDeg*gTheta_hat);
            //printf("\r\n gXhat: %f gYhat: %f gTheta: %f\n\r",gX_hat,(float)gY_hat,(float)radToDeg*gTheta_hat);
            
            //GYRO VALUES
            //printf("\r\n gyroX: %f gyroY: %f gyroZ: %f\n\r",(float)gyro_x,(float)gyro_y,(float)gyro_z);
            //printf("\r\n%f %f %f\n\r",(float)gyro_x,(float)gyro_y,(float)gyro_z);
            //printf("\r\n%f %f %f\n\r",(float)accel_x,(float)accel_y,(float)accel_z);
            //printf("\r\n accelX: %f accelY: %f accelZ: %f\n\r",(float)accel_x,(float)accel_y,(float)accel_z);
            }


        if(!gHandshook){
            counter +=1;
            encoderTicks Ticks_preHandshake = encoder_get_ticks_since_last_time();
            ticks_Left_preHandshake = -(double)Ticks_preHandshake.left;
            ticks_Right_preHandshake = -(double)Ticks_preHandshake.right;
            total_ticks_r_preHandshake = total_ticks_r_preHandshake+ticks_Right_preHandshake;
            total_ticks_l_preHandshake = total_ticks_l_preHandshake+ticks_Left_preHandshake;

            // Matlab generated C code
            if (newCommand){
            turning = 1;
            setpointX = xWaypoint;
            setpointY = yWaypoint;
            waitingCommand = 0;
            newCommand = 0;
                    
            }

            api(setpointX, setpointY,newCommand,&waitingCommand,
         ticks_Left_preHandshake,ticks_Right_preHandshake,&distanceDriven, &turning,
         xprev,yprev, thetaprev,&gX_hat,
         &gY_hat,&gTheta_hat, &leftU,
         &rightU);


            ////uncomment for square test
            if (counter==squareTestInterval){
            xWaypoint=xWaypoint2;
            yWaypoint=yWaypoint2;

            newCommand=1;
            }

            if (counter ==2*squareTestInterval){
            xWaypoint=xWaypoint3;
            yWaypoint=yWaypoint3;

            newCommand=1;
            }
            if (counter == 3*squareTestInterval){
                xWaypoint=xWaypoint4;
                yWaypoint=yWaypoint4;

                newCommand =1;
            }

        if (counter==4*squareTestInterval){
                leftU  = 0;
                rightU = 0;
            }

        if(counter == 300){
            int i;
            for(i = 0; i<4*squareTestInterval; ++i){
                    printf("\r\n%f %f\n\r",(float)xarrayPos[i],(float)yarrayPos[i]);
                    vTaskDelay(10);
            }
        }

        //uncomment for linetest
        // if(counter == 150){
        //     int i;
        //     for(i = 0; i<lineTestInterval; ++i){
        //             printf("\r\n%f %f\n\r",(float)xarrayPos[i],(float)yarrayPos[i]);
        //             vTaskDelay(10);
        // }
        }

        //collision logic
        // if (checkForCollision() == true){ 
        //         motor_brake();
        //         robotMovement = moveStop;
        //         xQueueSend(scanStatusQ,&robotMovement,0);
        //         printf("\r\n Testing collision block\n\r");
        //     leftU  =  0;
        //     rightU = 0;   
        //     }
        
        // temp values of global states for plotting
            xprev     = gX_hat;
            yprev     = gY_hat;
            thetaprev = gTheta_hat;
            // uncomment for square test
            if (counter<4*squareTestInterval){
            xarrayPos[counter-1] = xprev;
            yarrayPos[counter-1] = yprev;
            }

            //uncomment for line test
            // if (counter<lineTestInterval){
            //     xarrayPos[counter-1] = xprev;
            //     yarrayPos[counter-1] = yprev;
            // }


            uL = (int)leftU;
            uR = (int)rightU;

            vMotorMovementSwitch(uL,uR);
            
        }        


        if (gHandshook) {
            if (xQueueReceive(poseControllerQ, &Setpoint, 0) == pdTRUE) {
            NRF_LOG_INFO("\n\nNew setpoint: X = "NRF_LOG_FLOAT_MARKER", Y = "NRF_LOG_FLOAT_MARKER"\n\n",NRF_LOG_FLOAT(Setpoint.x), NRF_LOG_FLOAT(Setpoint.y));
            }
            
            encoderTicks Ticks_preHandshake = encoder_get_ticks_since_last_time();
            ticks_Left_preHandshake = -(double)Ticks_preHandshake.left;
            ticks_Right_preHandshake = -(double)Ticks_preHandshake.right;
            total_ticks_r_preHandshake = total_ticks_r_preHandshake+ticks_Right_preHandshake;
            total_ticks_l_preHandshake = total_ticks_l_preHandshake+ticks_Left_preHandshake;


            if (newCommand){
            turning = 1;
            setpointX = xWaypoint;
            setpointY = yWaypoint;
            waitingCommand = 0;
            newCommand = 0;
                    
            }
            
            taskYIELD();

            // Matlab generated C code
            api(setpointX, setpointY,newCommand,&waitingCommand,
         ticks_Left_preHandshake,ticks_Right_preHandshake,&distanceDriven, &turning,
         xprev,yprev, thetaprev,&gX_hat,
         &gY_hat,&gTheta_hat, &leftU,
         &rightU);


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

           
            // Cast to int before sending to motor
            int uR = (int)rightU;
            int uL = (int)leftU;


			xSemaphoreTake(xPoseMutex, 15);
            set_position_estimate_heading(gTheta_hat);					// previously: gTheta_hat = kf_state.heading;  replaced with: gTheta_hat = gyroSum;
            set_position_estimate_x(gX_hat/1000); // convert from mm to m
            set_position_estimate_y(gY_hat/1000); // convert from mm to m
            xSemaphoreGive(xPoseMutex);

            
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
            // 
        } //endif (gHandshook)
    }



