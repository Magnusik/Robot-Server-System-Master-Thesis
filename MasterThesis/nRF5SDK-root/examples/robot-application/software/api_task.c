#include "api_task.h"

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





void vApiTask(void *arg){

    //Constants
    #define COMPLETE 0
    #define GYRO_MIN 0.25

    //MACRO variables
    #define SQUARE 1
    #define LINE 2
    #define NO_TEST 0

    //MACROs for running different sequences
    #define DEBUG 0
    #define LOG 1
    #define TEST_TYPE LINE // SQUARE | LINE | NO_TEST

    // SQUARE test parameters
    #if (TEST_TYPE==SQUARE) 
        int squareTestInterval = 60;
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
    #endif

    // run straight line test
    #if (TEST_TYPE==LINE)
        double xWaypoint = 1000;
        double yWaypoint = 0;
        int lineTestInterval = 150;
        int xarrayPos[lineTestInterval];
        int yarrayPos[lineTestInterval];
    #endif

    #if (TEST_TYPE==NO_TEST)
        double xWaypoint=0;
        double yWaypoint=0;
    #endif


    vServo_setAngle(0);

    struct sCartesian Setpoint = {0, 0};
    double gX_hat = 0.0;
    double gY_hat = 0.0;
    double gTheta_hat = 0.0;
    double leftU = 0.0;
    double rightU = 0.0;
    double ticks_Left = 0;
    double ticks_Right = 0;
    uint8_t robotMovement = moveStop;

    //prehandshake
    double ticks_Left_preHandshake      = 0;
    double ticks_Right_preHandshake     = 0;
    double total_ticks_r_preHandshake   = 0;
    double total_ticks_l_preHandshake   = 0;

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
    int counter = 0;
    int uL = 0;
    int uR = 0;
    float time_since_startup = 0;

    // used to display variables on OLED screen
    char test[128];
    char test2[128];
    char test3[128];
    char test4[128];

    while (true) {

        //vTaskDelay(200);
        taskYIELD();
        TickType_t ticks_since_startup_prev = ticks_since_startup;
        ticks_since_startup = xTaskGetTickCount();
		float delta_t = (ticks_since_startup - ticks_since_startup_prev)*1.0 / configTICK_RATE_HZ;
        time_since_startup = time_since_startup+delta_t;
        // double X_hat = gX_hat;
        // double Y_hat = gY_hat;
        // double Theta_hat = gTheta_hat;

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

        #if (DEBUG) //Printed to COM port via USB
        {
            //TICKS
            //printf("\r\nTicks Left: %f Ticks Right: %f\n\r",(float)ticks_Left_preHandshake,(float)ticks_Right_preHandshake);
            //printf("\r\n total ticks R: %f \n\r",total_ticks_r_preHandshake);
            //printf("\r\n total ticks L:  %f \n\r",total_ticks_l_preHandshake);

            //INPUT
            //printf("\r\nuL: %f uR: %f\n\r",(float)leftU,(float)rightU);
            
            //SETPOINT
            // printf("\r\n Setpoint: x %f y %f \n\r",(float)Setpoint.x, (float)Setpoint.y);
            // printf("\r\n New Setpoint Command %d \n\r", new_setpoint_command);

            //Distance Driven between setpoint commands
            //printf("\r\n Distance driven : %f \n\r",(float)distanceDriven);
            // printf("\r\n waitingcommand : %f \n\r",(float)waitingCommand);
            // printf("\r\n turning: %f \n\r",(float)turning);
            
            //GLOBAL STATES
            //double radToDeg = 180/3.14;
            //printf("\r\n %f %f %f\n\r",gX_hat,(float)gY_hat,(float)radToDeg*gTheta_hat);
            //printf("\r\n gXhat: %f gYhat: %f gTheta: %f\n\r",gX_hat,(float)gY_hat,(float)radToDeg*gTheta_hat);
            
            //GYRO VALUES
            //printf("\r\n gyroX: %f gyroY: %f gyroZ: %f\n\r",(float)gyro_x,(float)gyro_y,(float)gyro_z);
            //printf("\r\n test angle: %f\n\r",(float)gyroAngleZ);
            //printf("\r\n%f %f %f\n\r",(float)gyro_x,(float)gyro_y,(float)gyro_z);
            //printf("\r\n%f %f %f\n\r",(float)accel_x,(float)accel_y,(float)accel_z);
            //printf("\r\n accelX: %f accelY: %f accelZ: %f\n\r",(float)accel_x,(float)accel_y,(float)accel_z);

            //scope random value
            printf("\r\n Random value : %f \n\r",(float)time_since_startup);
        }
        #endif

        if(!gHandshook){
            //printf("\r\n Testing before handshake block\n\r");
            counter +=1;
            encoderTicks Ticks_preHandshake = encoder_get_ticks_since_last_time();
            ticks_Left_preHandshake = -(double)Ticks_preHandshake.left;
            ticks_Right_preHandshake = -(double)Ticks_preHandshake.right;
            total_ticks_r_preHandshake = total_ticks_r_preHandshake+ticks_Right_preHandshake;
            total_ticks_l_preHandshake = total_ticks_l_preHandshake+ticks_Left_preHandshake;

            // 
            if (newCommand){
            turning = 1;
            setpointX = xWaypoint;
            setpointY = yWaypoint;
            waitingCommand = 0;
            newCommand = 0;
            ddInitX = gX_hat;
            ddInitY = gY_hat;
            thetaIntegralError=0;  
            }
            //vTaskDelay(100);
            
        //  Displaying variables on OLED screen
        // Keep in mind that this action may slow down the system affecting the time constant of the system.
        // Use it mainly for debugging.

        // sprintf(test, "X: %i Y: %i", (int)gX_hat, (int)gY_hat); 
        // sprintf(test2, "Left: %f", (float)total_ticks_l_preHandshake);  
        // sprintf(test3, "Right: %f", (float)total_ticks_r_preHandshake);  
        // sprintf(test4, "Theta: %f", (float)gTheta_hat);  
        // display_text_on_line(1, test);
        // display_text_on_line(2, test2);
        // display_text_on_line(3, test3);
        // display_text_on_line(4, test4);
            
            
            //MATLAB generated function

            controllerApi(setpointX, setpointY,  newCommand,
                   &waitingCommand, ticks_Left_preHandshake, ticks_Right_preHandshake,
                   &distanceDriven, &turning, xprev,
                   yprev, thetaprev, ddInitX,
                   ddInitY, delta_theta_gyro,
                   &thetaIntegralError, delta_t,&thetaError,
                   &gX_hat, &gY_hat, &gTheta_hat,
                   &leftU, &rightU);

         
            

            //SQUARE test MACRO
            #if (TEST_TYPE==SQUARE)
            {   
                if(time_since_startup>1&&time_since_startup<10){
                    if (xWaypoint !=xWaypoint1 || yWaypoint!=yWaypoint1){newCommand=1;}
                    xWaypoint=xWaypoint1;
                    yWaypoint=yWaypoint1;
                }

                if (time_since_startup>10 && time_since_startup<20){
                    
                    if (xWaypoint !=xWaypoint2 || yWaypoint!=yWaypoint2){
                        newCommand=1;
                        xWaypoint=xWaypoint2;
                        yWaypoint=yWaypoint2;
                    }
                }

                if (time_since_startup>20 && time_since_startup<30){

                    if (xWaypoint !=xWaypoint3 || yWaypoint!=yWaypoint3){
                newCommand=1;    
                xWaypoint=xWaypoint3;
                yWaypoint=yWaypoint3;
                    }
                }

                if (time_since_startup>30 && time_since_startup<40){
                    if (xWaypoint !=xWaypoint4 || yWaypoint!=yWaypoint4){
                        newCommand=1;
                        xWaypoint=xWaypoint4;
                        yWaypoint=yWaypoint4;
                    }

                }

                if (time_since_startup>40){
                        leftU  = 0;
                        rightU = 0;
                    }

                if(time_since_startup>50 && LOG){ //to be continued
                    int i;
                    for(i = 0; i<4*squareTestInterval; ++i){
                            printf("\r\n%f %f\n\r",(float)xarrayPos[i],(float)yarrayPos[i]);
                            vTaskDelay(10);
                    }
                }
            }
            #endif

        //LINE test LOG MACRO
        #if(TEST_TYPE==LINE && LOG)
        {
            if(counter == 300){
                int i;
                for(i = 50; i<lineTestInterval; ++i){
                        printf("\r\n%f %f\n\r",(float)xarrayPos[i],(float)yarrayPos[i]);
                        vTaskDelay(10);
            }
            
        }
        if(counter == 151){printf("\r\n%f \n\r",(float)distanceDriven);}
        }
        #endif

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
        
        // temp values of global states
        xprev     = gX_hat;
        yprev     = gY_hat;
        thetaprev = gTheta_hat;

        // SQUARE test LOG MACRO
        #if (TEST==SQUARE && LOG)
        {
            if (counter<4*squareTestInterval){
                xarrayPos[counter-1] = xprev;
                yarrayPos[counter-1] = yprev;
            }
        }
        #endif

        // LINE test LOG MACRO
        #if (TEST_TYPE==LINE && LOG)
        {
            if (counter<=lineTestInterval){
                xarrayPos[counter-1] = (int)xprev;
                yarrayPos[counter-1] = (int)yprev;
            }
        }
        #endif

        uL = (int)leftU;
        uR = (int)rightU;

        vMotorMovementSwitch(uL,uR);
        taskYIELD();        


        if (gHandshook) {
            printf("\r\n Testing handshake block\n\r");
            encoderTicks Ticks = encoder_get_ticks_since_last_time();
            ticks_Left = -(double)Ticks.left;
            ticks_Right = -(double)Ticks.right;
            if (xQueueReceive(poseControllerQ, &Setpoint, 0) == pdTRUE) {
            NRF_LOG_INFO("\n\nNew setpoint: X = "NRF_LOG_FLOAT_MARKER", Y = "NRF_LOG_FLOAT_MARKER"\n\n",NRF_LOG_FLOAT(Setpoint.x), NRF_LOG_FLOAT(Setpoint.y));
            printf("\r\n Testing queue block\n\r");
            newCommand=true;
            }

            if (newCommand){
                turning = 1;
                setpointX = Setpoint.x*10;
                setpointY = Setpoint.y*10;
                waitingCommand = 0;
                newCommand = 0;
                ddInitX = gX_hat;
                ddInitY = gY_hat;  
            }
        
          controllerApi(setpointX, setpointY,  newCommand,
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


            if (DEBUG){
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
            }



            //vTaskDelay(100);
           
            // Cast to int before sending to motor
            int uR = (int)rightU;
            int uL = (int)leftU;


			xSemaphoreTake(xPoseMutex, 15);
            set_position_estimate_heading(gTheta_hat);					
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
            // if ((Setpoint.x - X_hat) < 0.02) active_command_exists = false;
        } //endif (gHandshook)
    }
}
    // vTaskPrioritySet(handle_api, 1);



