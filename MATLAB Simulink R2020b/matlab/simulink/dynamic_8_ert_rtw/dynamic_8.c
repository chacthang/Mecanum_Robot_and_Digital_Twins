/*
 * File: dynamic_8.c
 *
 * Code generated for Simulink model 'dynamic_8'.
 *
 * Model version                  : 7.28
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Mon Apr  8 01:12:15 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "dynamic_8.h"
#define NumBitsPerChar                 8U

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

/* Continuous states */
X rtX;

/* Block signals and states (default storage) */
DW rtDW;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* private model entry point functions */
extern void dynamic_8_derivatives(void);
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);
static real_T rtGetNaN(void);
static real32_T rtGetNaNF(void);
extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
static void rt_InitInfAndNaN(size_t realSize);
static boolean_T rtIsInf(real_T value);
static boolean_T rtIsInfF(real32_T value);
static boolean_T rtIsNaN(real_T value);
static boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;

real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;

/*
 * Initialize rtInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0x7FF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    inf = tmpVal.fltVal;
  }

  return inf;
}

/*
 * Initialize rtInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}

/*
 * Initialize rtMinusInf needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF00000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    minf = tmpVal.fltVal;
  }

  return minf;
}

/*
 * Initialize rtMinusInfF needed by the generated code.
 * Inf is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}

/*
 * Initialize rtNaN needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.bitVal.words.wordH = 0xFFF80000U;
    tmpVal.bitVal.words.wordL = 0x00000000U;
    nan = tmpVal.fltVal;
  }

  return nan;
}

/*
 * Initialize rtNaNF needed by the generated code.
 * NaN is initialized as non-signaling. Assumes IEEE.
 */
static real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0 } };

  nanF.wordL.wordLuint = 0xFFC00000U;
  return nanF.wordL.wordLreal;
}

/*
 * Initialize the rtInf, rtMinusInf, and rtNaN needed by the
 * generated code. NaN is initialized as non-signaling. Assumes IEEE.
 */
static void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}

