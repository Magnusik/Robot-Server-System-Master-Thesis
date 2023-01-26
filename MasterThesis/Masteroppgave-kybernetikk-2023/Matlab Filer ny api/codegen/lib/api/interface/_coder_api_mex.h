/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_api_mex.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 26-Jan-2023 17:44:44
 */

#ifndef _CODER_API_MEX_H
#define _CODER_API_MEX_H

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

void unsafe_api_mexFunction(int32_T nlhs, mxArray *plhs[8], int32_T nrhs,
                            const mxArray *prhs[11]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_api_mex.h
 *
 * [EOF]
 */
