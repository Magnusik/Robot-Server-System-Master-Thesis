/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_controllerApi_mex.c
 *
 * MATLAB Coder version            : 5.4
 * C/C++ source code generated on  : 03-May-2023 10:29:10
 */

/* Include Files */
#include "_coder_controllerApi_mex.h"
#include "_coder_controllerApi_api.h"

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
  mexAtExit(&controllerApi_atexit);
  /* Module initialization. */
  controllerApi_initialize();
  /* Dispatch the entry-point. */
  unsafe_controllerApi_mexFunction(nlhs, plhs, nrhs, prhs);
  /* Module termination. */
  controllerApi_terminate();
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
 *                mxArray *plhs[9]
 *                int32_T nrhs
 *                const mxArray *prhs[16]
 * Return Type  : void
 */
void unsafe_controllerApi_mexFunction(int32_T nlhs, mxArray *plhs[9],
                                      int32_T nrhs, const mxArray *prhs[16])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs[9];
  int32_T b_nlhs;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 16) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 16, 4,
                        13, "controllerApi");
  }
  if (nlhs > 9) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 13,
                        "controllerApi");
  }
  /* Call the function. */
  controllerApi_api(prhs, nlhs, outputs);
  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    b_nlhs = 1;
  } else {
    b_nlhs = nlhs;
  }
  emlrtReturnArrays(b_nlhs, &plhs[0], &outputs[0]);
}

/*
 * File trailer for _coder_controllerApi_mex.c
 *
 * [EOF]
 */