/* Test if value is infinite */
static boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
  boolean_T result = (boolean_T) 0;
  size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
  if (bitsPerReal == 32U) {
    result = rtIsNaNF((real32_T)value);
  } else {
    union {
      LittleEndianIEEEDouble bitVal;
      real_T fltVal;
    } tmpVal;

    tmpVal.fltVal = value;
    result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
                         ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                          (tmpVal.bitVal.words.wordL != 0) ));
  }

  return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
  IEEESingle tmp;
  tmp.wordL.wordLreal = value;
  return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                     (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE4_IntgData *id = (ODE4_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T *f3 = id->f[3];
  real_T temp;
  int_T i;
  int_T nXc = 6;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  dynamic_8_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  dynamic_8_step();
  dynamic_8_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  dynamic_8_step();
  dynamic_8_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  dynamic_8_step();
  dynamic_8_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void dynamic_8_step(void)
{
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  {
    static const real_T b_a[9] = { 0.0055987558320373249, -0.0, 0.0, -0.0,
      0.0055987558320373249, -0.0, -0.0, -0.0, 0.014814814814814815 };

    static const real_T b_b[9] = { 178.61111111111111, 0.0, 0.0, 0.0,
      178.61111111111111, 0.0, 0.0, 0.0, 67.5 };

    static const real_T b[4] = { -0.6, 0.6, 0.6, -0.6 };

    static const int8_T a[9] = { 4, 0, 0, 0, 4, 0, 0, 0, 4 };

    real_T B_0[12];
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
    w1 = rtM->Timing.t[0];

    /* Sin: '<Root>/Sine Wave1' */
    rtDW.SineWave1 = sin(0.41887902047863906 * w1) * 5.0;

    /* Sin: '<Root>/Sine Wave' */
    rtDW.SineWave = sin(0.83775804095727813 * w1) * 2.5;

    /* Derivative: '<S1>/Derivative1' incorporates:
     *  Derivative: '<S1>/Derivative'
     *  Derivative: '<S1>/Derivative2'
     */
    w1 = rtM->Timing.t[0];
    if ((rtDW.TimeStampA >= w1) && (rtDW.TimeStampB >= w1)) {
      /* Derivative: '<S1>/Derivative1' */
      rtDW.Derivative1[0] = 0.0;
      rtDW.Derivative1[1] = 0.0;
      rtDW.Derivative1[2] = 0.0;
    } else {
      w2 = rtDW.TimeStampA;
      lastU = &rtDW.LastUAtTimeA;
      if (rtDW.TimeStampA < rtDW.TimeStampB) {
        if (rtDW.TimeStampB < w1) {
          w2 = rtDW.TimeStampB;
          lastU = &rtDW.LastUAtTimeB;
        }
      } else {
        if (rtDW.TimeStampA >= w1) {
          w2 = rtDW.TimeStampB;
          lastU = &rtDW.LastUAtTimeB;
        }
      }

      w2 = w1 - w2;

      /* Derivative: '<S1>/Derivative1' incorporates:
       *  Constant: '<Root>/Constant'
       */
      rtDW.Derivative1[0] = (rtDW.SineWave1 - (*lastU)[0]) / w2;
      rtDW.Derivative1[1] = (rtDW.SineWave - (*lastU)[1]) / w2;
      rtDW.Derivative1[2] = (0.0 - (*lastU)[2]) / w2;
    }

    /* End of Derivative: '<S1>/Derivative1' */

    /* Derivative: '<S1>/Derivative2' */
    if ((rtDW.TimeStampA_m >= w1) && (rtDW.TimeStampB_i >= w1)) {
      rtb_Derivative2[0] = 0.0;
      rtb_Derivative2[1] = 0.0;
      rtb_Derivative2[2] = 0.0;
    } else {
      w2 = rtDW.TimeStampA_m;
      lastU = &rtDW.LastUAtTimeA_d;
      if (rtDW.TimeStampA_m < rtDW.TimeStampB_i) {
        if (rtDW.TimeStampB_i < w1) {
          w2 = rtDW.TimeStampB_i;
          lastU = &rtDW.LastUAtTimeB_o;
        }
      } else {
        if (rtDW.TimeStampA_m >= w1) {
          w2 = rtDW.TimeStampB_i;
          lastU = &rtDW.LastUAtTimeB_o;
        }
      }

      w2 = w1 - w2;
      rtb_Derivative2[0] = (rtDW.Derivative1[0] - (*lastU)[0]) / w2;
      rtb_Derivative2[1] = (rtDW.Derivative1[1] - (*lastU)[1]) / w2;
      rtb_Derivative2[2] = (rtDW.Derivative1[2] - (*lastU)[2]) / w2;
    }

    /* Sum: '<S1>/Sum' incorporates:
     *  Constant: '<Root>/Constant'
     *  Integrator: '<S2>/Integrator1'
     */
    rtDW.Sum[0] = rtDW.SineWave1 - rtX.Integrator1_CSTATE[0];
    rtDW.Sum[1] = rtDW.SineWave - rtX.Integrator1_CSTATE[1];
    rtDW.Sum[2] = 0.0 - rtX.Integrator1_CSTATE[2];

    /* Derivative: '<S1>/Derivative' */
    if ((rtDW.TimeStampA_o >= w1) && (rtDW.TimeStampB_g >= w1)) {
      rtb_Derivative_idx_0 = 0.0;
      rtb_Derivative_idx_1 = 0.0;
      rtb_Derivative_idx_2 = 0.0;
    } else {
      w2 = rtDW.TimeStampA_o;
      lastU = &rtDW.LastUAtTimeA_k;
      if (rtDW.TimeStampA_o < rtDW.TimeStampB_g) {
        if (rtDW.TimeStampB_g < w1) {
          w2 = rtDW.TimeStampB_g;
          lastU = &rtDW.LastUAtTimeB_on;
        }
      } else {
        if (rtDW.TimeStampA_o >= w1) {
          w2 = rtDW.TimeStampB_g;
          lastU = &rtDW.LastUAtTimeB_on;
        }
      }

      w2 = w1 - w2;
      rtb_Derivative_idx_0 = (rtDW.Sum[0] - (*lastU)[0]) / w2;
      rtb_Derivative_idx_1 = (rtDW.Sum[1] - (*lastU)[1]) / w2;
      rtb_Derivative_idx_2 = (rtDW.Sum[2] - (*lastU)[2]) / w2;
    }

    /* Integrator: '<S2>/Integrator' */
    rtDW.Integrator[0] = rtX.Integrator_CSTATE[0];
    rtDW.Integrator[1] = rtX.Integrator_CSTATE[1];
    rtDW.Integrator[2] = rtX.Integrator_CSTATE[2];

    /* MATLAB Function: '<S1>/control' incorporates:
     *  Integrator: '<S2>/Integrator1'
     *  MATLAB Function: '<S2>/robot'
     */
    w1 = cos(rtX.Integrator1_CSTATE[2]);
    w2 = sin(rtX.Integrator1_CSTATE[2]);
    B_0[0] = (w1 + w2) * 20.833333333333332;
    B_0[3] = (w1 - w2) * 20.833333333333332;
    B_tmp = (cos(rtX.Integrator1_CSTATE[2]) + sin(rtX.Integrator1_CSTATE[2])) *
      20.833333333333332;
    B_0[6] = B_tmp;
    B_tmp_0 = (cos(rtX.Integrator1_CSTATE[2]) - sin(rtX.Integrator1_CSTATE[2])) *
      20.833333333333332;
    B_0[9] = B_tmp_0;
    B_0[1] = (-w1 + w2) * 20.833333333333332;
    B_0[4] = B_tmp;
    B_tmp_1 = (-cos(rtX.Integrator1_CSTATE[2]) + sin(rtX.Integrator1_CSTATE[2]))
      * 20.833333333333332;
    B_0[7] = B_tmp_1;
    B_0[10] = B_tmp;
    B_0[2] = -12.499999999999998;
    B_0[5] = 12.499999999999998;
    B_0[8] = 12.499999999999998;
    B_0[11] = -12.499999999999998;
    xm = w1 * rtDW.Integrator[0] + w2 * rtDW.Integrator[1];
    ym = -w2 * rtDW.Integrator[0] + w1 * rtDW.Integrator[1];
    w3 = xm - ym;
    w1 = (w3 - 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
    xm += ym;
    w2 = (xm + 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
    w3 = (w3 + 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
    xm = (xm - 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
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
      y_tmp[p3] = B_0[p1];
      y_tmp[p3 + 1] = B_0[p1 + 3];
      y_tmp[p3 + 2] = B_0[p1 + 6];
      y_tmp[p3 + 3] = B_0[p1 + 9];
      for (p2 = 0; p2 < 3; p2++) {
        itmp = p2 + 3 * p1;
        y[itmp] = 0.0;
        y[itmp] += y_tmp[p3] * B_0[p2];
        y[itmp] += y_tmp[p3 + 1] * B_0[p2 + 3];
        y[itmp] += y_tmp[p3 + 2] * B_0[p2 + 6];
        y[itmp] += y_tmp[p3 + 3] * B_0[p2 + 9];
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

    absx21 = 178.61111111111111 * rtDW.Integrator[1] * rtDW.Integrator[2];
    absx31 = -178.61111111111111 * rtDW.Integrator[0] * rtDW.Integrator[2];
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
        y_tmp[p3] += B_0[3 * p2] * b_a[p1];
        y_tmp[p3] += B_0[3 * p2 + 1] * w1;
        y_tmp[p3] += B_0[3 * p2 + 2] * w2;
      }

      /* MATLAB Function: '<S1>/x2r' */
      tmp[p1] = ((((real_T)a[p1 + 3] * rtDW.Sum[1] + (real_T)a[p1] * rtDW.Sum[0])
                  + (real_T)a[p1 + 6] * rtDW.Sum[2]) + rtDW.Derivative1[p1]) -
        rtDW.Integrator[p1];
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
    B_0[0] = B_tmp;
    B_0[3] = B_tmp_0;
    B_0[6] = B_tmp;
    B_0[9] = B_tmp_0;
    B_0[1] = B_tmp_1;
    B_0[4] = B_tmp;
    B_0[7] = B_tmp_1;
    B_0[10] = B_tmp;
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
      B_0[3 * p1 + 2] = 20.833333333333332 * b[p1];
    }

    /* MATLAB Function: '<S2>/robot' incorporates:
     *  Integrator: '<S2>/Integrator1'
     */
    xm = cos(rtX.Integrator1_CSTATE[2]) * rtDW.Integrator[0] + sin
      (rtX.Integrator1_CSTATE[2]) * rtDW.Integrator[1];
    ym = -sin(rtX.Integrator1_CSTATE[2]) * rtDW.Integrator[0] + cos
      (rtX.Integrator1_CSTATE[2]) * rtDW.Integrator[1];
    w3 = xm - ym;
    w1 = (w3 - 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
    xm += ym;
    w2 = (xm + 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
    w3 = (w3 + 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
    xm = (xm - 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
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
      absx21 = B_0[p1];
      absx31 = absx21 * ym;
      rtb_Derivative_idx_1 = absx21 * B_tmp;
      absx21 = B_0[p1 + 3];
      absx31 += absx21 * tmp_0;
      rtb_Derivative_idx_1 += absx21 * B_tmp_0;
      absx21 = B_0[p1 + 6];
      absx31 += absx21 * tmp_1;
      rtb_Derivative_idx_1 += absx21 * B_tmp_1;
      absx21 = B_0[p1 + 9];
      absx31 += absx21 * tmp_2;
      rtb_Derivative_idx_1 += absx21 * rtb_Derivative_idx_0;
      rtb_Derivative2_0[p1] = (rtb_Derivative_idx_1 - tmp[p1]) - absx31;
    }

    for (p1 = 0; p1 < 3; p1++) {
      rtDW.Q_2dot[p1] = 0.0;
      rtDW.Q_2dot[p1] += b_a[p1] * rtb_Derivative2_0[0];
      rtDW.Q_2dot[p1] += b_a[p1 + 3] * rtb_Derivative2_0[1];
      rtDW.Q_2dot[p1] += b_a[p1 + 6] * rtb_Derivative2_0[2];
    }

    /* Outport: '<Root>/w5' incorporates:
     *  MATLAB Function: '<S2>/robot'
     */
    rtY.w5 = w1;

    /* Outport: '<Root>/w6' incorporates:
     *  MATLAB Function: '<S2>/robot'
     */
    rtY.w6 = w2;

    /* Outport: '<Root>/w7' incorporates:
     *  MATLAB Function: '<S2>/robot'
     */
    rtY.w7 = w3;

    /* Outport: '<Root>/w8' incorporates:
     *  MATLAB Function: '<S2>/robot'
     */
    rtY.w8 = xm;
  }

  if (rtmIsMajorTimeStep(rtM)) {
    real_T (*lastU)[3];

    /* Update for Derivative: '<S1>/Derivative1' incorporates:
     *  Constant: '<Root>/Constant'
     */
    if (rtDW.TimeStampA == (rtInf)) {
      rtDW.TimeStampA = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeA;
    } else if (rtDW.TimeStampB == (rtInf)) {
      rtDW.TimeStampB = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeB;
    } else if (rtDW.TimeStampA < rtDW.TimeStampB) {
      rtDW.TimeStampA = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeA;
    } else {
      rtDW.TimeStampB = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeB;
    }

    (*lastU)[0] = rtDW.SineWave1;
    (*lastU)[1] = rtDW.SineWave;
    (*lastU)[2] = 0.0;

    /* End of Update for Derivative: '<S1>/Derivative1' */

    /* Update for Derivative: '<S1>/Derivative2' */
    if (rtDW.TimeStampA_m == (rtInf)) {
      rtDW.TimeStampA_m = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeA_d;
    } else if (rtDW.TimeStampB_i == (rtInf)) {
      rtDW.TimeStampB_i = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeB_o;
    } else if (rtDW.TimeStampA_m < rtDW.TimeStampB_i) {
      rtDW.TimeStampA_m = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeA_d;
    } else {
      rtDW.TimeStampB_i = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeB_o;
    }

    (*lastU)[0] = rtDW.Derivative1[0];
    (*lastU)[1] = rtDW.Derivative1[1];
    (*lastU)[2] = rtDW.Derivative1[2];

    /* End of Update for Derivative: '<S1>/Derivative2' */

    /* Update for Derivative: '<S1>/Derivative' */
    if (rtDW.TimeStampA_o == (rtInf)) {
      rtDW.TimeStampA_o = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeA_k;
    } else if (rtDW.TimeStampB_g == (rtInf)) {
      rtDW.TimeStampB_g = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeB_on;
    } else if (rtDW.TimeStampA_o < rtDW.TimeStampB_g) {
      rtDW.TimeStampA_o = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeA_k;
    } else {
      rtDW.TimeStampB_g = rtM->Timing.t[0];
      lastU = &rtDW.LastUAtTimeB_on;
    }

    (*lastU)[0] = rtDW.Sum[0];
    (*lastU)[1] = rtDW.Sum[1];
    (*lastU)[2] = rtDW.Sum[2];

    /* End of Update for Derivative: '<S1>/Derivative' */
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void dynamic_8_derivatives(void)
{
  XDot *_rtXdot;
  _rtXdot = ((XDot *) rtM->derivs);

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = rtDW.Integrator[0];

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = rtDW.Q_2dot[0];

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[1] = rtDW.Integrator[1];

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[1] = rtDW.Q_2dot[1];

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[2] = rtDW.Integrator[2];

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[2] = rtDW.Q_2dot[2];
}

/* Model initialize function */
void dynamic_8_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (real_T **) &rtM->contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->intgData.y = rtM->odeY;
  rtM->intgData.f[0] = rtM->odeF[0];
  rtM->intgData.f[1] = rtM->odeF[1];
  rtM->intgData.f[2] = rtM->odeF[2];
  rtM->intgData.f[3] = rtM->odeF[3];
  rtM->contStates = ((X *) &rtX);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->intgData);
  rtsiSetSolverName(&rtM->solverInfo,"ode4");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 0.01;

  /* InitializeConditions for Derivative: '<S1>/Derivative1' */
  rtDW.TimeStampA = (rtInf);
  rtDW.TimeStampB = (rtInf);

  /* InitializeConditions for Derivative: '<S1>/Derivative2' */
  rtDW.TimeStampA_m = (rtInf);
  rtDW.TimeStampB_i = (rtInf);

  /* InitializeConditions for Derivative: '<S1>/Derivative' */
  rtDW.TimeStampA_o = (rtInf);
  rtDW.TimeStampB_g = (rtInf);

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  rtX.Integrator1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  rtX.Integrator_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  rtX.Integrator1_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  rtX.Integrator_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  rtX.Integrator1_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  rtX.Integrator_CSTATE[2] = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
