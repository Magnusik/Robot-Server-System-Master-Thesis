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


    double gX_hat = 0.0;
    double gY_hat = 0.0;
    double gTheta_hat = 0.0;

    double leftU = 0.0;
    double rightU = 0.0;
    
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

  int squareTestInterval = 15;
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

    while (true) {

        vTaskDelay(200);

            if (debug){
            //TICKS
            printf("\r\nTicks Left: %f Ticks Right: %f\n\r",(float)ticks_Left_preHandshake,(float)ticks_Right_preHandshake);
            // printf("\r\n total ticks R: %f \n\r",total_ticks_r_preHandshake);
            // printf("\r\n total ticks L:  %f \n\r",total_ticks_l_preHandshake);

            //INPUT
            printf("\r\nuL: %f uR: %f\n\r",(float)leftU,(float)rightU);
            
            //SETPOINT
            // printf("\r\n Setpoint: x %f y %f \n\r",(float)Setpoint.x, (float)Setpoint.y);
            // printf("\r\n New Setpoint Command %d \n\r", new_setpoint_command);

            //distance driven between setpoint commands
            printf("\r\n Distance driven : %f \n\r",(float)distanceDriven);
            // printf("\r\n waitingcommand : %f \n\r",(float)waitingCommand);
            // printf("\r\n turning: %f \n\r",(float)turning);
            
            //GLOBAL STATES
            double radToDeg = 180/3.14;
            printf("\r\n gXhat: %f gYhat: %f gTheta: %f\n\r",gX_hat,(float)gY_hat,(float)radToDeg*gTheta_hat);
            
            //GYRO VALUES
            // printf("\r\n gyroX: %f gyroY: %f gyroZ: %f\n\r",(float)gyro_x,(float)gyro_y,(float)gyro_z);
            // printf("\r\n accelX: %f accelY: %f accelZ: %f\n\r",(float)accel_x,(float)accel_y,(float)accel_z);
            
            }

            counter +=1;

            //Encoder ticks
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


            // uncomment for square test
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

        if(counter == 150){
            int i;
            for(i = 0; i<4*squareTestInterval; ++i){
                    printf("\r\n%f %f\n\r",(float)xarrayPos[i],(float)yarrayPos[i]);
                    vTaskDelay(10);
            }
        }

        
        // temp values of global states
            xprev     = gX_hat;
            yprev     = gY_hat;
            thetaprev = gTheta_hat;
            //uncomment for square test plotting
            if (counter<4*squareTestInterval){
            xarrayPos[counter-1] = xprev;
            yarrayPos[counter-1] = yprev;
            }

            uL = (int)leftU;
            uR = (int)rightU;
            vMotorMovementSwitch(uL,uR);
            
        }        
}



