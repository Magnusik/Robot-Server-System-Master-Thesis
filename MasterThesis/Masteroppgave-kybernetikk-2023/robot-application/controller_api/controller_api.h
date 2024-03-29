/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: controller_api.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 01-Jun-2023 13:20:00
 */

#ifndef CONTROLLER_API_H
#define CONTROLLER_API_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void controller_api(double setpointX, double setpointY,
                           double newCommand, double *waitingCommand,
                           double ticksLeft, double ticksRight,
                           double *distanceDriven, double *turning,
                           double xprev, double yprev, double thetaprev,
                           double ddInitX, double ddInitY, double sThetaGyro,
                           double *thetaIntegralError, double delta_t,
                           double *thetaError, double *gX_hat, double *gY_hat,
                           double *gTheta_hat, double *leftU, double *rightU);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for controller_api.h
 *
 * [EOF]
 */
