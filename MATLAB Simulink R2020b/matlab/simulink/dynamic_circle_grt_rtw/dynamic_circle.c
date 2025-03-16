/*
 * dynamic_circle.c
 *
 * Code generation for model "dynamic_circle".
 *
 * Model version              : 7.32
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Sat Apr  6 17:58:08 2024
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-32 (Windows32)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "dynamic_circle.h"
#include "dynamic_circle_private.h"

/* Block signals (default storage) */
B_dynamic_circle_T dynamic_circle_B;

/* Continuous states */
X_dynamic_circle_T dynamic_circle_X;

/* Block states (default storage) */
DW_dynamic_circle_T dynamic_circle_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_dynamic_circle_T dynamic_circle_Y;

/* Real-time model */
static RT_MODEL_dynamic_circle_T dynamic_circle_M_;
RT_MODEL_dynamic_circle_T *const dynamic_circle_M = &dynamic_circle_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  dynamic_circle_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  dynamic_circle_step();
  dynamic_circle_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  dynamic_circle_step();
  dynamic_circle_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void dynamic_circle_step(void)
{
  if (rtmIsMajorTimeStep(dynamic_circle_M)) {
    /* set solver stop time */
    if (!(dynamic_circle_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&dynamic_circle_M->solverInfo,
                            ((dynamic_circle_M->Timing.clockTickH0 + 1) *
        dynamic_circle_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&dynamic_circle_M->solverInfo,
                            ((dynamic_circle_M->Timing.clockTick0 + 1) *
        dynamic_circle_M->Timing.stepSize0 +
        dynamic_circle_M->Timing.clockTickH0 *
        dynamic_circle_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(dynamic_circle_M)) {
    dynamic_circle_M->Timing.t[0] = rtsiGetT(&dynamic_circle_M->solverInfo);
  }

  {
    static const real_T b_a[9] = { 0.0055987558320373249, -0.0, 0.0, -0.0,
      0.0055987558320373249, -0.0, -0.0, -0.0, 0.014814814814814815 };

    static const real_T b_b[9] = { 178.61111111111111, 0.0, 0.0, 0.0,
      178.61111111111111, 0.0, 0.0, 0.0, 67.5 };

    static const real_T b[4] = { -0.6, 0.6, 0.6, -0.6 };

    static const int8_T a[9] = { 4, 0, 0, 0, 4, 0, 0, 0, 4 };

    real_T B[12];
    real_T y_tmp[12];
    real_T y_tmp_0[12];
    real_T x[9];
    real_T y[9];
    real_T rtb_Saturation[4];
    real_T rtb_Derivative2[3];
    real_T rtb_Derivative2_0[3];
    real_T tmp[3];
    real_T (*lastU)[3];
    real_T B_tmp;
    real_T B_tmp_0;
    real_T B_tmp_1;
    real_T absx21;
    real_T absx31;
    real_T rtb_Derivative_idx_0;
    real_T rtb_Derivative_idx_1;
    real_T rtb_Derivative_idx_2;
    real_T tmp_0;
    real_T tmp_1;
    real_T tmp_2;
    real_T w1;
    real_T w2;
    real_T w3;
    real_T xm;
    real_T ym;
    int32_T itmp;
    int32_T p1;
    int32_T p2;
    int32_T p3;

    /* Sin: '<Root>/Sine Wave1' incorporates:
     *  Sin: '<Root>/Sine Wave'
     */
    w1 = 0.41887902047863906 * dynamic_circle_M->Timing.t[0];

    /* Sin: '<Root>/Sine Wave1' */
    dynamic_circle_B.SineWave1 = -sin(w1 + 1.5707963267948966);

    /* Sin: '<Root>/Sine Wave' */
    dynamic_circle_B.SineWave = sin(w1);

    /* Derivative: '<S1>/Derivative1' incorporates:
     *  Derivative: '<S1>/Derivative'
     *  Derivative: '<S1>/Derivative2'
     */
    w1 = dynamic_circle_M->Timing.t[0];
    if ((dynamic_circle_DW.TimeStampA >= w1) && (dynamic_circle_DW.TimeStampB >=
         w1)) {
      /* Derivative: '<S1>/Derivative1' */
      dynamic_circle_B.Derivative1[0] = 0.0;
      dynamic_circle_B.Derivative1[1] = 0.0;
      dynamic_circle_B.Derivative1[2] = 0.0;
    } else {
      w2 = dynamic_circle_DW.TimeStampA;
      lastU = &dynamic_circle_DW.LastUAtTimeA;
      if (dynamic_circle_DW.TimeStampA < dynamic_circle_DW.TimeStampB) {
        if (dynamic_circle_DW.TimeStampB < w1) {
          w2 = dynamic_circle_DW.TimeStampB;
          lastU = &dynamic_circle_DW.LastUAtTimeB;
        }
      } else {
        if (dynamic_circle_DW.TimeStampA >= w1) {
          w2 = dynamic_circle_DW.TimeStampB;
          lastU = &dynamic_circle_DW.LastUAtTimeB;
        }
      }

      w2 = w1 - w2;

      /* Derivative: '<S1>/Derivative1' incorporates:
       *  Constant: '<Root>/Constant'
       */
      dynamic_circle_B.Derivative1[0] = (dynamic_circle_B.SineWave1 - (*lastU)[0])
        / w2;
      dynamic_circle_B.Derivative1[1] = (dynamic_circle_B.SineWave - (*lastU)[1])
        / w2;
      dynamic_circle_B.Derivative1[2] = (0.0 - (*lastU)[2]) / w2;
    }

    /* End of Derivative: '<S1>/Derivative1' */

    /* Derivative: '<S1>/Derivative2' */
    if ((dynamic_circle_DW.TimeStampA_m >= w1) &&
        (dynamic_circle_DW.TimeStampB_i >= w1)) {
      rtb_Derivative2[0] = 0.0;
      rtb_Derivative2[1] = 0.0;
      rtb_Derivative2[2] = 0.0;
    } else {
      w2 = dynamic_circle_DW.TimeStampA_m;
      lastU = &dynamic_circle_DW.LastUAtTimeA_d;
      if (dynamic_circle_DW.TimeStampA_m < dynamic_circle_DW.TimeStampB_i) {
        if (dynamic_circle_DW.TimeStampB_i < w1) {
          w2 = dynamic_circle_DW.TimeStampB_i;
          lastU = &dynamic_circle_DW.LastUAtTimeB_o;
        }
      } else {
        if (dynamic_circle_DW.TimeStampA_m >= w1) {
          w2 = dynamic_circle_DW.TimeStampB_i;
          lastU = &dynamic_circle_DW.LastUAtTimeB_o;
        }
      }

      w2 = w1 - w2;
      rtb_Derivative2[0] = (dynamic_circle_B.Derivative1[0] - (*lastU)[0]) / w2;
      rtb_Derivative2[1] = (dynamic_circle_B.Derivative1[1] - (*lastU)[1]) / w2;
      rtb_Derivative2[2] = (dynamic_circle_B.Derivative1[2] - (*lastU)[2]) / w2;
    }

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant'
     *  Integrator: '<S2>/Integrator1'
     */
    dynamic_circle_B.Sum[0] = dynamic_circle_B.SineWave1 -
      dynamic_circle_X.Integrator1_CSTATE[0];
    dynamic_circle_B.Sum[1] = dynamic_circle_B.SineWave -
      dynamic_circle_X.Integrator1_CSTATE[1];
    dynamic_circle_B.Sum[2] = 0.0 - dynamic_circle_X.Integrator1_CSTATE[2];

    /* Derivative: '<S1>/Derivative' */
    if ((dynamic_circle_DW.TimeStampA_o >= w1) &&
        (dynamic_circle_DW.TimeStampB_g >= w1)) {
      rtb_Derivative_idx_0 = 0.0;
      rtb_Derivative_idx_1 = 0.0;
      rtb_Derivative_idx_2 = 0.0;
    } else {
      w2 = dynamic_circle_DW.TimeStampA_o;
      lastU = &dynamic_circle_DW.LastUAtTimeA_k;
      if (dynamic_circle_DW.TimeStampA_o < dynamic_circle_DW.TimeStampB_g) {
        if (dynamic_circle_DW.TimeStampB_g < w1) {
          w2 = dynamic_circle_DW.TimeStampB_g;
          lastU = &dynamic_circle_DW.LastUAtTimeB_on;
        }
      } else {
        if (dynamic_circle_DW.TimeStampA_o >= w1) {
          w2 = dynamic_circle_DW.TimeStampB_g;
          lastU = &dynamic_circle_DW.LastUAtTimeB_on;
        }
      }

      w2 = w1 - w2;
      rtb_Derivative_idx_0 = (dynamic_circle_B.Sum[0] - (*lastU)[0]) / w2;
      rtb_Derivative_idx_1 = (dynamic_circle_B.Sum[1] - (*lastU)[1]) / w2;
      rtb_Derivative_idx_2 = (dynamic_circle_B.Sum[2] - (*lastU)[2]) / w2;
    }

    /* Integrator: '<S2>/Integrator' */
    dynamic_circle_B.Integrator[0] = dynamic_circle_X.Integrator_CSTATE[0];
    dynamic_circle_B.Integrator[1] = dynamic_circle_X.Integrator_CSTATE[1];
    dynamic_circle_B.Integrator[2] = dynamic_circle_X.Integrator_CSTATE[2];

    /* MATLAB Function: '<S1>/control' incorporates:
     *  Integrator: '<S2>/Integrator1'
     *  MATLAB Function: '<S2>/robot'
     */
    w1 = cos(dynamic_circle_X.Integrator1_CSTATE[2]);
    w2 = sin(dynamic_circle_X.Integrator1_CSTATE[2]);
    B[0] = (w1 + w2) * 20.833333333333332;
    B[3] = (w1 - w2) * 20.833333333333332;
    B_tmp = (cos(dynamic_circle_X.Integrator1_CSTATE[2]) + sin
             (dynamic_circle_X.Integrator1_CSTATE[2])) * 20.833333333333332;
    B[6] = B_tmp;
    B_tmp_0 = (cos(dynamic_circle_X.Integrator1_CSTATE[2]) - sin
               (dynamic_circle_X.Integrator1_CSTATE[2])) * 20.833333333333332;
    B[9] = B_tmp_0;
    B[1] = (-w1 + w2) * 20.833333333333332;
    B[4] = B_tmp;
    B_tmp_1 = (-cos(dynamic_circle_X.Integrator1_CSTATE[2]) + sin
               (dynamic_circle_X.Integrator1_CSTATE[2])) * 20.833333333333332;
    B[7] = B_tmp_1;
    B[10] = B_tmp;
    B[2] = -12.499999999999998;
    B[5] = 12.499999999999998;
    B[8] = 12.499999999999998;
    B[11] = -12.499999999999998;
    xm = w1 * dynamic_circle_B.Integrator[0] + w2 * dynamic_circle_B.Integrator
      [1];
    ym = -w2 * dynamic_circle_B.Integrator[0] + w1 *
      dynamic_circle_B.Integrator[1];
    w3 = xm - ym;
    w1 = (w3 - 0.6 * dynamic_circle_B.Integrator[2]) * 20.833333333333332;
    xm += ym;
    w2 = (xm + 0.6 * dynamic_circle_B.Integrator[2]) * 20.833333333333332;
    w3 = (w3 + 0.6 * dynamic_circle_B.Integrator[2]) * 20.833333333333332;
    xm = (xm - 0.6 * dynamic_circle_B.Integrator[2]) * 20.833333333333332;
    if (w1 > 20.833333333333332) {
      w1 = 20.833333333333332;
    } else {
      if (w1 < -20.833333333333332) {
        w1 = -20.833333333333332;
      }
    }

    if (w2 > 20.833333333333332) {
      w2 = 20.833333333333332;
    } else {
      if (w2 < -20.833333333333332) {
        w2 = -20.833333333333332;
      }
    }

    if (w3 > 20.833333333333332) {
      w3 = 20.833333333333332;
    } else {
      if (w3 < -20.833333333333332) {
        w3 = -20.833333333333332;
      }
    }

    if (xm > 20.833333333333332) {
      xm = 20.833333333333332;
    } else {
      if (xm < -20.833333333333332) {
        xm = -20.833333333333332;
      }
    }

    for (p1 = 0; p1 < 3; p1++) {
      p3 = p1 << 2;
      y_tmp[p3] = B[p1];
      y_tmp[p3 + 1] = B[p1 + 3];
      y_tmp[p3 + 2] = B[p1 + 6];
      y_tmp[p3 + 3] = B[p1 + 9];
      for (p2 = 0; p2 < 3; p2++) {
        itmp = p2 + 3 * p1;
        y[itmp] = 0.0;
        y[itmp] += y_tmp[p3] * B[p2];
        y[itmp] += y_tmp[p3 + 1] * B[p2 + 3];
        y[itmp] += y_tmp[p3 + 2] * B[p2 + 6];
        y[itmp] += y_tmp[p3 + 3] * B[p2 + 9];
      }
    }

    memcpy(&x[0], &y[0], 9U * sizeof(real_T));
    p1 = 0;
    p2 = 3;
    p3 = 6;
    ym = fabs(y[0]);
    absx21 = fabs(y[1]);
    absx31 = fabs(y[2]);
    if ((absx21 > ym) && (absx21 > absx31)) {
      p1 = 3;
      p2 = 0;
      x[0] = y[1];
      x[1] = y[0];
      x[3] = y[4];
      x[4] = y[3];
      x[6] = y[7];
      x[7] = y[6];
    } else {
      if (absx31 > ym) {
        p1 = 6;
        p3 = 0;
        x[0] = y[2];
        x[2] = y[0];
        x[3] = y[5];
        x[5] = y[3];
        x[6] = y[8];
        x[8] = y[6];
      }
    }

    absx31 = x[1] / x[0];
    x[1] = absx31;
    absx21 = x[2] / x[0];
    x[2] = absx21;
    x[4] -= absx31 * x[3];
    x[5] -= absx21 * x[3];
    x[7] -= absx31 * x[6];
    x[8] -= absx21 * x[6];
    if (fabs(x[5]) > fabs(x[4])) {
      itmp = p2;
      p2 = p3;
      p3 = itmp;
      x[1] = absx21;
      x[2] = absx31;
      ym = x[4];
      x[4] = x[5];
      x[5] = ym;
      ym = x[7];
      x[7] = x[8];
      x[8] = ym;
    }

    absx31 = x[5] / x[4];
    x[8] -= absx31 * x[7];
    ym = (absx31 * x[1] - x[2]) / x[8];
    absx21 = -(x[7] * ym + x[1]) / x[4];
    y[p1] = ((1.0 - x[3] * absx21) - x[6] * ym) / x[0];
    y[p1 + 1] = absx21;
    y[p1 + 2] = ym;
    ym = -absx31 / x[8];
    absx21 = (1.0 - x[7] * ym) / x[4];
    y[p2] = -(x[3] * absx21 + x[6] * ym) / x[0];
    y[p2 + 1] = absx21;
    y[p2 + 2] = ym;
    ym = 1.0 / x[8];
    absx21 = -x[7] * ym / x[4];
    y[p3] = -(x[3] * absx21 + x[6] * ym) / x[0];
    y[p3 + 1] = absx21;
    y[p3 + 2] = ym;
    for (p1 = 0; p1 < 9; p1++) {
      x[p1] = a[p1];
    }

    for (p1 = 0; p1 < 3; p1++) {
      for (p2 = 0; p2 < 4; p2++) {
        p3 = p2 + (p1 << 2);
        y_tmp_0[p3] = 0.0;
        y_tmp_0[p3] += y[3 * p1] * y_tmp[p2];
        y_tmp_0[p3] += y[3 * p1 + 1] * y_tmp[p2 + 4];
        y_tmp_0[p3] += y[3 * p1 + 2] * y_tmp[p2 + 8];
      }
    }

    absx21 = 178.61111111111111 * dynamic_circle_B.Integrator[1] *
      dynamic_circle_B.Integrator[2];
    absx31 = -178.61111111111111 * dynamic_circle_B.Integrator[0] *
      dynamic_circle_B.Integrator[2];
    if (w1 < 0.0) {
      w1 = -1.0;
    } else if (w1 > 0.0) {
      w1 = 1.0;
    } else if (w1 == 0.0) {
      w1 = 0.0;
    } else {
      w1 = (rtNaN);
    }

    ym = 0.00588 * w1;
    if (w2 < 0.0) {
      w2 = -1.0;
    } else if (w2 > 0.0) {
      w2 = 1.0;
    } else if (w2 == 0.0) {
      w2 = 0.0;
    } else {
      w2 = (rtNaN);
    }

    tmp_0 = 0.00588 * w2;
    if (w3 < 0.0) {
      w3 = -1.0;
    } else if (w3 > 0.0) {
      w3 = 1.0;
    } else if (w3 == 0.0) {
      w3 = 0.0;
    } else {
      w3 = (rtNaN);
    }

    tmp_1 = 0.00588 * w3;
    if (xm < 0.0) {
      xm = -1.0;
    } else if (xm > 0.0) {
      xm = 1.0;
    } else if (xm == 0.0) {
      xm = 0.0;
    } else {
      xm = (rtNaN);
    }

    tmp_2 = 0.00588 * xm;
    for (p1 = 0; p1 < 3; p1++) {
      w1 = b_a[p1 + 3];
      w2 = b_a[p1 + 6];
      for (p2 = 0; p2 < 4; p2++) {
        p3 = p1 + 3 * p2;
        y_tmp[p3] = 0.0;
        y_tmp[p3] += B[3 * p2] * b_a[p1];
        y_tmp[p3] += B[3 * p2 + 1] * w1;
        y_tmp[p3] += B[3 * p2 + 2] * w2;
      }

      /* MATLAB Function: '<S1>/x2r' */
      tmp[p1] = ((((real_T)a[p1 + 3] * dynamic_circle_B.Sum[1] + (real_T)a[p1] *
                   dynamic_circle_B.Sum[0]) + (real_T)a[p1 + 6] *
                  dynamic_circle_B.Sum[2]) + dynamic_circle_B.Derivative1[p1]) -
        dynamic_circle_B.Integrator[p1];
      rtb_Derivative2_0[p1] = ((((x[p1 + 3] * rtb_Derivative_idx_1 + x[p1] *
        rtb_Derivative_idx_0) + x[p1 + 6] * rtb_Derivative_idx_2) +
        rtb_Derivative2[p1]) + (w2 * 0.0 + (w1 * absx31 + b_a[p1] * absx21))) +
        (((y_tmp[p1 + 3] * tmp_0 + y_tmp[p1] * ym) + y_tmp[p1 + 6] * tmp_1) +
         y_tmp[p1 + 9] * tmp_2);
    }

    for (p1 = 0; p1 < 3; p1++) {
      for (p2 = 0; p2 < 4; p2++) {
        p3 = p2 + (p1 << 2);
        y_tmp[p3] = 0.0;
        y_tmp[p3] += b_b[3 * p1] * y_tmp_0[p2];
        y_tmp[p3] += b_b[3 * p1 + 1] * y_tmp_0[p2 + 4];
        y_tmp[p3] += b_b[3 * p1 + 2] * y_tmp_0[p2 + 8];
      }

      rtb_Derivative2[p1] = x[p1 + 6] * tmp[2] + (x[p1 + 3] * tmp[1] + x[p1] *
        tmp[0]);
    }

    w1 = rtb_Derivative2_0[0] + rtb_Derivative2[0];
    w2 = rtb_Derivative2_0[1] + rtb_Derivative2[1];
    xm = rtb_Derivative2_0[2] + rtb_Derivative2[2];

    /* MATLAB Function: '<S2>/robot' */
    B[0] = B_tmp;
    B[3] = B_tmp_0;
    B[6] = B_tmp;
    B[9] = B_tmp_0;
    B[1] = B_tmp_1;
    B[4] = B_tmp;
    B[7] = B_tmp_1;
    B[10] = B_tmp;
    for (p1 = 0; p1 < 4; p1++) {
      /* MATLAB Function: '<S1>/control' */
      w3 = y_tmp[p1 + 8] * xm + (y_tmp[p1 + 4] * w2 + y_tmp[p1] * w1);

      /* Saturate: '<Root>/Saturation' */
      if (w3 > 100.0) {
        rtb_Saturation[p1] = 100.0;
      } else if (w3 < -100.0) {
        rtb_Saturation[p1] = -100.0;
      } else {
        rtb_Saturation[p1] = w3;
      }

      /* End of Saturate: '<Root>/Saturation' */

      /* MATLAB Function: '<S2>/robot' */
      B[3 * p1 + 2] = 20.833333333333332 * b[p1];
    }

    /* MATLAB Function: '<S2>/robot' incorporates:
     *  Integrator: '<S2>/Integrator1'
     */
    xm = cos(dynamic_circle_X.Integrator1_CSTATE[2]) *
      dynamic_circle_B.Integrator[0] + sin(dynamic_circle_X.Integrator1_CSTATE[2])
      * dynamic_circle_B.Integrator[1];
    ym = -sin(dynamic_circle_X.Integrator1_CSTATE[2]) *
      dynamic_circle_B.Integrator[0] + cos(dynamic_circle_X.Integrator1_CSTATE[2])
      * dynamic_circle_B.Integrator[1];
    w3 = xm - ym;
    w1 = (w3 - 0.6 * dynamic_circle_B.Integrator[2]) * 20.833333333333332;
    xm += ym;
    w2 = (xm + 0.6 * dynamic_circle_B.Integrator[2]) * 20.833333333333332;
    w3 = (w3 + 0.6 * dynamic_circle_B.Integrator[2]) * 20.833333333333332;
    xm = (xm - 0.6 * dynamic_circle_B.Integrator[2]) * 20.833333333333332;
    if (w1 > 15.707963267948966) {
      w1 = 15.707963267948966;
    } else {
      if (w1 < -15.707963267948966) {
        w1 = -15.707963267948966;
      }
    }

    if (w2 > 15.707963267948966) {
      w2 = 15.707963267948966;
    } else {
      if (w2 < -15.707963267948966) {
        w2 = -15.707963267948966;
      }
    }

    if (w3 > 15.707963267948966) {
      w3 = 15.707963267948966;
    } else {
      if (w3 < -15.707963267948966) {
        w3 = -15.707963267948966;
      }
    }

    if (xm > 15.707963267948966) {
      xm = 15.707963267948966;
    } else {
      if (xm < -15.707963267948966) {
        xm = -15.707963267948966;
      }
    }

    B_tmp = rtb_Saturation[0];
    B_tmp_0 = rtb_Saturation[1];
    B_tmp_1 = rtb_Saturation[2];
    rtb_Derivative_idx_0 = rtb_Saturation[3];
    tmp[0] = absx21;
    tmp[1] = absx31;
    tmp[2] = 0.0;
    if (w1 < 0.0) {
      absx21 = -1.0;
    } else if (w1 > 0.0) {
      absx21 = 1.0;
    } else if (w1 == 0.0) {
      absx21 = 0.0;
    } else {
      absx21 = (rtNaN);
    }

    ym = 0.00588 * absx21;
    if (w2 < 0.0) {
      absx21 = -1.0;
    } else if (w2 > 0.0) {
      absx21 = 1.0;
    } else if (w2 == 0.0) {
      absx21 = 0.0;
    } else {
      absx21 = (rtNaN);
    }

    tmp_0 = 0.00588 * absx21;
    if (w3 < 0.0) {
      absx21 = -1.0;
    } else if (w3 > 0.0) {
      absx21 = 1.0;
    } else if (w3 == 0.0) {
      absx21 = 0.0;
    } else {
      absx21 = (rtNaN);
    }

    tmp_1 = 0.00588 * absx21;
    if (xm < 0.0) {
      absx21 = -1.0;
    } else if (xm > 0.0) {
      absx21 = 1.0;
    } else if (xm == 0.0) {
      absx21 = 0.0;
    } else {
      absx21 = (rtNaN);
    }

    tmp_2 = 0.00588 * absx21;
    for (p1 = 0; p1 < 3; p1++) {
      absx21 = B[p1];
      absx31 = absx21 * ym;
      rtb_Derivative_idx_1 = absx21 * B_tmp;
      absx21 = B[p1 + 3];
      absx31 += absx21 * tmp_0;
      rtb_Derivative_idx_1 += absx21 * B_tmp_0;
      absx21 = B[p1 + 6];
      absx31 += absx21 * tmp_1;
      rtb_Derivative_idx_1 += absx21 * B_tmp_1;
      absx21 = B[p1 + 9];
      absx31 += absx21 * tmp_2;
      rtb_Derivative_idx_1 += absx21 * rtb_Derivative_idx_0;
      rtb_Derivative2_0[p1] = (rtb_Derivative_idx_1 - tmp[p1]) - absx31;
    }

    for (p1 = 0; p1 < 3; p1++) {
      dynamic_circle_B.Q_2dot[p1] = 0.0;
      dynamic_circle_B.Q_2dot[p1] += b_a[p1] * rtb_Derivative2_0[0];
      dynamic_circle_B.Q_2dot[p1] += b_a[p1 + 3] * rtb_Derivative2_0[1];
      dynamic_circle_B.Q_2dot[p1] += b_a[p1 + 6] * rtb_Derivative2_0[2];
    }

    /* Outport: '<Root>/w1' incorporates:
     *  MATLAB Function: '<S2>/robot'
     */
    dynamic_circle_Y.w1 = w1;

    /* Outport: '<Root>/w2' incorporates:
     *  MATLAB Function: '<S2>/robot'
     */
    dynamic_circle_Y.w2 = w2;

    /* Outport: '<Root>/w3' incorporates:
     *  MATLAB Function: '<S2>/robot'
     */
    dynamic_circle_Y.w3 = w3;

    /* Outport: '<Root>/w4' incorporates:
     *  MATLAB Function: '<S2>/robot'
     */
    dynamic_circle_Y.w4 = xm;
  }

  if (rtmIsMajorTimeStep(dynamic_circle_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(dynamic_circle_M->rtwLogInfo,
                        (dynamic_circle_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(dynamic_circle_M)) {
    real_T (*lastU)[3];

    /* Update for Derivative: '<S1>/Derivative1' incorporates:
     *  Constant: '<Root>/Constant'
     */
    if (dynamic_circle_DW.TimeStampA == (rtInf)) {
      dynamic_circle_DW.TimeStampA = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeA;
    } else if (dynamic_circle_DW.TimeStampB == (rtInf)) {
      dynamic_circle_DW.TimeStampB = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeB;
    } else if (dynamic_circle_DW.TimeStampA < dynamic_circle_DW.TimeStampB) {
      dynamic_circle_DW.TimeStampA = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeA;
    } else {
      dynamic_circle_DW.TimeStampB = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeB;
    }

    (*lastU)[0] = dynamic_circle_B.SineWave1;
    (*lastU)[1] = dynamic_circle_B.SineWave;
    (*lastU)[2] = 0.0;

    /* End of Update for Derivative: '<S1>/Derivative1' */

    /* Update for Derivative: '<S1>/Derivative2' */
    if (dynamic_circle_DW.TimeStampA_m == (rtInf)) {
      dynamic_circle_DW.TimeStampA_m = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeA_d;
    } else if (dynamic_circle_DW.TimeStampB_i == (rtInf)) {
      dynamic_circle_DW.TimeStampB_i = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeB_o;
    } else if (dynamic_circle_DW.TimeStampA_m < dynamic_circle_DW.TimeStampB_i)
    {
      dynamic_circle_DW.TimeStampA_m = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeA_d;
    } else {
      dynamic_circle_DW.TimeStampB_i = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeB_o;
    }

    (*lastU)[0] = dynamic_circle_B.Derivative1[0];
    (*lastU)[1] = dynamic_circle_B.Derivative1[1];
    (*lastU)[2] = dynamic_circle_B.Derivative1[2];

    /* End of Update for Derivative: '<S1>/Derivative2' */

    /* Update for Derivative: '<S1>/Derivative' */
    if (dynamic_circle_DW.TimeStampA_o == (rtInf)) {
      dynamic_circle_DW.TimeStampA_o = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeA_k;
    } else if (dynamic_circle_DW.TimeStampB_g == (rtInf)) {
      dynamic_circle_DW.TimeStampB_g = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeB_on;
    } else if (dynamic_circle_DW.TimeStampA_o < dynamic_circle_DW.TimeStampB_g)
    {
      dynamic_circle_DW.TimeStampA_o = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeA_k;
    } else {
      dynamic_circle_DW.TimeStampB_g = dynamic_circle_M->Timing.t[0];
      lastU = &dynamic_circle_DW.LastUAtTimeB_on;
    }

    (*lastU)[0] = dynamic_circle_B.Sum[0];
    (*lastU)[1] = dynamic_circle_B.Sum[1];
    (*lastU)[2] = dynamic_circle_B.Sum[2];

    /* End of Update for Derivative: '<S1>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(dynamic_circle_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(dynamic_circle_M)!=-1) &&
          !((rtmGetTFinal(dynamic_circle_M)-
             (((dynamic_circle_M->Timing.clockTick1+
                dynamic_circle_M->Timing.clockTickH1* 4294967296.0)) * 0.1)) >
            (((dynamic_circle_M->Timing.clockTick1+
               dynamic_circle_M->Timing.clockTickH1* 4294967296.0)) * 0.1) *
            (DBL_EPSILON))) {
        rtmSetErrorStatus(dynamic_circle_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&dynamic_circle_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++dynamic_circle_M->Timing.clockTick0)) {
      ++dynamic_circle_M->Timing.clockTickH0;
    }

    dynamic_circle_M->Timing.t[0] = rtsiGetSolverStopTime
      (&dynamic_circle_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.1s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.1, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      dynamic_circle_M->Timing.clockTick1++;
      if (!dynamic_circle_M->Timing.clockTick1) {
        dynamic_circle_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void dynamic_circle_derivatives(void)
{
  XDot_dynamic_circle_T *_rtXdot;
  _rtXdot = ((XDot_dynamic_circle_T *) dynamic_circle_M->derivs);

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = dynamic_circle_B.Integrator[0];

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = dynamic_circle_B.Q_2dot[0];

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[1] = dynamic_circle_B.Integrator[1];

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[1] = dynamic_circle_B.Q_2dot[1];

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[2] = dynamic_circle_B.Integrator[2];

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[2] = dynamic_circle_B.Q_2dot[2];
}

/* Model initialize function */
void dynamic_circle_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)dynamic_circle_M, 0,
                sizeof(RT_MODEL_dynamic_circle_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&dynamic_circle_M->solverInfo,
                          &dynamic_circle_M->Timing.simTimeStep);
    rtsiSetTPtr(&dynamic_circle_M->solverInfo, &rtmGetTPtr(dynamic_circle_M));
    rtsiSetStepSizePtr(&dynamic_circle_M->solverInfo,
                       &dynamic_circle_M->Timing.stepSize0);
    rtsiSetdXPtr(&dynamic_circle_M->solverInfo, &dynamic_circle_M->derivs);
    rtsiSetContStatesPtr(&dynamic_circle_M->solverInfo, (real_T **)
                         &dynamic_circle_M->contStates);
    rtsiSetNumContStatesPtr(&dynamic_circle_M->solverInfo,
      &dynamic_circle_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&dynamic_circle_M->solverInfo,
      &dynamic_circle_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&dynamic_circle_M->solverInfo,
      &dynamic_circle_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&dynamic_circle_M->solverInfo,
      &dynamic_circle_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&dynamic_circle_M->solverInfo, (&rtmGetErrorStatus
      (dynamic_circle_M)));
    rtsiSetRTModelPtr(&dynamic_circle_M->solverInfo, dynamic_circle_M);
  }

  rtsiSetSimTimeStep(&dynamic_circle_M->solverInfo, MAJOR_TIME_STEP);
  dynamic_circle_M->intgData.y = dynamic_circle_M->odeY;
  dynamic_circle_M->intgData.f[0] = dynamic_circle_M->odeF[0];
  dynamic_circle_M->intgData.f[1] = dynamic_circle_M->odeF[1];
  dynamic_circle_M->intgData.f[2] = dynamic_circle_M->odeF[2];
  dynamic_circle_M->contStates = ((X_dynamic_circle_T *) &dynamic_circle_X);
  rtsiSetSolverData(&dynamic_circle_M->solverInfo, (void *)
                    &dynamic_circle_M->intgData);
  rtsiSetSolverName(&dynamic_circle_M->solverInfo,"ode3");
  rtmSetTPtr(dynamic_circle_M, &dynamic_circle_M->Timing.tArray[0]);
  rtmSetTFinal(dynamic_circle_M, 30.0);
  dynamic_circle_M->Timing.stepSize0 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    dynamic_circle_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(dynamic_circle_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(dynamic_circle_M->rtwLogInfo, (NULL));
    rtliSetLogT(dynamic_circle_M->rtwLogInfo, "tout");
    rtliSetLogX(dynamic_circle_M->rtwLogInfo, "");
    rtliSetLogXFinal(dynamic_circle_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(dynamic_circle_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(dynamic_circle_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(dynamic_circle_M->rtwLogInfo, 0);
    rtliSetLogDecimation(dynamic_circle_M->rtwLogInfo, 1);
    rtliSetLogY(dynamic_circle_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(dynamic_circle_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(dynamic_circle_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &dynamic_circle_B), 0,
                sizeof(B_dynamic_circle_T));

  /* states (continuous) */
  {
    (void) memset((void *)&dynamic_circle_X, 0,
                  sizeof(X_dynamic_circle_T));
  }

  /* states (dwork) */
  (void) memset((void *)&dynamic_circle_DW, 0,
                sizeof(DW_dynamic_circle_T));

  /* external outputs */
  (void) memset((void *)&dynamic_circle_Y, 0,
                sizeof(ExtY_dynamic_circle_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(dynamic_circle_M->rtwLogInfo, 0.0,
    rtmGetTFinal(dynamic_circle_M), dynamic_circle_M->Timing.stepSize0,
    (&rtmGetErrorStatus(dynamic_circle_M)));

  /* InitializeConditions for Derivative: '<S1>/Derivative1' */
  dynamic_circle_DW.TimeStampA = (rtInf);
  dynamic_circle_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Derivative: '<S1>/Derivative2' */
  dynamic_circle_DW.TimeStampA_m = (rtInf);
  dynamic_circle_DW.TimeStampB_i = (rtInf);

  /* InitializeConditions for Derivative: '<S1>/Derivative' */
  dynamic_circle_DW.TimeStampA_o = (rtInf);
  dynamic_circle_DW.TimeStampB_g = (rtInf);

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  dynamic_circle_X.Integrator1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  dynamic_circle_X.Integrator_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  dynamic_circle_X.Integrator1_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  dynamic_circle_X.Integrator_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  dynamic_circle_X.Integrator1_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  dynamic_circle_X.Integrator_CSTATE[2] = 0.0;
}

/* Model terminate function */
void dynamic_circle_terminate(void)
{
  /* (no terminate code required) */
}
