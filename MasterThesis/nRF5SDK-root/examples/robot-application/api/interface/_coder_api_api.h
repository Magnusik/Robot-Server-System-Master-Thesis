/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_api_api.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 03-Feb-2023 11:06:07
 */

#ifndef _CODER_API_API_H
#define _CODER_API_API_H

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
void api(real_T setpointX, real_T setpointY, real_T newCommand,
         real_T *waitingCommand, real_T ticksLeft, real_T ticksRight,
         real_T *distanceDriven, real_T *turning, real_T xprev, real_T yprev,
         real_T thetaprev, real_T ddInitX, real_T ddInitY, real_T *gX_hat,
         real_T *gY_hat, real_T *gTheta_hat, real_T *leftU, real_T *rightU);

void api_api(const mxArray *const prhs[13], int32_T nlhs,
             const mxArray *plhs[8]);

void api_atexit(void);

void api_initialize(void);

void api_terminate(void);

void api_xil_shutdown(void);

void api_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_api_api.h
 *
 * [EOF]
 */
