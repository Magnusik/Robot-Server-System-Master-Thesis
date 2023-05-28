/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_controllerApi_api.h
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 28-May-2023 20:34:53
 */

#ifndef _CODER_CONTROLLERAPI_API_H
#define _CODER_CONTROLLERAPI_API_H

/* Include Files */
#include "emlrt.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void controllerApi(real_T setpointX, real_T setpointY, real_T newCommand,
                   real_T *waitingCommand, real_T ticksLeft, real_T ticksRight,
                   real_T *distanceDriven, real_T *turning, real_T xprev,
                   real_T yprev, real_T thetaprev, real_T ddInitX,
                   real_T ddInitY, real_T sThetaGyro,
                   real_T *thetaIntegralError, real_T delta_t,
                   real_T *thetaError, real_T *gX_hat, real_T *gY_hat,
                   real_T *gTheta_hat, real_T *leftU, real_T *rightU);

void controllerApi_api(const mxArray *const prhs[17], int32_T nlhs,
                       const mxArray *plhs[10]);

void controllerApi_atexit(void);

void controllerApi_initialize(void);

void controllerApi_terminate(void);

void controllerApi_xil_shutdown(void);

void controllerApi_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_controllerApi_api.h
 *
 * [EOF]
 */
