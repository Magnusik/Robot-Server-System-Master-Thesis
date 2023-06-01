/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_controller_api_mex.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 01-Jun-2023 13:20:00
 */

/* Include Files */
#include "_coder_controller_api_mex.h"
#include "_coder_controller_api_api.h"

/* Function Definitions */
/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[]
 *                int32_T nrhs
 *                const mxArray *prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&controller_api_atexit);
  /* Module initialization. */
  controller_api_initialize();
  /* Dispatch the entry-point. */
  unsafe_controller_api_mexFunction(nlhs, plhs, nrhs, prhs);
  /* Module termination. */
  controller_api_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL, (const char_T *)"windows-1252", true);
  return emlrtRootTLSGlobal;
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[10]
 *                int32_T nrhs
 *                const mxArray *prhs[17]
 * Return Type  : void
 */
void unsafe_controller_api_mexFunction(int32_T nlhs, mxArray *plhs[10],
                                       int32_T nrhs, const mxArray *prhs[17])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs[10];
  int32_T b_nlhs;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 17) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 17, 4,
                        14, "controller_api");
  }
  if (nlhs > 10) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 14,
                        "controller_api");
  }
  /* Call the function. */
  controller_api_api(prhs, nlhs, outputs);
  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }
  emlrtReturnArrays(b_nlhs, &plhs[0], &outputs[0]);
}

/*
 * File trailer for _coder_controller_api_mex.c
 *
 * [EOF]
 */
