/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_motor_gen_api.h
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 02-Nov-2020 15:59:07
 */

#ifndef _CODER_MOTOR_GEN_API_H
#define _CODER_MOTOR_GEN_API_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void motor_gen(int32_T v, int32_T h, int32_T *tv, int32_T *th);
extern void motor_gen_api(const mxArray * const prhs[2], int32_T nlhs, const
  mxArray *plhs[2]);
extern void motor_gen_atexit(void);
extern void motor_gen_initialize(void);
extern void motor_gen_terminate(void);
extern void motor_gen_xil_shutdown(void);
extern void motor_gen_xil_terminate(void);

#endif

/*
 * File trailer for _coder_motor_gen_api.h
 *
 * [EOF]
 */
