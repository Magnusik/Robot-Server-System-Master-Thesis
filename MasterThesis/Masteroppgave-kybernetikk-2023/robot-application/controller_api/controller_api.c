/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: controller_api.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 01-Jun-2023 13:20:00
 */

/* Include Files */
#include "controller_api.h"
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
 * This function changes global states and returns input to the motors.
 *  FUNCTION    ~ Description
 *  -------------------------------------------------------------------------
 *  estimator() ~ makes an estimate of the position and orientation
 *  regulator() ~ returns input to the DC motor drivers
 *  -------------------------------------------------------------------------
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
 *                double *thetaError
 *                double *gX_hat
 *                double *gY_hat
 *                double *gTheta_hat
 *                double *leftU
 *                double *rightU
 * Return Type  : void
 */
void controller_api(double setpointX, double setpointY, double newCommand,
                    double *waitingCommand, double ticksLeft, double ticksRight,
                    double *distanceDriven, double *turning, double xprev,
                    double yprev, double thetaprev, double ddInitX,
                    double ddInitY, double sThetaGyro,
                    double *thetaIntegralError, double delta_t,
                    double *thetaError, double *gX_hat, double *gY_hat,
                    double *gTheta_hat, double *leftU, double *rightU)
{
  double a;
  double b_a;
  double distanceRemaining;
  double leftover;
  double theta;
  double thetaDerivativeError;
  double uI;
  double yDiffTarget;
  /*  Estimates position and orientation [x_hat, y_hat, theta_hat] */
  /*  Returns xHat */
  /*  VARIABLE   [UNITS] [RANGE]      ~  Description */
  /*  -------------------------------------------------------------------------
   */
  /*  Encoder   [int,int]             ~ wheel encoder ticks */
  /*  sThetaGyro[rad]                 ~ theta increment from gyroscope */
  /*  turning   [bool]                ~ is the robot in rotating mode? */
  /*  sDistance [mm]                  ~ distance travelled since last cycle */
  /*  prev      [mm,mm,rad            ~ the previous iteration from xHat */
  /*  xHat      [mm,mm,rad]           ~ the current estimate pose [x,y,theta] */
  /*  -------------------------------------------------------------------------
   */
  /* Constants  [ticks], [mm] */
  /* Encoder ticks from sample, difference of tick sample and  */
  /* average of tick */
  theta = ticksRight - ticksLeft;
  yDiffTarget = theta;
  if (!rtIsNaN(theta)) {
    if (theta < 0.0) {
      yDiffTarget = -1.0;
    } else {
      yDiffTarget = (theta > 0.0);
    }
  }
  /* Distance [mm] from one sample, Distance of ticks difference (used to
   * calculate angle theta)  */
  uI = (ticksLeft + ticksRight) / 2.0 * 0.70162235930172046;
  /* Theta change orientation [rad] in one sample */
  if (*turning != 0.0) {
    *gX_hat = xprev;
    *gY_hat = yprev;
    theta = thetaprev + 0.017453292519943295 * sThetaGyro;
    uI = 0.0;
  } else {
    *gX_hat = xprev + uI * cos(thetaprev);
    *gY_hat = yprev + uI * sin(thetaprev);
    theta = thetaprev + yDiffTarget * fabs(theta) / 2.0 * 0.70162235930172046 /
                            527.78756580308527 * 2.0 * 3.1415926535897931;
  }
  /* modulus function */
  /*  smallest signed angle (maps angle into [-pi,pi] */
  *gTheta_hat = ((theta + 3.1415926535897931) -
                 6.2831853071795862 *
                     floor((theta + 3.1415926535897931) / 6.2831853071795862)) -
                3.1415926535897931;
  /* Returns the inputs to the Left and Right motors */
  /*  VARIABLE          [UNITS] [RANGE]   Description */
  /*  -------------------------------------------------------------------------
   */
  /*  xHat              [mm,mm,rad]       = [xEstimateNow, yEstimateNow,
   * thetaEstimateNow]   */
  /*  setpoint          [mm,mm]           = [xSetpoint, ySetpoint] */
  /*  ddInit            [mm,mm]           = [ddInitX, ddInitY] ~ the position
   * estimate at the time of receiving set point command */
  /*  turning           [bool]            ~ is the robot in rotating mode? */
  /*  waitingCommand    [bool]            ~ the robot is in an idle state
   * waiting for a new command? */
  /*  sDistance         [mm]              ~ distance moved this sample   */
  /*  sTime             [s]               ~ sample time this cycle  */
  /*  xDiffTarget       [mm]              ~ difference between setpoint x and
   * current x position estimate    */
  /*  yDiffTarget       [mm]              ~ difference between setpoint y and
   * current y position estimate   */
  /*  thetaError        [rad] [-pi,pi]    ~ difference between orientation of
   * robot and orientation towards setpoint  */
  /*  distanceDriven    [mm]              ~ distance driven since last setpoint
   * command */
  /*  distanceRemaining [mm]              ~ distance from current position
   * towards target */
  /*  maxDistanceTarget [mm]              ~ max distance to travel before
   * stopping   */
  /*  destinationZone   [mm]              ~ radius around end destination */
  /*  angleThreshold    [rad]             ~ stop condition for rotation mode */
  /*  uL,uR             [%, %] [0,50]     ~ input duty cycle to left and right
   * motor */
  /*  -------------------------------------------------------------------------
   */
  /* xHAt */
  /* Setpoint positions */
  /* Difference in posistion towards the target  */
  theta = setpointX - *gX_hat;
  yDiffTarget = setpointY - *gY_hat;
  /* Conditional Thresholds */
  a = setpointX - ddInitX;
  b_a = setpointY - ddInitY;
  distanceRemaining = sqrt(theta * theta + yDiffTarget * yDiffTarget);
  *distanceDriven += uI;
  /* Angle towards target   */
  /* Proportional Error */
  theta =
      (rt_atan2d_snf(yDiffTarget, theta) - *gTheta_hat) + 3.1415926535897931;
  /* modulus function */
  yDiffTarget = floor(theta / 6.2831853071795862);
  leftover = theta - 6.2831853071795862 * yDiffTarget;
  /* smallest signed angle */
  /* Derivative Error */
  thetaDerivativeError =
      ((leftover - 3.1415926535897931) - *thetaError) / delta_t;
  if (newCommand != 0.0) {
    thetaDerivativeError = 0.0;
    /*  To prevent a unintended high contribution from derivative term after
     * rotation. */
  }
  /* Integral Error */
  /*  saturation of integralerror to +-20 degrees */
  *thetaIntegralError =
      fmax(fmin(*thetaIntegralError + (leftover - 3.1415926535897931),
                0.3490658503988659),
           -0.3490658503988659);
  if (*turning != 0.0) {
    /*  Rotates robot based on its current position and threshold for rotating
     */
    /*  Returns input to DC motor drivers and manipulates turning variable */
    /*  VARIABLE    [UNITS][RANGE]          ~  Description */
    /*  -------------------------------------------------------------------------
     */
    /*  turning           [bool]            ~ is the robot in rotating mode? */
    /*  thetaError        [rad]             ~ difference between robot
     * orientation and orientation towards target */
    /*  angleThreshold    [rad]             ~ stop condition for rotation mode
     */
    /*  uL,uR,u           [%, %,%] [0,50]   ~ input duty cycle to left and right
     * motor */
    /*  -------------------------------------------------------------------------
     */
    if (fabs((theta - 6.2831853071795862 * yDiffTarget) - 3.1415926535897931) >
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
    double uD;
    int dirIntegralControlLeft_tmp;
    theta = fmin(30.0, distanceRemaining / 200.0 + 10.0);
    /* Input slows down depending on distance remaining to target */
    /*  Moves the robot towards the target. PID controller to controll each
     * wheel input.  */
    /*  Returns the input uL and uR to the DC motors drivers */
    /*  VARIABLE          [UNITS] [RANGE]     Description */
    /*  -------------------------------------------------------------------------
     */
    /*  thetaError        [rad] [-pi,pi]      ~ difference between orientation
     * of robot and orientation towards setpoint  */
    /*  distanceRemaining   [mm]              ~ distance towards the destination
     */
    /*  distanceDriven      [mm]              ~ distance driven since last
     * command */
    /*  destinationZone     [mm]              ~ radius around end destination */
    /*  maxDistanceTarget   [mm]              ~ maximal distance to travel for a
     * command */
    /*  waitingCommand      [bool]            ~ the robot is in an idle state
     * waiting for a new command? */
    /*  thetaIntegralError  [rad]             ~ accumulated angle deviation */
    /*  thetaDerivativeError[rad/s]           ~ theta derivative divided by loop
     * time */
    /*  sTime               [s]               ~ sample time */
    /*  uL,uR,u             [%, %,%] [0,50]   ~ input duty cycle to left and
     * right motor */
    /*  ----------------------------------------------------------------------------
     */
    /* PID gains */
    /* PID saturation limits  */
    /* PID corrections with saturation */
    yDiffTarget = fmin(20.0 * fabs(leftover - 3.1415926535897931), 20.0);
    uI = fmin(10.0 * fabs(*thetaIntegralError) * delta_t, 10.0);
    uD = fmin(0.5 * fabs(thetaDerivativeError), 10.0);
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
    if (!rtIsNaN(thetaDerivativeError)) {
      if (thetaDerivativeError < 0.0) {
        thetaDerivativeError = -1.0;
      } else {
        thetaDerivativeError = (thetaDerivativeError > 0.0);
      }
    }
    if ((distanceRemaining > 100.0) &&
        (*distanceDriven < sqrt(a * a + b_a * b_a)) &&
        (!(*waitingCommand != 0.0))) {
      *rightU = rt_roundd_snf(
          ((theta +
            (dirProportionalControlLeft_tmp + 1.0) / 2.0 * yDiffTarget) +
           ((double)dirIntegralControlLeft_tmp + 1.0) / 2.0 * uI) -
          (thetaDerivativeError + 1.0) / 2.0 * uD);
      /*  to minimize type casting error to int later */
      *leftU = rt_roundd_snf(
          ((theta +
            (1.0 - dirProportionalControlLeft_tmp) / 2.0 * yDiffTarget) +
           (1.0 - (double)dirIntegralControlLeft_tmp) / 2.0 * uI) -
          (1.0 - thetaDerivativeError) / 2.0 * uD);
      /*  [uL,uR] must not exceed MAX value [50,50]. */
    } else {
      *rightU = 0.0;
      *leftU = 0.0;
    }
    if ((*leftU == 0.0) && (*rightU == 0.0)) {
      /*  Needed to idle the robot */
      *waitingCommand = 1.0;
    }
  }
  *thetaError = leftover - 3.1415926535897931;
}

/*
 * File trailer for controller_api.c
 *
 * [EOF]
 */
