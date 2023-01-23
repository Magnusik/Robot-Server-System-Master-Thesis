/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: _coder_motor_gen_info.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 02-Nov-2020 15:59:07
 */

/* Include Files */
#include "_coder_motor_gen_info.h"
#include "emlrt.h"
#include "tmwtypes.h"

/* Function Declarations */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void);

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
static const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char * data[8] = {
    "789ced595d6fd250183e98cd18934dbc5013cde2c7ed12ce609b21de3104866303853192c5cc7e1c68b1a7a76b8b6ede6c893fc0dbfd002ff44eefbcf00778e3"
    "ddfc39185bcad90e1db50cb06ea46f52da9787739ef7a3e7e9490191fc7a0400306b1d73d671f408746cc63ade5b40d471c115d06b6e3cd23d5f65fc39e6f7d3",
    "600ab40f9c7114b7c77fe8fa02514db4673a8eca6174325224585639d5acec6b08e8c820ca1b247690baaca08a8c519975366c0f6719e8c4b121fb3a2d21e175"
    "b985812e19a7112aacd3a9876d474cbebf0f4ef39dea530f16a7f55872e54b2deac2b7332fd34f604e36575b3c2ce9a4890433b19058803a21265c2726d1774c",
    "649810772e1b488d611aa73defde8871def48993e2082b3bd8b48a69ec4848d190defd9ec6f16ac838dce6150735caf76d483e3a75d9878fe2dbf942add322ab"
    "370d9dc30fec1bc980eba94a21b5025fd8ade2a04988c2933d6815092a320f31672a1c0f8966c0337573dae75bb71b03e6c19ed93c66c0b5ceba9b167f45bcf8",
    "da3e7ced21f800163e05cad7b5ffc5c7aebfb6cf7dd88fefb6075fd4857364515b2d35a5c562fd713357c8258c3ac2e9d3384a3e3c7e7100c667e3086a7e763d"
    "0f53c78bb29e0f47cce39e4f1e1417886871cbd6c35357392526714645e754432306ea89e7d588f14c317e6f3c0e22489ccef28ddac78a4ffe143f771fed63be",
    "5335384fcb06d9b2f53e57bdea362e1dc9ce06abcb8782b384435d1e8cef96075fd48517f3a9645c528b5bcfb1c6d7d2956ab29ade05a12e4f9a2ecf317ebf3c"
    "28eed2e506324f04a6a881cbabcb559ffc293e1e5dee2d9bddca5097c7c347edb2eaf2a0fbe572bd20a2ad6625b36ca05c7c93af4ac6e66eb85fbe70eb79d4fb",
    "e18e4f1e1477e9b22c22d594cdfd91f5d86d5e7150a37c5f86e4a3539718bf1f1fc5c7d33f5aae180e4a37bed6027e6ff1f1e771a07c5d9b741d1693eab3a6ba"
    "24d5d6961ad9b7712e535e29c53393a3c33f3cc60f5a47ce63fea80bff07fbe38702c198a83b82fd5a9cbe031fd77ef9be4f5e1477ebb2b1d2921533af6eb430",
    "d265616cfb65f6ff89de781c44242d5e41e3eb6bc3277f8a9fabaf86b5a9472274d4d9f9b4db7c56ae5d55b41eb841e94cecf371b0fbe7eb77bf07c9476dd275"
    "fbdd8226af1919a1f8b42467a5e54a32c52f1743dd0e75bb7b0e4ab7a73de371102b82c5040875db2faf50b71d0b75fbef3c7e7100c60f52b7ff00f5d482af",
    "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(&data[0], 8880U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/*
 * Arguments    : void
 * Return Type  : mxArray *
 */
mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * epFieldName[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * propFieldName[4] = { "Version", "ResolvedFunctions",
    "EntryPoints", "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, epFieldName);
  xInputs = emlrtCreateLogicalMatrix(1, 2);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("motor_gen"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (2.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "C:\\GitHub\\Project2020\\root\\Motor_test\\motor_gen.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (738097.66513888887));
  xResult = emlrtCreateStructMatrix(1, 1, 4, propFieldName);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.8.0.1451342 (R2020a) Update 5"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_motor_gen_info.c
 *
 * [EOF]
 */
