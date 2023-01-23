/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: motor_gen.c
 *
 * MATLAB Coder version            : 5.0
 * C/C++ source code generated on  : 02-Nov-2020 15:59:07
 */

/* Include Files */
#include "motor_gen.h"

/* Function Definitions */

/*
 * Arguments    : int v
 *                int h
 *                int *tv
 *                int *th
 * Return Type  : void
 */
void motor_gen(int v, int h, int *tv, int *th)
{
  if (v > 1073741823) {
    *tv = MAX_int32_T;
  } else if (v <= -1073741824) {
    *tv = MIN_int32_T;
  } else {
    *tv = v << 1;
  }

  if (h > 536870911) {
    *th = MAX_int32_T;
  } else if (h <= -536870912) {
    *th = MIN_int32_T;
  } else {
    *th = h << 2;
  }
}

/*
 * File trailer for motor_gen.c
 *
 * [EOF]
 */
