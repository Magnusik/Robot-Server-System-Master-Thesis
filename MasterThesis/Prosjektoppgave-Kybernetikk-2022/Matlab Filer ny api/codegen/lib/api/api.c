/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: api.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 18-Dec-2022 14:05:41
 */

/* Include Files */
#include "api.h"
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
 *                double *gX_hat
 *                double *gY_hat
 *                double *gTheta_hat
 *                double *leftU
 *                double *rightU
 * Return Type  : void
 */
void api(double setpointX, double setpointY, double newCommand,
         double *waitingCommand, double ticksLeft, double ticksRight,
         double *distanceDriven, double *turning, double xprev, double yprev,
         double thetaprev, double *gX_hat, double *gY_hat, double *gTheta_hat,
         double *leftU, double *rightU)
{
  double delta_y;
  double sDistance;
  double sTheta;
  int uL;
  int uR;
  (void)newCommand;
  /*  Calculation of current position and orientation [x_hat, y_hat, theta_hat],
   * and distance moved during this sample */
  /*    Detailed explanation goes here */
  /* Constants  [ticks], [mm] */
  /* Encoder ticks from sample, difference of tick sample and  */
  /* average of tick */
  sTheta = ticksRight;
  if (ticksRight < 0.0) {
    sTheta = -1.0;
  } else if (ticksRight > 0.0) {
    sTheta = 1.0;
  } else if (ticksRight == 0.0) {
    sTheta = 0.0;
  }
  /* Distance [mm] from one sample, Distance of ticks difference (used to
   * calculate angle theta)  */
  sDistance = (ticksLeft + ticksRight) / 2.0 * 0.70162235930172046;
  /* Theta change orientation [rad] in one sample */
  sTheta = sTheta * fabs(ticksRight - ticksLeft) / 2.0 * 0.70162235930172046 /
           527.78756580308527 * 2.0 * 3.1415926535897931;
  if (*turning != 0.0) {
    *gX_hat = xprev;
    *gY_hat = yprev;
    sTheta += thetaprev;
    sDistance = 0.0;
  } else {
    *gX_hat = xprev + sDistance * cos(thetaprev);
    *gY_hat = yprev + sDistance * sin(thetaprev);
    sTheta += thetaprev;
  }
  /* modulus function */
  /*  smallest signed angle (maps angle into [-pi,pi] */
  *gTheta_hat = ((sTheta + 3.1415926535897931) -
                 6.2831853071795862 * floor((sTheta + 3.1415926535897931) /
                                            6.2831853071795862)) -
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
  sTheta = setpointX - *gX_hat;
  delta_y = setpointY - *gY_hat;
  /* thresholds */
  *distanceDriven += sDistance;
  if (*turning != 0.0) {
    /* Rotates robot based on its current position and threshold for rotating */
    /*  delta_x  = x_d - x  */
    /*  delta_y  = y_d - y */
    /*  theta_0 = theta_hat  */
    /*  angle towards setpoint   */
    sTheta =
        (rt_atan2d_snf(delta_y, sTheta) - *gTheta_hat) + 3.1415926535897931;
    /* modulus function */
    /* smallest signed angle */
    sTheta =
        (sTheta - 6.2831853071795862 * floor(sTheta / 6.2831853071795862)) -
        3.1415926535897931;
    if (fabs(sTheta) > 0.087266462599716474) {
      *turning = 1.0;
      if (sTheta > 0.0) {
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
    /* Moves the robot Forward if thresholds are met */
    /*   distanceRemaining [mm] */
    /*   distanceDriven [mm] */
    /*   thresholdDR [mm] */
    /*   thresholdDD [mm] */
    if ((sqrt(sTheta * sTheta + delta_y * delta_y) > 50.0) &&
        (*distanceDriven < 1200.0) && (!(*waitingCommand != 0.0))) {
      uR = 11;
      uL = 10;
    } else {
      uR = 0;
      uL = 0;
    }
    *leftU = uL;
    *rightU = uR;
    if ((uL == 0) && (uR == 0)) {
      *waitingCommand = 1.0;
    }
  }
}

/*
 * File trailer for api.c
 *
 * [EOF]
 */
