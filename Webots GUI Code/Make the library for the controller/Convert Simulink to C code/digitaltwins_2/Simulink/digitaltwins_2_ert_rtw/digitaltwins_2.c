/*
 * File: digitaltwins_2.c
 *
 * Code generated for Simulink model 'digitaltwins_2'.
 *
 * Model version                  : 7.69
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Sat May 18 01:17:52 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "digitaltwins_2.h"
#include "digitaltwins_2_private.h"

/* Block signals (default storage) */
B_digitaltwins_2_T digitaltwins_2_B;

/* Continuous states */
X_digitaltwins_2_T digitaltwins_2_X;

/* Block states (default storage) */
DW_digitaltwins_2_T digitaltwins_2_DW;

/* External inputs (root inport signals with default storage) */
ExtU_digitaltwins_2_T digitaltwins_2_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_digitaltwins_2_T digitaltwins_2_Y;

/* Real-time model */
static RT_MODEL_digitaltwins_2_T digitaltwins_2_M_;
RT_MODEL_digitaltwins_2_T *const digitaltwins_2_M = &digitaltwins_2_M_;

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
  int_T nXc = 12;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  digitaltwins_2_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  digitaltwins_2_step();
  digitaltwins_2_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  digitaltwins_2_step();
  digitaltwins_2_derivatives();

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
void digitaltwins_2_step(void)
{
  if (rtmIsMajorTimeStep(digitaltwins_2_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&digitaltwins_2_M->solverInfo,
                          ((digitaltwins_2_M->Timing.clockTick0+1)*
      digitaltwins_2_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(digitaltwins_2_M)) {
    digitaltwins_2_M->Timing.t[0] = rtsiGetT(&digitaltwins_2_M->solverInfo);
  }

  {
    static const real_T b_a[9] = { 0.0057126550883552056, -0.0, 0.0, -0.0,
      0.0057126550883552056, -0.0, -0.0, -0.0, 0.015101637923424473 };

    static const real_T b_b[9] = { 175.04995217345095, 0.0, 0.0, 0.0,
      175.04995217345095, 0.0, 0.0, 0.0, 66.217982782442334 };

    static const int8_T a_0[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
      1 };

    static const int8_T a[9] = { 4, 0, 0, 0, 4, 0, 0, 0, 4 };

    static const int8_T a_1[9] = { 10, 0, 0, 0, 10, 0, 0, 0, 10 };

    real_T B[12];
    real_T y_tmp[12];
    real_T y_tmp_0[12];
    real_T x[9];
    real_T y[9];
    real_T Qv_temp[4];
    real_T rtb_u_control_f[4];
    real_T rtb_Derivative2[3];
    real_T rtb_Derivative2_0[3];
    real_T tmp[3];
    real_T x_0[3];
    real_T (*lastU)[3];
    real_T absx11;
    real_T absx21;
    real_T absx31;
    real_T rtb_Derivative_idx_0;
    real_T rtb_Derivative_idx_1;
    real_T rtb_Derivative_idx_2;
    real_T rtb_Derivative_o_idx_0;
    real_T tmp_0;
    real_T w1;
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
    rtb_Derivative_o_idx_0 = digitaltwins_2_M->Timing.t[0];

    /* Sin: '<Root>/Sine Wave1' */
    digitaltwins_2_B.SineWave1 = sin(0.41887902047863906 *
      rtb_Derivative_o_idx_0 + 0.0) * 1.0 + 2.5;

    /* Sin: '<Root>/Sine Wave' */
    digitaltwins_2_B.SineWave = sin(0.83775804095727813 * rtb_Derivative_o_idx_0
      + 0.0) * 1.0 + 3;

    /* Derivative: '<S1>/Derivative1' incorporates:
     *  Derivative: '<S1>/Derivative'
     *  Derivative: '<S1>/Derivative2'
     *  Derivative: '<S7>/Derivative'
     *  Derivative: '<S7>/Derivative1'
     *  Derivative: '<S7>/Derivative2'
     */
    rtb_Derivative_o_idx_0 = digitaltwins_2_M->Timing.t[0];
    if ((digitaltwins_2_DW.TimeStampA >= rtb_Derivative_o_idx_0) &&
        (digitaltwins_2_DW.TimeStampB >= rtb_Derivative_o_idx_0)) {
      /* Derivative: '<S1>/Derivative1' */
      digitaltwins_2_B.Derivative1[0] = 0.0;
      digitaltwins_2_B.Derivative1[1] = 0.0;
      digitaltwins_2_B.Derivative1[2] = 0.0;
    } else {
      w1 = digitaltwins_2_DW.TimeStampA;
      lastU = &digitaltwins_2_DW.LastUAtTimeA;
      if (digitaltwins_2_DW.TimeStampA < digitaltwins_2_DW.TimeStampB) {
        if (digitaltwins_2_DW.TimeStampB < rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB;
          lastU = &digitaltwins_2_DW.LastUAtTimeB;
        }
      } else {
        if (digitaltwins_2_DW.TimeStampA >= rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB;
          lastU = &digitaltwins_2_DW.LastUAtTimeB;
        }
      }

      w1 = rtb_Derivative_o_idx_0 - w1;

      /* Derivative: '<S1>/Derivative1' incorporates:
       *  Constant: '<Root>/Constant'
       */
      digitaltwins_2_B.Derivative1[0] = (digitaltwins_2_B.SineWave1 - (*lastU)[0])
        / w1;
      digitaltwins_2_B.Derivative1[1] = (digitaltwins_2_B.SineWave - (*lastU)[1])
        / w1;
      digitaltwins_2_B.Derivative1[2] = (0.0 - (*lastU)[2]) / w1;
    }

    /* End of Derivative: '<S1>/Derivative1' */

    /* Derivative: '<S1>/Derivative2' */
    if ((digitaltwins_2_DW.TimeStampA_m >= rtb_Derivative_o_idx_0) &&
        (digitaltwins_2_DW.TimeStampB_i >= rtb_Derivative_o_idx_0)) {
      rtb_Derivative2[0] = 0.0;
      rtb_Derivative2[1] = 0.0;
      rtb_Derivative2[2] = 0.0;
    } else {
      w1 = digitaltwins_2_DW.TimeStampA_m;
      lastU = &digitaltwins_2_DW.LastUAtTimeA_d;
      if (digitaltwins_2_DW.TimeStampA_m < digitaltwins_2_DW.TimeStampB_i) {
        if (digitaltwins_2_DW.TimeStampB_i < rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_i;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_o;
        }
      } else {
        if (digitaltwins_2_DW.TimeStampA_m >= rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_i;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_o;
        }
      }

      w1 = rtb_Derivative_o_idx_0 - w1;
      rtb_Derivative2[0] = (digitaltwins_2_B.Derivative1[0] - (*lastU)[0]) / w1;
      rtb_Derivative2[1] = (digitaltwins_2_B.Derivative1[1] - (*lastU)[1]) / w1;
      rtb_Derivative2[2] = (digitaltwins_2_B.Derivative1[2] - (*lastU)[2]) / w1;
    }

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant'
     *  Inport: '<Root>/Q'
     */
    digitaltwins_2_B.Sum[0] = digitaltwins_2_B.SineWave1 - digitaltwins_2_U.Q[0];
    digitaltwins_2_B.Sum[1] = digitaltwins_2_B.SineWave - digitaltwins_2_U.Q[1];
    digitaltwins_2_B.Sum[2] = 0.0 - digitaltwins_2_U.Q[2];

    /* Derivative: '<S1>/Derivative' */
    if ((digitaltwins_2_DW.TimeStampA_o >= rtb_Derivative_o_idx_0) &&
        (digitaltwins_2_DW.TimeStampB_g >= rtb_Derivative_o_idx_0)) {
      rtb_Derivative_idx_0 = 0.0;
      rtb_Derivative_idx_1 = 0.0;
      rtb_Derivative_idx_2 = 0.0;
    } else {
      w1 = digitaltwins_2_DW.TimeStampA_o;
      lastU = &digitaltwins_2_DW.LastUAtTimeA_k;
      if (digitaltwins_2_DW.TimeStampA_o < digitaltwins_2_DW.TimeStampB_g) {
        if (digitaltwins_2_DW.TimeStampB_g < rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_g;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_on;
        }
      } else {
        if (digitaltwins_2_DW.TimeStampA_o >= rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_g;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_on;
        }
      }

      w1 = rtb_Derivative_o_idx_0 - w1;
      rtb_Derivative_idx_0 = (digitaltwins_2_B.Sum[0] - (*lastU)[0]) / w1;
      rtb_Derivative_idx_1 = (digitaltwins_2_B.Sum[1] - (*lastU)[1]) / w1;
      rtb_Derivative_idx_2 = (digitaltwins_2_B.Sum[2] - (*lastU)[2]) / w1;
    }

    /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
     *  Inport: '<Root>/Q'
     *  Inport: '<Root>/Q_dot'
     */
    w1 = cos(digitaltwins_2_U.Q[2]);
    w3 = sin(digitaltwins_2_U.Q[2]);
    B[0] = (w1 + w3) * 20.618556701030926;
    B[3] = (w1 - w3) * 20.618556701030926;
    xm = (cos(digitaltwins_2_U.Q[2]) + sin(digitaltwins_2_U.Q[2])) *
      20.618556701030926;
    B[6] = xm;
    B[9] = (cos(digitaltwins_2_U.Q[2]) - sin(digitaltwins_2_U.Q[2])) *
      20.618556701030926;
    B[1] = (-w1 + w3) * 20.618556701030926;
    B[4] = xm;
    B[7] = (-cos(digitaltwins_2_U.Q[2]) + sin(digitaltwins_2_U.Q[2])) *
      20.618556701030926;
    B[10] = xm;
    B[2] = -12.371134020618555;
    B[5] = 12.371134020618555;
    B[8] = 12.371134020618555;
    B[11] = -12.371134020618555;
    xm = w1 * digitaltwins_2_U.Q_dot[0] + w3 * digitaltwins_2_U.Q_dot[1];
    ym = -w3 * digitaltwins_2_U.Q_dot[0] + w1 * digitaltwins_2_U.Q_dot[1];
    w3 = xm - ym;
    w1 = (w3 - 0.6 * digitaltwins_2_U.Q_dot[2]) * 20.618556701030926;
    ym += xm;
    xm = (ym + 0.6 * digitaltwins_2_U.Q_dot[2]) * 20.618556701030926;
    w3 = (w3 + 0.6 * digitaltwins_2_U.Q_dot[2]) * 20.618556701030926;
    ym = (ym - 0.6 * digitaltwins_2_U.Q_dot[2]) * 20.618556701030926;
    if (w1 > 5.0) {
      w1 = 5.0;
    } else {
      if (w1 < -5.0) {
        w1 = -5.0;
      }
    }

    if (xm > 5.0) {
      xm = 5.0;
    } else {
      if (xm < -5.0) {
        xm = -5.0;
      }
    }

    if (w3 > 5.0) {
      w3 = 5.0;
    } else {
      if (w3 < -5.0) {
        w3 = -5.0;
      }
    }

    if (ym > 5.0) {
      ym = 5.0;
    } else {
      if (ym < -5.0) {
        ym = -5.0;
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
    absx11 = fabs(y[0]);
    absx21 = fabs(y[1]);
    absx31 = fabs(y[2]);
    if ((absx21 > absx11) && (absx21 > absx31)) {
      p1 = 3;
      p2 = 0;
      x[0] = y[1];
      x[1] = y[0];
      x[3] = y[4];
      x[4] = y[3];
      x[6] = y[7];
      x[7] = y[6];
    } else {
      if (absx31 > absx11) {
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

    absx11 = x[1] / x[0];
    x[1] = absx11;
    absx21 = x[2] / x[0];
    x[2] = absx21;
    x[4] -= absx11 * x[3];
    x[5] -= absx21 * x[3];
    x[7] -= absx11 * x[6];
    x[8] -= absx21 * x[6];
    if (fabs(x[5]) > fabs(x[4])) {
      itmp = p2;
      p2 = p3;
      p3 = itmp;
      x[1] = absx21;
      x[2] = absx11;
      absx11 = x[4];
      x[4] = x[5];
      x[5] = absx11;
      absx11 = x[7];
      x[7] = x[8];
      x[8] = absx11;
    }

    absx11 = x[5] / x[4];
    x[8] -= absx11 * x[7];
    absx21 = (absx11 * x[1] - x[2]) / x[8];
    absx31 = -(x[7] * absx21 + x[1]) / x[4];
    y[p1] = ((1.0 - x[3] * absx31) - x[6] * absx21) / x[0];
    y[p1 + 1] = absx31;
    y[p1 + 2] = absx21;
    absx21 = -absx11 / x[8];
    absx31 = (1.0 - x[7] * absx21) / x[4];
    y[p2] = -(x[3] * absx31 + x[6] * absx21) / x[0];
    y[p2 + 1] = absx31;
    y[p2 + 2] = absx21;
    absx21 = 1.0 / x[8];
    absx31 = -x[7] * absx21 / x[4];
    y[p3] = -(x[3] * absx31 + x[6] * absx21) / x[0];
    y[p3 + 1] = absx31;
    y[p3 + 2] = absx21;
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

    absx11 = 175.04995217345095 * digitaltwins_2_U.Q_dot[1] *
      digitaltwins_2_U.Q_dot[2];
    absx21 = -175.04995217345095 * digitaltwins_2_U.Q_dot[0] *
      digitaltwins_2_U.Q_dot[2];
    if (w1 < 0.0) {
      w1 = -1.0;
    } else if (w1 > 0.0) {
      w1 = 1.0;
    } else if (w1 == 0.0) {
      w1 = 0.0;
    } else {
      w1 = (rtNaN);
    }

    absx31 = 0.0059473125000000012 * w1;
    if (xm < 0.0) {
      xm = -1.0;
    } else if (xm > 0.0) {
      xm = 1.0;
    } else if (xm == 0.0) {
      xm = 0.0;
    } else {
      xm = (rtNaN);
    }

    tmp_0 = 0.0059473125000000012 * xm;
    if (w3 < 0.0) {
      w3 = -1.0;
    } else if (w3 > 0.0) {
      w3 = 1.0;
    } else if (w3 == 0.0) {
      w3 = 0.0;
    } else {
      w3 = (rtNaN);
    }

    w1 = 0.0059473125000000012 * w3;
    if (ym < 0.0) {
      ym = -1.0;
    } else if (ym > 0.0) {
      ym = 1.0;
    } else if (ym == 0.0) {
      ym = 0.0;
    } else {
      ym = (rtNaN);
    }

    xm = 0.0059473125 * ym;
    for (p1 = 0; p1 < 3; p1++) {
      w3 = b_a[p1 + 3];
      ym = b_a[p1 + 6];
      for (p2 = 0; p2 < 4; p2++) {
        p3 = p1 + 3 * p2;
        y_tmp[p3] = 0.0;
        y_tmp[p3] += B[3 * p2] * b_a[p1];
        y_tmp[p3] += B[3 * p2 + 1] * w3;
        y_tmp[p3] += B[3 * p2 + 2] * ym;
      }

      /* MATLAB Function: '<S1>/x2r' */
      tmp[p1] = ((((real_T)a[p1 + 3] * digitaltwins_2_B.Sum[1] + (real_T)a[p1] *
                   digitaltwins_2_B.Sum[0]) + (real_T)a[p1 + 6] *
                  digitaltwins_2_B.Sum[2]) + digitaltwins_2_B.Derivative1[p1]) -
        digitaltwins_2_U.Q_dot[p1];
      rtb_Derivative2_0[p1] = ((((x[p1 + 3] * rtb_Derivative_idx_1 + x[p1] *
        rtb_Derivative_idx_0) + x[p1 + 6] * rtb_Derivative_idx_2) +
        rtb_Derivative2[p1]) + (ym * 0.0 + (w3 * absx21 + b_a[p1] * absx11))) +
        (((y_tmp[p1 + 3] * tmp_0 + y_tmp[p1] * absx31) + y_tmp[p1 + 6] * w1) +
         y_tmp[p1 + 9] * xm);
    }

    for (p1 = 0; p1 < 3; p1++) {
      for (p2 = 0; p2 < 4; p2++) {
        p3 = p2 + (p1 << 2);
        y_tmp[p3] = 0.0;
        y_tmp[p3] += b_b[3 * p1] * y_tmp_0[p2];
        y_tmp[p3] += b_b[3 * p1 + 1] * y_tmp_0[p2 + 4];
        y_tmp[p3] += b_b[3 * p1 + 2] * y_tmp_0[p2 + 8];
      }

      x_0[p1] = x[p1 + 6] * tmp[2] + (x[p1 + 3] * tmp[1] + x[p1] * tmp[0]);
    }

    w1 = rtb_Derivative2_0[0] + x_0[0];
    rtb_Derivative_idx_0 = rtb_Derivative2_0[1] + x_0[1];
    rtb_Derivative_idx_1 = rtb_Derivative2_0[2] + x_0[2];
    for (p1 = 0; p1 < 4; p1++) {
      rtb_u_control_f[p1] = y_tmp[p1 + 8] * rtb_Derivative_idx_1 + (y_tmp[p1 + 4]
        * rtb_Derivative_idx_0 + y_tmp[p1] * w1);
    }

    /* End of MATLAB Function: '<S1>/MATLAB Function' */

    /* Integrator: '<S2>/Integrator1' */
    digitaltwins_2_B.Integrator1[0] = digitaltwins_2_X.Integrator1_CSTATE[0];
    digitaltwins_2_B.Integrator1[1] = digitaltwins_2_X.Integrator1_CSTATE[1];
    digitaltwins_2_B.Integrator1[2] = digitaltwins_2_X.Integrator1_CSTATE[2];

    /* Derivative: '<S7>/Derivative1' */
    if ((digitaltwins_2_DW.TimeStampA_j >= rtb_Derivative_o_idx_0) &&
        (digitaltwins_2_DW.TimeStampB_m >= rtb_Derivative_o_idx_0)) {
      /* Derivative: '<S7>/Derivative1' */
      digitaltwins_2_B.Derivative1_j[0] = 0.0;
      digitaltwins_2_B.Derivative1_j[1] = 0.0;
      digitaltwins_2_B.Derivative1_j[2] = 0.0;
    } else {
      w1 = digitaltwins_2_DW.TimeStampA_j;
      lastU = &digitaltwins_2_DW.LastUAtTimeA_f;
      if (digitaltwins_2_DW.TimeStampA_j < digitaltwins_2_DW.TimeStampB_m) {
        if (digitaltwins_2_DW.TimeStampB_m < rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_m;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_o2;
        }
      } else {
        if (digitaltwins_2_DW.TimeStampA_j >= rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_m;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_o2;
        }
      }

      w1 = rtb_Derivative_o_idx_0 - w1;

      /* Derivative: '<S7>/Derivative1' */
      digitaltwins_2_B.Derivative1_j[0] = (digitaltwins_2_B.Integrator1[0] -
        (*lastU)[0]) / w1;
      digitaltwins_2_B.Derivative1_j[1] = (digitaltwins_2_B.Integrator1[1] -
        (*lastU)[1]) / w1;
      digitaltwins_2_B.Derivative1_j[2] = (digitaltwins_2_B.Integrator1[2] -
        (*lastU)[2]) / w1;
    }

    /* Derivative: '<S7>/Derivative2' */
    if ((digitaltwins_2_DW.TimeStampA_g >= rtb_Derivative_o_idx_0) &&
        (digitaltwins_2_DW.TimeStampB_d >= rtb_Derivative_o_idx_0)) {
      rtb_Derivative2[0] = 0.0;
      rtb_Derivative2[1] = 0.0;
      rtb_Derivative2[2] = 0.0;
    } else {
      w1 = digitaltwins_2_DW.TimeStampA_g;
      lastU = &digitaltwins_2_DW.LastUAtTimeA_b;
      if (digitaltwins_2_DW.TimeStampA_g < digitaltwins_2_DW.TimeStampB_d) {
        if (digitaltwins_2_DW.TimeStampB_d < rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_d;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_c;
        }
      } else {
        if (digitaltwins_2_DW.TimeStampA_g >= rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_d;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_c;
        }
      }

      w1 = rtb_Derivative_o_idx_0 - w1;
      rtb_Derivative2[0] = (digitaltwins_2_B.Derivative1_j[0] - (*lastU)[0]) /
        w1;
      rtb_Derivative2[1] = (digitaltwins_2_B.Derivative1_j[1] - (*lastU)[1]) /
        w1;
      rtb_Derivative2[2] = (digitaltwins_2_B.Derivative1_j[2] - (*lastU)[2]) /
        w1;
    }

    /* MATLAB Function: '<S3>/Qv_' incorporates:
     *  Inport: '<Root>/Qv'
     */
    absx11 = digitaltwins_2_U.Qv[0];
    absx21 = digitaltwins_2_U.Qv[1];
    w1 = digitaltwins_2_U.Qv[2];
    for (p1 = 0; p1 < 4; p1++) {
      rtb_Derivative_idx_0 = (real_T)a_0[p1 + 12] + ((real_T)a_0[p1 + 8] * w1 +
        ((real_T)a_0[p1 + 4] * absx21 + (real_T)a_0[p1] * absx11));
      Qv_temp[p1] = rtb_Derivative_idx_0;
    }

    /* Sum: '<S7>/Sum' incorporates:
     *  MATLAB Function: '<S3>/Qv_'
     */
    digitaltwins_2_B.Sum_m[0] = digitaltwins_2_B.Integrator1[0] - Qv_temp[0];
    digitaltwins_2_B.Sum_m[1] = digitaltwins_2_B.Integrator1[1] - Qv_temp[1];
    digitaltwins_2_B.Sum_m[2] = digitaltwins_2_B.Integrator1[2] - Qv_temp[2];

    /* Derivative: '<S7>/Derivative' */
    if ((digitaltwins_2_DW.TimeStampA_g5 >= rtb_Derivative_o_idx_0) &&
        (digitaltwins_2_DW.TimeStampB_a >= rtb_Derivative_o_idx_0)) {
      rtb_Derivative_o_idx_0 = 0.0;
      rtb_Derivative_idx_0 = 0.0;
      rtb_Derivative_idx_1 = 0.0;
    } else {
      w1 = digitaltwins_2_DW.TimeStampA_g5;
      lastU = &digitaltwins_2_DW.LastUAtTimeA_o;
      if (digitaltwins_2_DW.TimeStampA_g5 < digitaltwins_2_DW.TimeStampB_a) {
        if (digitaltwins_2_DW.TimeStampB_a < rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_a;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_e;
        }
      } else {
        if (digitaltwins_2_DW.TimeStampA_g5 >= rtb_Derivative_o_idx_0) {
          w1 = digitaltwins_2_DW.TimeStampB_a;
          lastU = &digitaltwins_2_DW.LastUAtTimeB_e;
        }
      }

      w1 = rtb_Derivative_o_idx_0 - w1;
      rtb_Derivative_o_idx_0 = (digitaltwins_2_B.Sum_m[0] - (*lastU)[0]) / w1;
      rtb_Derivative_idx_0 = (digitaltwins_2_B.Sum_m[1] - (*lastU)[1]) / w1;
      rtb_Derivative_idx_1 = (digitaltwins_2_B.Sum_m[2] - (*lastU)[2]) / w1;
    }

    /* MATLAB Function: '<S7>/MATLAB Function' incorporates:
     *  Inport: '<Root>/Qv_dot'
     *  MATLAB Function: '<S3>/Qv_'
     */
    w1 = cos(Qv_temp[2]);
    w3 = sin(Qv_temp[2]);
    B[0] = (w1 + w3) * 20.618556701030926;
    B[3] = (w1 - w3) * 20.618556701030926;
    xm = (cos(Qv_temp[2]) + sin(Qv_temp[2])) * 20.618556701030926;
    B[6] = xm;
    B[9] = (cos(Qv_temp[2]) - sin(Qv_temp[2])) * 20.618556701030926;
    B[1] = (-w1 + w3) * 20.618556701030926;
    B[4] = xm;
    B[7] = (-cos(Qv_temp[2]) + sin(Qv_temp[2])) * 20.618556701030926;
    B[10] = xm;
    B[2] = -12.371134020618555;
    B[5] = 12.371134020618555;
    B[8] = 12.371134020618555;
    B[11] = -12.371134020618555;
    xm = w1 * digitaltwins_2_U.Qv_dot[0] + w3 * digitaltwins_2_U.Qv_dot[1];
    ym = -w3 * digitaltwins_2_U.Qv_dot[0] + w1 * digitaltwins_2_U.Qv_dot[1];
    w3 = xm - ym;
    w1 = (w3 - 0.6 * digitaltwins_2_U.Qv_dot[2]) * 20.618556701030926;
    ym += xm;
    xm = (ym + 0.6 * digitaltwins_2_U.Qv_dot[2]) * 20.618556701030926;
    w3 = (w3 + 0.6 * digitaltwins_2_U.Qv_dot[2]) * 20.618556701030926;
    ym = (ym - 0.6 * digitaltwins_2_U.Qv_dot[2]) * 20.618556701030926;
    if (w1 > 5.0) {
      w1 = 5.0;
    } else {
      if (w1 < -5.0) {
        w1 = -5.0;
      }
    }

    if (xm > 5.0) {
      xm = 5.0;
    } else {
      if (xm < -5.0) {
        xm = -5.0;
      }
    }

    if (w3 > 5.0) {
      w3 = 5.0;
    } else {
      if (w3 < -5.0) {
        w3 = -5.0;
      }
    }

    if (ym > 5.0) {
      ym = 5.0;
    } else {
      if (ym < -5.0) {
        ym = -5.0;
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
    absx11 = fabs(y[0]);
    absx21 = fabs(y[1]);
    absx31 = fabs(y[2]);
    if ((absx21 > absx11) && (absx21 > absx31)) {
      p1 = 3;
      p2 = 0;
      x[0] = y[1];
      x[1] = y[0];
      x[3] = y[4];
      x[4] = y[3];
      x[6] = y[7];
      x[7] = y[6];
    } else {
      if (absx31 > absx11) {
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

    absx11 = x[1] / x[0];
    x[1] = absx11;
    absx21 = x[2] / x[0];
    x[2] = absx21;
    x[4] -= absx11 * x[3];
    x[5] -= absx21 * x[3];
    x[7] -= absx11 * x[6];
    x[8] -= absx21 * x[6];
    if (fabs(x[5]) > fabs(x[4])) {
      itmp = p2;
      p2 = p3;
      p3 = itmp;
      x[1] = absx21;
      x[2] = absx11;
      absx11 = x[4];
      x[4] = x[5];
      x[5] = absx11;
      absx11 = x[7];
      x[7] = x[8];
      x[8] = absx11;
    }

    absx11 = x[5] / x[4];
    x[8] -= absx11 * x[7];
    absx21 = (absx11 * x[1] - x[2]) / x[8];
    absx31 = -(x[7] * absx21 + x[1]) / x[4];
    y[p1] = ((1.0 - x[3] * absx31) - x[6] * absx21) / x[0];
    y[p1 + 1] = absx31;
    y[p1 + 2] = absx21;
    absx21 = -absx11 / x[8];
    absx31 = (1.0 - x[7] * absx21) / x[4];
    y[p2] = -(x[3] * absx31 + x[6] * absx21) / x[0];
    y[p2 + 1] = absx31;
    y[p2 + 2] = absx21;
    absx21 = 1.0 / x[8];
    absx31 = -x[7] * absx21 / x[4];
    y[p3] = -(x[3] * absx31 + x[6] * absx21) / x[0];
    y[p3 + 1] = absx31;
    y[p3 + 2] = absx21;
    for (p1 = 0; p1 < 9; p1++) {
      x[p1] = a_1[p1];
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

    absx11 = 175.04995217345095 * digitaltwins_2_U.Qv_dot[1] *
      digitaltwins_2_U.Qv_dot[2];
    absx21 = -175.04995217345095 * digitaltwins_2_U.Qv_dot[0] *
      digitaltwins_2_U.Qv_dot[2];
    if (w1 < 0.0) {
      w1 = -1.0;
    } else if (w1 > 0.0) {
      w1 = 1.0;
    } else if (w1 == 0.0) {
      w1 = 0.0;
    } else {
      w1 = (rtNaN);
    }

    absx31 = 0.0059473125000000012 * w1;
    if (xm < 0.0) {
      xm = -1.0;
    } else if (xm > 0.0) {
      xm = 1.0;
    } else if (xm == 0.0) {
      xm = 0.0;
    } else {
      xm = (rtNaN);
    }

    tmp_0 = 0.0059473125000000012 * xm;
    if (w3 < 0.0) {
      w3 = -1.0;
    } else if (w3 > 0.0) {
      w3 = 1.0;
    } else if (w3 == 0.0) {
      w3 = 0.0;
    } else {
      w3 = (rtNaN);
    }

    w1 = 0.0059473125000000012 * w3;
    if (ym < 0.0) {
      ym = -1.0;
    } else if (ym > 0.0) {
      ym = 1.0;
    } else if (ym == 0.0) {
      ym = 0.0;
    } else {
      ym = (rtNaN);
    }

    xm = 0.0059473125 * ym;
    for (p1 = 0; p1 < 3; p1++) {
      w3 = b_a[p1 + 3];
      ym = b_a[p1 + 6];
      for (p2 = 0; p2 < 4; p2++) {
        p3 = p1 + 3 * p2;
        y_tmp[p3] = 0.0;
        y_tmp[p3] += B[3 * p2] * b_a[p1];
        y_tmp[p3] += B[3 * p2 + 1] * w3;
        y_tmp[p3] += B[3 * p2 + 2] * ym;
      }

      /* MATLAB Function: '<S7>/x2r' */
      tmp[p1] = ((((real_T)a_1[p1 + 3] * digitaltwins_2_B.Sum_m[1] + (real_T)
                   a_1[p1] * digitaltwins_2_B.Sum_m[0]) + (real_T)a_1[p1 + 6] *
                  digitaltwins_2_B.Sum_m[2]) + digitaltwins_2_B.Derivative1_j[p1])
        - digitaltwins_2_U.Qv_dot[p1];
      rtb_Derivative2_0[p1] = ((((x[p1 + 3] * rtb_Derivative_idx_0 + x[p1] *
        rtb_Derivative_o_idx_0) + x[p1 + 6] * rtb_Derivative_idx_1) +
        rtb_Derivative2[p1]) + (ym * 0.0 + (w3 * absx21 + b_a[p1] * absx11))) +
        (((y_tmp[p1 + 3] * tmp_0 + y_tmp[p1] * absx31) + y_tmp[p1 + 6] * w1) +
         y_tmp[p1 + 9] * xm);
    }

    for (p1 = 0; p1 < 3; p1++) {
      for (p2 = 0; p2 < 4; p2++) {
        p3 = p2 + (p1 << 2);
        y_tmp[p3] = 0.0;
        y_tmp[p3] += b_b[3 * p1] * y_tmp_0[p2];
        y_tmp[p3] += b_b[3 * p1 + 1] * y_tmp_0[p2 + 4];
        y_tmp[p3] += b_b[3 * p1 + 2] * y_tmp_0[p2 + 8];
      }

      x_0[p1] = x[p1 + 6] * tmp[2] + (x[p1 + 3] * tmp[1] + x[p1] * tmp[0]);
    }

    w1 = rtb_Derivative2_0[0] + x_0[0];
    rtb_Derivative_idx_0 = rtb_Derivative2_0[1] + x_0[1];
    rtb_Derivative_idx_1 = rtb_Derivative2_0[2] + x_0[2];
    for (p1 = 0; p1 < 4; p1++) {
      /* Sum: '<S3>/Sum1' incorporates:
       *  MATLAB Function: '<S7>/MATLAB Function'
       */
      rtb_Derivative_o_idx_0 = rtb_u_control_f[p1];
      xm = ((y_tmp[p1 + 4] * rtb_Derivative_idx_0 + y_tmp[p1] * w1) + y_tmp[p1 +
            8] * rtb_Derivative_idx_1) + rtb_Derivative_o_idx_0;

      /* Saturate: '<S3>/Saturation' */
      if (xm > 10.0) {
        digitaltwins_2_Y.Tv[p1] = 10.0;
      } else if (xm < (-10.0)) {
        digitaltwins_2_Y.Tv[p1] = (-10.0);
      } else {
        digitaltwins_2_Y.Tv[p1] = xm;
      }

      /* End of Saturate: '<S3>/Saturation' */

      /* Saturate: '<Root>/Saturation' */
      if (rtb_Derivative_o_idx_0 > 10.0) {
        digitaltwins_2_Y.Tp[p1] = 10.0;
      } else if (rtb_Derivative_o_idx_0 < (-10.0)) {
        digitaltwins_2_Y.Tp[p1] = (-10.0);
      } else {
        digitaltwins_2_Y.Tp[p1] = rtb_Derivative_o_idx_0;
      }

      /* End of Saturate: '<Root>/Saturation' */
    }

    /* Integrator: '<S2>/Integrator' */
    digitaltwins_2_B.Integrator[0] = digitaltwins_2_X.Integrator_CSTATE[0];
    digitaltwins_2_B.Integrator[1] = digitaltwins_2_X.Integrator_CSTATE[1];
    digitaltwins_2_B.Integrator[2] = digitaltwins_2_X.Integrator_CSTATE[2];

    /* MATLAB Function: '<S2>/MATLAB Function1' */
    w1 = cos(digitaltwins_2_B.Integrator1[2]);
    w3 = sin(digitaltwins_2_B.Integrator1[2]);
    B[0] = (w1 + w3) * 20.618556701030926;
    B[3] = (w1 - w3) * 20.618556701030926;
    xm = (cos(digitaltwins_2_B.Integrator1[2]) + sin
          (digitaltwins_2_B.Integrator1[2])) * 20.618556701030926;
    B[6] = xm;
    B[9] = (cos(digitaltwins_2_B.Integrator1[2]) - sin
            (digitaltwins_2_B.Integrator1[2])) * 20.618556701030926;
    B[1] = (-w1 + w3) * 20.618556701030926;
    B[4] = xm;
    B[7] = (-cos(digitaltwins_2_B.Integrator1[2]) + sin
            (digitaltwins_2_B.Integrator1[2])) * 20.618556701030926;
    B[10] = xm;
    B[2] = -12.371134020618555;
    B[5] = 12.371134020618555;
    B[8] = 12.371134020618555;
    B[11] = -12.371134020618555;
    xm = w1 * digitaltwins_2_B.Integrator[0] + w3 * digitaltwins_2_B.Integrator
      [1];
    ym = -w3 * digitaltwins_2_B.Integrator[0] + w1 *
      digitaltwins_2_B.Integrator[1];
    w3 = xm - ym;
    digitaltwins_2_Y.w1 = (w3 - 0.6 * digitaltwins_2_B.Integrator[2]) *
      20.618556701030926;
    ym += xm;
    digitaltwins_2_Y.w2 = (ym + 0.6 * digitaltwins_2_B.Integrator[2]) *
      20.618556701030926;
    digitaltwins_2_Y.w3 = (w3 + 0.6 * digitaltwins_2_B.Integrator[2]) *
      20.618556701030926;
    digitaltwins_2_Y.w4 = (ym - 0.6 * digitaltwins_2_B.Integrator[2]) *
      20.618556701030926;
    if (digitaltwins_2_Y.w1 > 5.0) {
      digitaltwins_2_Y.w1 = 5.0;
    } else {
      if (digitaltwins_2_Y.w1 < -5.0) {
        digitaltwins_2_Y.w1 = -5.0;
      }
    }

    if (digitaltwins_2_Y.w2 > 5.0) {
      digitaltwins_2_Y.w2 = 5.0;
    } else {
      if (digitaltwins_2_Y.w2 < -5.0) {
        digitaltwins_2_Y.w2 = -5.0;
      }
    }

    if (digitaltwins_2_Y.w3 > 5.0) {
      digitaltwins_2_Y.w3 = 5.0;
    } else {
      if (digitaltwins_2_Y.w3 < -5.0) {
        digitaltwins_2_Y.w3 = -5.0;
      }
    }

    if (digitaltwins_2_Y.w4 > 5.0) {
      digitaltwins_2_Y.w4 = 5.0;
    } else {
      if (digitaltwins_2_Y.w4 < -5.0) {
        digitaltwins_2_Y.w4 = -5.0;
      }
    }

    absx11 = digitaltwins_2_Y.Tp[0];
    absx21 = digitaltwins_2_Y.Tp[1];
    w1 = digitaltwins_2_Y.Tp[2];
    xm = digitaltwins_2_Y.Tp[3];
    for (p1 = 0; p1 < 3; p1++) {
      rtb_Derivative_o_idx_0 = B[p1 + 9] * xm + (B[p1 + 6] * w1 + (B[p1 + 3] *
        absx21 + B[p1] * absx11));
      rtb_Derivative2_0[p1] = rtb_Derivative_o_idx_0;
    }

    tmp[0] = 175.04995217345095 * digitaltwins_2_B.Integrator[1] *
      digitaltwins_2_B.Integrator[2];
    tmp[1] = -175.04995217345095 * digitaltwins_2_B.Integrator[0] *
      digitaltwins_2_B.Integrator[2];
    tmp[2] = 0.0;
    if (digitaltwins_2_Y.w1 < 0.0) {
      w1 = -1.0;
    } else if (digitaltwins_2_Y.w1 > 0.0) {
      w1 = 1.0;
    } else if (digitaltwins_2_Y.w1 == 0.0) {
      w1 = 0.0;
    } else {
      w1 = (rtNaN);
    }

    absx11 = 0.0059473125000000012 * w1;
    if (digitaltwins_2_Y.w2 < 0.0) {
      xm = -1.0;
    } else if (digitaltwins_2_Y.w2 > 0.0) {
      xm = 1.0;
    } else if (digitaltwins_2_Y.w2 == 0.0) {
      xm = 0.0;
    } else {
      xm = (rtNaN);
    }

    absx21 = 0.0059473125000000012 * xm;
    if (digitaltwins_2_Y.w3 < 0.0) {
      w3 = -1.0;
    } else if (digitaltwins_2_Y.w3 > 0.0) {
      w3 = 1.0;
    } else if (digitaltwins_2_Y.w3 == 0.0) {
      w3 = 0.0;
    } else {
      w3 = (rtNaN);
    }

    w1 = 0.0059473125000000012 * w3;
    if (digitaltwins_2_Y.w4 < 0.0) {
      ym = -1.0;
    } else if (digitaltwins_2_Y.w4 > 0.0) {
      ym = 1.0;
    } else if (digitaltwins_2_Y.w4 == 0.0) {
      ym = 0.0;
    } else {
      ym = (rtNaN);
    }

    xm = 0.0059473125 * ym;
    for (p1 = 0; p1 < 3; p1++) {
      rtb_Derivative2[p1] = (rtb_Derivative2_0[p1] - tmp[p1]) - (((B[p1 + 3] *
        absx21 + B[p1] * absx11) + B[p1 + 6] * w1) + B[p1 + 9] * xm);
    }

    for (p1 = 0; p1 < 3; p1++) {
      digitaltwins_2_B.Q_2dot[p1] = 0.0;
      digitaltwins_2_B.Q_2dot[p1] += b_a[p1] * rtb_Derivative2[0];
      digitaltwins_2_B.Q_2dot[p1] += b_a[p1 + 3] * rtb_Derivative2[1];
      digitaltwins_2_B.Q_2dot[p1] += b_a[p1 + 6] * rtb_Derivative2[2];
    }

    /* End of MATLAB Function: '<S2>/MATLAB Function1' */

    /* Integrator: '<S9>/Integrator' */
    digitaltwins_2_B.Integrator_k[0] = digitaltwins_2_X.Integrator_CSTATE_c[0];
    digitaltwins_2_B.Integrator_k[1] = digitaltwins_2_X.Integrator_CSTATE_c[1];
    digitaltwins_2_B.Integrator_k[2] = digitaltwins_2_X.Integrator_CSTATE_c[2];

    /* MATLAB Function: '<S9>/Virtual robot' incorporates:
     *  Integrator: '<S9>/Integrator1'
     */
    w1 = cos(digitaltwins_2_X.Integrator1_CSTATE_n[2]);
    w3 = sin(digitaltwins_2_X.Integrator1_CSTATE_n[2]);
    B[0] = (w1 + w3) * 20.618556701030926;
    B[3] = (w1 - w3) * 20.618556701030926;
    xm = (cos(digitaltwins_2_X.Integrator1_CSTATE_n[2]) + sin
          (digitaltwins_2_X.Integrator1_CSTATE_n[2])) * 20.618556701030926;
    B[6] = xm;
    B[9] = (cos(digitaltwins_2_X.Integrator1_CSTATE_n[2]) - sin
            (digitaltwins_2_X.Integrator1_CSTATE_n[2])) * 20.618556701030926;
    B[1] = (-w1 + w3) * 20.618556701030926;
    B[4] = xm;
    B[7] = (-cos(digitaltwins_2_X.Integrator1_CSTATE_n[2]) + sin
            (digitaltwins_2_X.Integrator1_CSTATE_n[2])) * 20.618556701030926;
    B[10] = xm;
    B[2] = -12.371134020618555;
    B[5] = 12.371134020618555;
    B[8] = 12.371134020618555;
    B[11] = -12.371134020618555;
    xm = w1 * digitaltwins_2_B.Integrator_k[0] + w3 *
      digitaltwins_2_B.Integrator_k[1];
    ym = -w3 * digitaltwins_2_B.Integrator_k[0] + w1 *
      digitaltwins_2_B.Integrator_k[1];
    w3 = xm - ym;
    digitaltwins_2_Y.w5 = (w3 - 0.6 * digitaltwins_2_B.Integrator_k[2]) *
      20.618556701030926;
    ym += xm;
    digitaltwins_2_Y.w6 = (ym + 0.6 * digitaltwins_2_B.Integrator_k[2]) *
      20.618556701030926;
    digitaltwins_2_Y.w7 = (w3 + 0.6 * digitaltwins_2_B.Integrator_k[2]) *
      20.618556701030926;
    digitaltwins_2_Y.w8 = (ym - 0.6 * digitaltwins_2_B.Integrator_k[2]) *
      20.618556701030926;
    if (digitaltwins_2_Y.w5 > 5.0) {
      digitaltwins_2_Y.w5 = 5.0;
    } else {
      if (digitaltwins_2_Y.w5 < -5.0) {
        digitaltwins_2_Y.w5 = -5.0;
      }
    }

    if (digitaltwins_2_Y.w6 > 5.0) {
      digitaltwins_2_Y.w6 = 5.0;
    } else {
      if (digitaltwins_2_Y.w6 < -5.0) {
        digitaltwins_2_Y.w6 = -5.0;
      }
    }

    if (digitaltwins_2_Y.w7 > 5.0) {
      digitaltwins_2_Y.w7 = 5.0;
    } else {
      if (digitaltwins_2_Y.w7 < -5.0) {
        digitaltwins_2_Y.w7 = -5.0;
      }
    }

    if (digitaltwins_2_Y.w8 > 5.0) {
      digitaltwins_2_Y.w8 = 5.0;
    } else {
      if (digitaltwins_2_Y.w8 < -5.0) {
        digitaltwins_2_Y.w8 = -5.0;
      }
    }

    absx11 = digitaltwins_2_Y.Tv[0];
    absx21 = digitaltwins_2_Y.Tv[1];
    w1 = digitaltwins_2_Y.Tv[2];
    xm = digitaltwins_2_Y.Tv[3];
    for (p1 = 0; p1 < 3; p1++) {
      rtb_Derivative_o_idx_0 = B[p1 + 9] * xm + (B[p1 + 6] * w1 + (B[p1 + 3] *
        absx21 + B[p1] * absx11));
      rtb_Derivative2_0[p1] = rtb_Derivative_o_idx_0;
    }

    tmp[0] = 175.04995217345095 * digitaltwins_2_B.Integrator_k[1] *
      digitaltwins_2_B.Integrator_k[2];
    tmp[1] = -175.04995217345095 * digitaltwins_2_B.Integrator_k[0] *
      digitaltwins_2_B.Integrator_k[2];
    tmp[2] = 0.0;
    if (digitaltwins_2_Y.w5 < 0.0) {
      w1 = -1.0;
    } else if (digitaltwins_2_Y.w5 > 0.0) {
      w1 = 1.0;
    } else if (digitaltwins_2_Y.w5 == 0.0) {
      w1 = 0.0;
    } else {
      w1 = (rtNaN);
    }

    absx11 = 0.0059473125000000012 * w1;
    if (digitaltwins_2_Y.w6 < 0.0) {
      xm = -1.0;
    } else if (digitaltwins_2_Y.w6 > 0.0) {
      xm = 1.0;
    } else if (digitaltwins_2_Y.w6 == 0.0) {
      xm = 0.0;
    } else {
      xm = (rtNaN);
    }

    absx21 = 0.0059473125000000012 * xm;
    if (digitaltwins_2_Y.w7 < 0.0) {
      w3 = -1.0;
    } else if (digitaltwins_2_Y.w7 > 0.0) {
      w3 = 1.0;
    } else if (digitaltwins_2_Y.w7 == 0.0) {
      w3 = 0.0;
    } else {
      w3 = (rtNaN);
    }

    w1 = 0.0059473125000000012 * w3;
    if (digitaltwins_2_Y.w8 < 0.0) {
      ym = -1.0;
    } else if (digitaltwins_2_Y.w8 > 0.0) {
      ym = 1.0;
    } else if (digitaltwins_2_Y.w8 == 0.0) {
      ym = 0.0;
    } else {
      ym = (rtNaN);
    }

    xm = 0.0059473125 * ym;
    for (p1 = 0; p1 < 3; p1++) {
      rtb_Derivative2[p1] = (rtb_Derivative2_0[p1] - tmp[p1]) - (((B[p1 + 3] *
        absx21 + B[p1] * absx11) + B[p1 + 6] * w1) + B[p1 + 9] * xm);
    }

    for (p1 = 0; p1 < 3; p1++) {
      digitaltwins_2_B.Qp_2dot[p1] = 0.0;
      digitaltwins_2_B.Qp_2dot[p1] += b_a[p1] * rtb_Derivative2[0];
      digitaltwins_2_B.Qp_2dot[p1] += b_a[p1 + 3] * rtb_Derivative2[1];
      digitaltwins_2_B.Qp_2dot[p1] += b_a[p1 + 6] * rtb_Derivative2[2];
    }

    /* End of MATLAB Function: '<S9>/Virtual robot' */
  }

  if (rtmIsMajorTimeStep(digitaltwins_2_M)) {
    real_T (*lastU)[3];

    /* Update for Derivative: '<S1>/Derivative1' incorporates:
     *  Constant: '<Root>/Constant'
     */
    if (digitaltwins_2_DW.TimeStampA == (rtInf)) {
      digitaltwins_2_DW.TimeStampA = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA;
    } else if (digitaltwins_2_DW.TimeStampB == (rtInf)) {
      digitaltwins_2_DW.TimeStampB = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB;
    } else if (digitaltwins_2_DW.TimeStampA < digitaltwins_2_DW.TimeStampB) {
      digitaltwins_2_DW.TimeStampA = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA;
    } else {
      digitaltwins_2_DW.TimeStampB = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB;
    }

    (*lastU)[0] = digitaltwins_2_B.SineWave1;
    (*lastU)[1] = digitaltwins_2_B.SineWave;
    (*lastU)[2] = 0.0;

    /* End of Update for Derivative: '<S1>/Derivative1' */

    /* Update for Derivative: '<S1>/Derivative2' */
    if (digitaltwins_2_DW.TimeStampA_m == (rtInf)) {
      digitaltwins_2_DW.TimeStampA_m = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_d;
    } else if (digitaltwins_2_DW.TimeStampB_i == (rtInf)) {
      digitaltwins_2_DW.TimeStampB_i = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_o;
    } else if (digitaltwins_2_DW.TimeStampA_m < digitaltwins_2_DW.TimeStampB_i)
    {
      digitaltwins_2_DW.TimeStampA_m = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_d;
    } else {
      digitaltwins_2_DW.TimeStampB_i = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_o;
    }

    (*lastU)[0] = digitaltwins_2_B.Derivative1[0];
    (*lastU)[1] = digitaltwins_2_B.Derivative1[1];
    (*lastU)[2] = digitaltwins_2_B.Derivative1[2];

    /* End of Update for Derivative: '<S1>/Derivative2' */

    /* Update for Derivative: '<S1>/Derivative' */
    if (digitaltwins_2_DW.TimeStampA_o == (rtInf)) {
      digitaltwins_2_DW.TimeStampA_o = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_k;
    } else if (digitaltwins_2_DW.TimeStampB_g == (rtInf)) {
      digitaltwins_2_DW.TimeStampB_g = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_on;
    } else if (digitaltwins_2_DW.TimeStampA_o < digitaltwins_2_DW.TimeStampB_g)
    {
      digitaltwins_2_DW.TimeStampA_o = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_k;
    } else {
      digitaltwins_2_DW.TimeStampB_g = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_on;
    }

    (*lastU)[0] = digitaltwins_2_B.Sum[0];
    (*lastU)[1] = digitaltwins_2_B.Sum[1];
    (*lastU)[2] = digitaltwins_2_B.Sum[2];

    /* End of Update for Derivative: '<S1>/Derivative' */

    /* Update for Derivative: '<S7>/Derivative1' */
    if (digitaltwins_2_DW.TimeStampA_j == (rtInf)) {
      digitaltwins_2_DW.TimeStampA_j = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_f;
    } else if (digitaltwins_2_DW.TimeStampB_m == (rtInf)) {
      digitaltwins_2_DW.TimeStampB_m = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_o2;
    } else if (digitaltwins_2_DW.TimeStampA_j < digitaltwins_2_DW.TimeStampB_m)
    {
      digitaltwins_2_DW.TimeStampA_j = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_f;
    } else {
      digitaltwins_2_DW.TimeStampB_m = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_o2;
    }

    (*lastU)[0] = digitaltwins_2_B.Integrator1[0];
    (*lastU)[1] = digitaltwins_2_B.Integrator1[1];
    (*lastU)[2] = digitaltwins_2_B.Integrator1[2];

    /* End of Update for Derivative: '<S7>/Derivative1' */

    /* Update for Derivative: '<S7>/Derivative2' */
    if (digitaltwins_2_DW.TimeStampA_g == (rtInf)) {
      digitaltwins_2_DW.TimeStampA_g = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_b;
    } else if (digitaltwins_2_DW.TimeStampB_d == (rtInf)) {
      digitaltwins_2_DW.TimeStampB_d = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_c;
    } else if (digitaltwins_2_DW.TimeStampA_g < digitaltwins_2_DW.TimeStampB_d)
    {
      digitaltwins_2_DW.TimeStampA_g = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_b;
    } else {
      digitaltwins_2_DW.TimeStampB_d = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_c;
    }

    (*lastU)[0] = digitaltwins_2_B.Derivative1_j[0];
    (*lastU)[1] = digitaltwins_2_B.Derivative1_j[1];
    (*lastU)[2] = digitaltwins_2_B.Derivative1_j[2];

    /* End of Update for Derivative: '<S7>/Derivative2' */

    /* Update for Derivative: '<S7>/Derivative' */
    if (digitaltwins_2_DW.TimeStampA_g5 == (rtInf)) {
      digitaltwins_2_DW.TimeStampA_g5 = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_o;
    } else if (digitaltwins_2_DW.TimeStampB_a == (rtInf)) {
      digitaltwins_2_DW.TimeStampB_a = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_e;
    } else if (digitaltwins_2_DW.TimeStampA_g5 < digitaltwins_2_DW.TimeStampB_a)
    {
      digitaltwins_2_DW.TimeStampA_g5 = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeA_o;
    } else {
      digitaltwins_2_DW.TimeStampB_a = digitaltwins_2_M->Timing.t[0];
      lastU = &digitaltwins_2_DW.LastUAtTimeB_e;
    }

    (*lastU)[0] = digitaltwins_2_B.Sum_m[0];
    (*lastU)[1] = digitaltwins_2_B.Sum_m[1];
    (*lastU)[2] = digitaltwins_2_B.Sum_m[2];

    /* End of Update for Derivative: '<S7>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(digitaltwins_2_M)) {
    rt_ertODEUpdateContinuousStates(&digitaltwins_2_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++digitaltwins_2_M->Timing.clockTick0;
    digitaltwins_2_M->Timing.t[0] = rtsiGetSolverStopTime
      (&digitaltwins_2_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      digitaltwins_2_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void digitaltwins_2_derivatives(void)
{
  XDot_digitaltwins_2_T *_rtXdot;
  _rtXdot = ((XDot_digitaltwins_2_T *) digitaltwins_2_M->derivs);

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = digitaltwins_2_B.Integrator[0];
  _rtXdot->Integrator1_CSTATE[1] = digitaltwins_2_B.Integrator[1];
  _rtXdot->Integrator1_CSTATE[2] = digitaltwins_2_B.Integrator[2];

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = digitaltwins_2_B.Q_2dot[0];
  _rtXdot->Integrator_CSTATE[1] = digitaltwins_2_B.Q_2dot[1];
  _rtXdot->Integrator_CSTATE[2] = digitaltwins_2_B.Q_2dot[2];

  /* Derivatives for Integrator: '<S9>/Integrator' */
  _rtXdot->Integrator_CSTATE_c[0] = digitaltwins_2_B.Qp_2dot[0];
  _rtXdot->Integrator_CSTATE_c[1] = digitaltwins_2_B.Qp_2dot[1];
  _rtXdot->Integrator_CSTATE_c[2] = digitaltwins_2_B.Qp_2dot[2];

  /* Derivatives for Integrator: '<S9>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_n[0] = digitaltwins_2_B.Integrator_k[0];
  _rtXdot->Integrator1_CSTATE_n[1] = digitaltwins_2_B.Integrator_k[1];
  _rtXdot->Integrator1_CSTATE_n[2] = digitaltwins_2_B.Integrator_k[2];
}

/* Model initialize function */
void digitaltwins_2_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&digitaltwins_2_M->solverInfo,
                          &digitaltwins_2_M->Timing.simTimeStep);
    rtsiSetTPtr(&digitaltwins_2_M->solverInfo, &rtmGetTPtr(digitaltwins_2_M));
    rtsiSetStepSizePtr(&digitaltwins_2_M->solverInfo,
                       &digitaltwins_2_M->Timing.stepSize0);
    rtsiSetdXPtr(&digitaltwins_2_M->solverInfo, &digitaltwins_2_M->derivs);
    rtsiSetContStatesPtr(&digitaltwins_2_M->solverInfo, (real_T **)
                         &digitaltwins_2_M->contStates);
    rtsiSetNumContStatesPtr(&digitaltwins_2_M->solverInfo,
      &digitaltwins_2_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&digitaltwins_2_M->solverInfo,
      &digitaltwins_2_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&digitaltwins_2_M->solverInfo,
      &digitaltwins_2_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&digitaltwins_2_M->solverInfo,
      &digitaltwins_2_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&digitaltwins_2_M->solverInfo, (&rtmGetErrorStatus
      (digitaltwins_2_M)));
    rtsiSetRTModelPtr(&digitaltwins_2_M->solverInfo, digitaltwins_2_M);
  }

  rtsiSetSimTimeStep(&digitaltwins_2_M->solverInfo, MAJOR_TIME_STEP);
  digitaltwins_2_M->intgData.y = digitaltwins_2_M->odeY;
  digitaltwins_2_M->intgData.f[0] = digitaltwins_2_M->odeF[0];
  digitaltwins_2_M->intgData.f[1] = digitaltwins_2_M->odeF[1];
  digitaltwins_2_M->intgData.f[2] = digitaltwins_2_M->odeF[2];
  digitaltwins_2_M->contStates = ((X_digitaltwins_2_T *) &digitaltwins_2_X);
  rtsiSetSolverData(&digitaltwins_2_M->solverInfo, (void *)
                    &digitaltwins_2_M->intgData);
  rtsiSetSolverName(&digitaltwins_2_M->solverInfo,"ode3");
  rtmSetTPtr(digitaltwins_2_M, &digitaltwins_2_M->Timing.tArray[0]);
  digitaltwins_2_M->Timing.stepSize0 = 0.03;

  /* InitializeConditions for Derivative: '<S1>/Derivative1' */
  digitaltwins_2_DW.TimeStampA = (rtInf);
  digitaltwins_2_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Derivative: '<S1>/Derivative2' */
  digitaltwins_2_DW.TimeStampA_m = (rtInf);
  digitaltwins_2_DW.TimeStampB_i = (rtInf);

  /* InitializeConditions for Derivative: '<S1>/Derivative' */
  digitaltwins_2_DW.TimeStampA_o = (rtInf);
  digitaltwins_2_DW.TimeStampB_g = (rtInf);

  /* InitializeConditions for Derivative: '<S7>/Derivative1' */
  digitaltwins_2_DW.TimeStampA_j = (rtInf);
  digitaltwins_2_DW.TimeStampB_m = (rtInf);

  /* InitializeConditions for Derivative: '<S7>/Derivative2' */
  digitaltwins_2_DW.TimeStampA_g = (rtInf);
  digitaltwins_2_DW.TimeStampB_d = (rtInf);

  /* InitializeConditions for Derivative: '<S7>/Derivative' */
  digitaltwins_2_DW.TimeStampA_g5 = (rtInf);
  digitaltwins_2_DW.TimeStampB_a = (rtInf);

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  digitaltwins_2_X.Integrator1_CSTATE[0] = 2.5;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  digitaltwins_2_X.Integrator_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S9>/Integrator' */
  digitaltwins_2_X.Integrator_CSTATE_c[0] = 0.0;

  /* InitializeConditions for Integrator: '<S9>/Integrator1' */
  digitaltwins_2_X.Integrator1_CSTATE_n[0] = 2.5;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  digitaltwins_2_X.Integrator1_CSTATE[1] = 3;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  digitaltwins_2_X.Integrator_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S9>/Integrator' */
  digitaltwins_2_X.Integrator_CSTATE_c[1] = 0.0;

  /* InitializeConditions for Integrator: '<S9>/Integrator1' */
  digitaltwins_2_X.Integrator1_CSTATE_n[1] = 3;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  digitaltwins_2_X.Integrator1_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  digitaltwins_2_X.Integrator_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S9>/Integrator' */
  digitaltwins_2_X.Integrator_CSTATE_c[2] = 0.0;

  /* InitializeConditions for Integrator: '<S9>/Integrator1' */
  digitaltwins_2_X.Integrator1_CSTATE_n[2] = 0.0;
}

/* Model terminate function */
void digitaltwins_2_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
