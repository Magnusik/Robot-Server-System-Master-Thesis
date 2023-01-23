/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: api.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 18-Dec-2022 14:05:41
 */

#ifndef API_H
#define API_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void api(double setpointX, double setpointY, double newCommand,
                double *waitingCommand, double ticksLeft, double ticksRight,
                double *distanceDriven, double *turning, double xprev,
                double yprev, double thetaprev, double *gX_hat, double *gY_hat,
                double *gTheta_hat, double *leftU, double *rightU);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for api.h
 *
 * [EOF]
 */
