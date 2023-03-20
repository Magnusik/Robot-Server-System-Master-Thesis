/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: controllerApi.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Mar-2023 14:44:52
 */

/* Include Files */
#include "controllerApi.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }
    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }
    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }
  return y;
}

/*
 * changes global states and returns input to the motors
 *
 *
 * Arguments    : double setpointX
 *                double setpointY
 *                double newCommand
 *                double *waitingCommand
 *                double ticksLeft
 *                double ticksRight
 *                double *distanceDriven
 *                double *turning
 *                double xprev
 *                double yprev
 *                double thetaprev
 *                double ddInitX
 *                double ddInitY
 *                double sThetaGyro
 *                double *gX_hat
 *                double *gY_hat
 *                double *gTheta_hat
 *                double *leftU
 *                double *rightU
 * Return Type  : void
 */
void controllerApi(double setpointX, double setpointY, double newCommand,
                   double *waitingCommand, double ticksLeft, double ticksRight,
                   double *distanceDriven, double *turning, double xprev,
                   double yprev, double thetaprev, double ddInitX,
                   double ddInitY, double sThetaGyro, double *gX_hat,
                   double *gY_hat, double *gTheta_hat, double *leftU,
                   double *rightU)
{
  double a;
  double b_a;
  double delta_y;
  double distanceRemaining;
  double sDistance;
  double theta;
  (void)newCommand;
  /*  Calculation of current position and orientation [x_hat, y_hat, theta_hat],
   * and distance moved during this sample */
  /*    Detailed explanation goes here */
  /* Constants  [ticks], [mm] */
  /* Encoder ticks from sample, difference of tick sample and  */
  /* average of tick */
  theta = ticksRight;
  if (ticksRight < 0.0) {
    theta = -1.0;
  } else if (ticksRight > 0.0) {
    theta = 1.0;
  } else if (ticksRight == 0.0) {
    theta = 0.0;
  }
  /* Distance [mm] from one sample, Distance of ticks difference (used to
   * calculate angle theta)  */
  sDistance = (ticksLeft + ticksRight) / 2.0 * 0.70162235930172046;
  /* Theta change orientation [rad] in one sample */
  if (*turning != 0.0) {
    *gX_hat = xprev;
    *gY_hat = yprev;
    theta = thetaprev + 0.017453292519943295 * sThetaGyro;
    sDistance = 0.0;
  } else {
    *gX_hat = xprev + sDistance * cos(thetaprev);
    *gY_hat = yprev + sDistance * sin(thetaprev);
    theta = thetaprev + theta * fabs(ticksRight - ticksLeft) / 2.0 *
                            0.70162235930172046 / 527.78756580308527 * 2.0 *
                            3.1415926535897931;
  }
  /* modulus function */
  /*  smallest signed angle (maps angle into [-pi,pi] */
  *gTheta_hat = ((theta + 3.1415926535897931) -
                 6.2831853071795862 *
                     floor((theta + 3.1415926535897931) / 6.2831853071795862)) -
                3.1415926535897931;
  /* Returns the inputs to the Left and Right motors */
  /*  xHat = [x_hat, y_hat, theta_hat] ~ [mm,mm,rad] */
  /*  setpoint = [x_d, y_d] ~ [mm,mm] */
  /*  turning ~ is the robot in rotating mode? */
  /*  sDistance ~ distance moved this sample */
  /*  waitingCommand ~ the robot is in an idle state waiting for a new command
   */
  /* Unpacking arguments */
  /* xHAt */
  /* setpoint */
  /* Errors */
  theta = setpointX - *gX_hat;
  delta_y = setpointY - *gY_hat;
  /* thresholds */
  a = setpointX - ddInitX;
  b_a = setpointY - ddInitY;
  distanceRemaining = sqrt(theta * theta + delta_y * delta_y);
  *distanceDriven += sDistance;
  /*  angle towards setpoint   */
  theta = (rt_atan2d_snf(delta_y, theta) - *gTheta_hat) + 3.1415926535897931;
  /* modulus function */
  theta -= 6.2831853071795862 * floor(theta / 6.2831853071795862);
  /* smallest signed angle */
  if (*turning != 0.0) {
    /* Rotates robot based on its current position and threshold for rotating */
    /*  delta_x  = x_d - x  */
    /*  delta_y  = y_d - y */
    /*  theta_0 = theta_hat  */
    if (fabs(theta - 3.1415926535897931) > 0.05235987755982989) {
      *turning = 1.0;
      if (theta - 3.1415926535897931 > 0.0) {
        /*  rotate counterclockwise */
        *rightU = 12.0;
        *leftU = -12.0;
      } else {
        /*  rotate counter clockwise */
        *rightU = -12.0;
        *leftU = 12.0;
      }
    } else {
      *turning = 0.0;
      *rightU = 0.0;
      *leftU = 0.0;
    }
    *distanceDriven = 0.0;
  } else {
    delta_y = fmin(30.0, floor(distanceRemaining / 100.0 + 10.0));
    /* Input slows down depending on distance remaining to target */
    /* Moves the robot Forward if thresholds are met */
    /*   distanceRemaining [mm] */
    /*   distanceDriven [mm] */
    /*   thresholdDR [mm] */
    /*   thresholdDD [mm] */
    /*  k_i = 0.5; */
    /*  k_d = 0.5; */
    /* thetaIntegralError = thetaIntegralError+thetaError; %% must be  */
    /* pidU = k_p*thetaError+k_i*thetaIntegralError+k_d*thetaErrorDot; */
    if ((distanceRemaining > 50.0) &&
        (*distanceDriven < sqrt(a * a + b_a * b_a)) &&
        (!(*waitingCommand != 0.0))) {
      theta = 0.75 * (theta - 3.1415926535897931);
      *rightU = (delta_y + 1.0) + theta;
      *leftU = delta_y - theta;
    } else {
      *rightU = 0.0;
      *leftU = 0.0;
    }
    if ((*leftU == 0.0) && (*rightU == 0.0)) {
      *waitingCommand = 1.0;
    }
  }
}

/*
 * File trailer for controllerApi.c
 *
 * [EOF]
 */
