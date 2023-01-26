/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_api_api.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 18-Dec-2022 14:05:41
 */

/* Include Files */
#include "_coder_api_api.h"
#include "_coder_api_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;

emlrtContext emlrtContextGlobal = {
    true,                                                 /* bFirstTime */
    false,                                                /* bInitialized */
    131610U,                                              /* fVersionInfo */
    NULL,                                                 /* fErrorFunction */
    "api",                                                /* fFunctionName */
    NULL,                                                 /* fRTCallStack */
    false,                                                /* bDebugMode */
    {2045744189U, 2170104910U, 2743257031U, 4284093946U}, /* fSigWrd */
    NULL                                                  /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId);

static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId);

static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *setpointX,
                               const char_T *identifier);

static const mxArray *emlrt_marshallOut(const real_T u);

/* Function Definitions */
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u,
                                 const emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
                                 const emlrtMsgIdentifier *msgId)
{
  static const int32_T dims = 0;
  real_T ret;
  emlrtCheckBuiltInR2012b((emlrtCTX)sp, msgId, src, (const char_T *)"double",
                          false, 0U, (void *)&dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *setpointX
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *setpointX,
                               const char_T *identifier)
{
  emlrtMsgIdentifier thisId;
  real_T y;
  thisId.fIdentifier = (const char_T *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(setpointX), &thisId);
  emlrtDestroyArray(&setpointX);
  return y;
}

/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *m;
  const mxArray *y;
  y = NULL;
  m = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m);
  return y;
}

/*
 * Arguments    : const mxArray * const prhs[11]
 *                int32_T nlhs
 *                const mxArray *plhs[8]
 * Return Type  : void
 */
void api_api(const mxArray *const prhs[11], int32_T nlhs,
             const mxArray *plhs[8])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  real_T distanceDriven;
  real_T gTheta_hat;
  real_T gX_hat;
  real_T gY_hat;
  real_T leftU;
  real_T newCommand;
  real_T rightU;
  real_T setpointX;
  real_T setpointY;
  real_T thetaprev;
  real_T ticksLeft;
  real_T ticksRight;
  real_T turning;
  real_T waitingCommand;
  real_T xprev;
  real_T yprev;
  st.tls = emlrtRootTLSGlobal;
  /* Marshall function inputs */
  setpointX = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "setpointX");
  setpointY = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "setpointY");
  newCommand = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "newCommand");
  waitingCommand =
      emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "waitingCommand");
  ticksLeft = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "ticksLeft");
  ticksRight = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "ticksRight");
  distanceDriven =
      emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "distanceDriven");
  turning = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "turning");
  xprev = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "xprev");
  yprev = emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "yprev");
  thetaprev = emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "thetaprev");
  /* Invoke the target function */
  api(setpointX, setpointY, newCommand, &waitingCommand, ticksLeft, ticksRight,
      &distanceDriven, &turning, xprev, yprev, thetaprev, &gX_hat, &gY_hat,
      &gTheta_hat, &leftU, &rightU);
  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(gX_hat);
  if (nlhs > 1) {
    plhs[1] = emlrt_marshallOut(gY_hat);
  }
  if (nlhs > 2) {
    plhs[2] = emlrt_marshallOut(gTheta_hat);
  }
  if (nlhs > 3) {
    plhs[3] = emlrt_marshallOut(distanceDriven);
  }
  if (nlhs > 4) {
    plhs[4] = emlrt_marshallOut(leftU);
  }
  if (nlhs > 5) {
    plhs[5] = emlrt_marshallOut(rightU);
  }
  if (nlhs > 6) {
    plhs[6] = emlrt_marshallOut(turning);
  }
  if (nlhs > 7) {
    plhs[7] = emlrt_marshallOut(waitingCommand);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void api_atexit(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  api_xil_terminate();
  api_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void api_initialize(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, NULL);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void api_terminate(void)
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_api_api.c
 *
 * [EOF]
 */