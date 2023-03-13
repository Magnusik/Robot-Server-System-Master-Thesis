/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_controllerApi_mex.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 07-Mar-2023 14:42:23
 */

#ifndef _CODER_CONTROLLERAPI_MEX_H
#define _CODER_CONTROLLERAPI_MEX_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
MEXFUNCTION_LINKAGE void mexFunction(int32_T nlhs, mxArray *plhs[],
                                     int32_T nrhs, const mxArray *prhs[]);

emlrtCTX mexFunctionCreateRootTLS(void);

void unsafe_controllerApi_mexFunction(int32_T nlhs, mxArray *plhs[8],
                                      int32_T nrhs, const mxArray *prhs[14]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_controllerApi_mex.h
 *
 * [EOF]
 */
