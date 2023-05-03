/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: controllerApi.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2023 10:29:10
 */

/* Include Files */
#include "controllerApi.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

static double rt_roundd_snf(double u);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    int b_u0;
    int b_u1;
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
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
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
 *                double *thetaIntegralError
 *                double delta_t
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
                   double ddInitY, double sThetaGyro,
                   double *thetaIntegralError, double delta_t, double *gX_hat,
                   double *gY_hat, double *gTheta_hat, double *leftU,
                   double *rightU)
{
  double a;
  double b_a;
  double delta_y;
  double distanceRemaining;
  double leftover;
  double theta;
  double u_i;
  (void)newCommand;
  /*  Calculation of current position and orientation [x_hat, y_hat, theta_hat],
   * and distance moved during this sample */
  /*    Detailed explanation goes here */
  /* Constants  [ticks], [mm] */
  /* Encoder ticks from sample, difference of tick sample and  */
  /* average of tick */
  delta_y = ticksRight;
  if (!rtIsNaN(ticksRight)) {
    if (ticksRight < 0.0) {
      delta_y = -1.0;
    } else {
      delta_y = (ticksRight > 0.0);
    }
  }
  /* Distance [mm] from one sample, Distance of ticks difference (used to
   * calculate angle theta)  */
  u_i = (ticksLeft + ticksRight) / 2.0 * 0.70162235930172046;
  /* Theta change orientation [rad] in one sample */
  if (*turning != 0.0) {
    *gX_hat = xprev;
    *gY_hat = yprev;
    theta = thetaprev + 0.017453292519943295 * sThetaGyro;
    u_i = 0.0;
  } else {
    *gX_hat = xprev + u_i * cos(thetaprev);
    *gY_hat = yprev + u_i * sin(thetaprev);
    theta = thetaprev + delta_y * fabs(ticksRight - ticksLeft) / 2.0 *
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
  /* Difference in posistion towards the target  */
  theta = setpointX - *gX_hat;
  delta_y = setpointY - *gY_hat;
  /* Condition Thresholds */
  a = setpointX - ddInitX;
  b_a = setpointY - ddInitY;
  distanceRemaining = sqrt(theta * theta + delta_y * delta_y);
  *distanceDriven += u_i;
  /* Angle towards setpoint   */
  theta = (rt_atan2d_snf(delta_y, theta) - *gTheta_hat) + 3.1415926535897931;
  /* modulus function */
  delta_y = floor(theta / 6.2831853071795862);
  leftover = theta - 6.2831853071795862 * delta_y;
  /* smallest signed angle */
  /* Integral Error */
  /*  note to self, vurdere å endre slik at små verdier er lik 0 for å unngå */
  /*  drift */
  /*  saturation of integralerror to +-20 degrees */
  *thetaIntegralError =
      fmax(fmin(*thetaIntegralError + (leftover - 3.1415926535897931),
                0.3490658503988659),
           -0.3490658503988659);
  if (*turning != 0.0) {
    /* Rotates robot based on its current position and threshold for rotating */
    /*  delta_x  = x_d - x  */
    /*  delta_y  = y_d - y */
    /*  theta_0 = theta_hat  */
    if (fabs((theta - 6.2831853071795862 * delta_y) - 3.1415926535897931) >
        0.05235987755982989) {
      *turning = 1.0;
      if (leftover - 3.1415926535897931 > 0.0) {
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
    double dirProportionalControlLeft_tmp;
    int dirIntegralControlLeft_tmp;
    theta = fmin(40.0, distanceRemaining / 500.0 + 12.0);
    /* Input slows down depending on distance remaining to target */
    /* Moves the robot Forward if thresholds are met */
    /*   distanceRemaining [mm] */
    /*   distanceDriven [mm] */
    /*   thresholdDR [mm] */
    /*   thresholdDD [mm] */
    /*  k_d = 0.5; */
    /*  Single Input [thetaError] Multiple Output [uL, uR] PID regulator (SIMO
     * PID) */
    /* PID saturation limits */
    /* PID corrections with saturation */
    delta_y = fmin(6.0 * fabs(leftover - 3.1415926535897931), 5.0);
    u_i = fmin(5.0 * fabs(*thetaIntegralError) * delta_t, 2.0);
    /*  Conditional Control Terms depending on direction */
    dirProportionalControlLeft_tmp = leftover - 3.1415926535897931;
    if (!rtIsNaN(leftover - 3.1415926535897931)) {
      if (leftover - 3.1415926535897931 < 0.0) {
        dirProportionalControlLeft_tmp = -1.0;
      } else {
        dirProportionalControlLeft_tmp = (leftover - 3.1415926535897931 > 0.0);
      }
    }
    /*  1 if tilted left, 0 if tilted right, 0.5 if at target direction */
    if (*thetaIntegralError < 0.0) {
      dirIntegralControlLeft_tmp = -1;
    } else {
      dirIntegralControlLeft_tmp = (*thetaIntegralError > 0.0);
    }
    if ((distanceRemaining > 50.0) &&
        (*distanceDriven < sqrt(a * a + b_a * b_a)) &&
        (!(*waitingCommand != 0.0))) {
      *rightU = rt_roundd_snf(
          ((theta + 1.0) +
           (dirProportionalControlLeft_tmp + 1.0) / 2.0 * delta_y) +
          ((double)dirIntegralControlLeft_tmp + 1.0) / 2.0 * u_i);
      /*  to minimize type casting error to int later */
      *leftU = rt_roundd_snf(
          (theta + (1.0 - dirProportionalControlLeft_tmp) / 2.0 * delta_y) +
          (1.0 - (double)dirIntegralControlLeft_tmp) / 2.0 * u_i);
    } else {
      *rightU = 0.0;
      *leftU = 0.0;
    }
    if ((*leftU == 0.0) && (*rightU == 0.0)) {
      /*  Needed to idle the robot */
      *waitingCommand = 1.0;
    }
  }
}

/*
 * File trailer for controllerApi.c
 *
 * [EOF]
 */
