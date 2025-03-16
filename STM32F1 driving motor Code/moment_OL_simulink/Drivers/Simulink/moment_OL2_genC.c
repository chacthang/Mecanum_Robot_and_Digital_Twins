/*
 * File: moment_OL2_genC.c
 *
 * Code generated for Simulink model 'moment_OL2_genC'.
 *
 * Model version                  : 7.73
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Sun Mar 31 15:18:06 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "moment_OL2_genC.h"
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
extern void moment_OL2_genC_derivatives(void);
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
static real_T rtGetInf(void);
static real32_T rtGetInfF(void);
static real_T rtGetMinusInf(void);
static real32_T rtGetMinusInfF(void);

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
  moment_OL2_genC_derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  moment_OL2_genC_step();
  moment_OL2_genC_derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  moment_OL2_genC_step();
  moment_OL2_genC_derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  moment_OL2_genC_step();
  moment_OL2_genC_derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void moment_OL2_genC_step(void)
{
  static const real_T a[9] = { 0.0055987558320373249, -0.0, 0.0, -0.0,
    0.0055987558320373249, -0.0, -0.0, -0.0, 0.014814814814814815 };

  real_T B_0[12];
  real_T B_1[3];
  real_T tmp[3];
  real_T B_2;
  real_T B_3;
  real_T rtb_CLOCK1;
  real_T rtb_CLOCK1_0;
  real_T tmp_0;
  real_T w1;
  real_T w1_0;
  real_T w2;
  real_T w2_0;
  real_T w3;
  real_T w3_0;
  int32_T T1;
  int32_T T2;
  int32_T T3;
  int32_T T4;
  int32_T i;
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  /* Clock: '<Root>/CLOCK1' */
  rtb_CLOCK1 = rtM->Timing.t[0];

  /* MATLAB Function: '<Root>/SET_POINT' */
  if (rtb_CLOCK1 <= 1.0) {
    T1 = 1;
    T2 = 1;
    T3 = 1;
    T4 = 1;
  } else if ((rtb_CLOCK1 > 1.0) && (rtb_CLOCK1 <= 5.0)) {
    T1 = 0;
    T2 = 0;
    T3 = 0;
    T4 = 0;
  } else if ((rtb_CLOCK1 > 5.0) && (rtb_CLOCK1 <= 6.0)) {
    T1 = 0;
    T2 = -2;
    T3 = 0;
    T4 = -2;
  } else if ((rtb_CLOCK1 > 6.0) && (rtb_CLOCK1 <= 12.0)) {
    T1 = 0;
    T2 = 0;
    T3 = 0;
    T4 = 0;
  } else if ((rtb_CLOCK1 > 12.0) && (rtb_CLOCK1 <= 13.0)) {
    T1 = -2;
    T2 = 0;
    T3 = -2;
    T4 = 0;
  } else if ((rtb_CLOCK1 > 13.0) && (rtb_CLOCK1 <= 17.0)) {
    T1 = 0;
    T2 = 0;
    T3 = 0;
    T4 = 0;
  } else if ((rtb_CLOCK1 > 17.0) && (rtb_CLOCK1 < 18.0)) {
    T1 = 1;
    T2 = 1;
    T3 = 1;
    T4 = 1;
  } else {
    T1 = 0;
    T2 = 0;
    T3 = 0;
    T4 = 0;
  }

  /* Integrator: '<S1>/Integrator' */
  rtDW.Integrator[0] = rtX.Integrator_CSTATE[0];
  rtDW.Integrator[1] = rtX.Integrator_CSTATE[1];
  rtDW.Integrator[2] = rtX.Integrator_CSTATE[2];

  /* MATLAB Function: '<S1>/MATLAB Function1' incorporates:
   *  Integrator: '<S1>/Integrator1'
   *  MATLAB Function: '<Root>/SET_POINT'
   */
  w1 = cos(rtX.Integrator1_CSTATE[2]);
  w2 = sin(rtX.Integrator1_CSTATE[2]);
  B_0[0] = (w1 + w2) * 20.833333333333332;
  B_0[3] = (w1 - w2) * 20.833333333333332;
  rtb_CLOCK1 = (cos(rtX.Integrator1_CSTATE[2]) + sin(rtX.Integrator1_CSTATE[2]))
    * 20.833333333333332;
  B_0[6] = rtb_CLOCK1;
  B_0[9] = (cos(rtX.Integrator1_CSTATE[2]) - sin(rtX.Integrator1_CSTATE[2])) *
    20.833333333333332;
  B_0[1] = (-w1 + w2) * 20.833333333333332;
  B_0[4] = rtb_CLOCK1;
  B_0[7] = (-cos(rtX.Integrator1_CSTATE[2]) + sin(rtX.Integrator1_CSTATE[2])) *
    20.833333333333332;
  B_0[10] = rtb_CLOCK1;
  B_0[2] = -12.499999999999998;
  B_0[5] = 12.499999999999998;
  B_0[8] = 12.499999999999998;
  B_0[11] = -12.499999999999998;
  rtb_CLOCK1 = w1 * rtDW.Integrator[0] + w2 * rtDW.Integrator[1];
  w2 = -w2 * rtDW.Integrator[0] + w1 * rtDW.Integrator[1];
  w3 = rtb_CLOCK1 - w2;
  w1 = (w3 - 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
  rtb_CLOCK1 += w2;
  w2 = (rtb_CLOCK1 + 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
  w3 = (w3 + 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
  rtb_CLOCK1 = (rtb_CLOCK1 - 0.6 * rtDW.Integrator[2]) * 20.833333333333332;
  tmp[0] = 178.61111111111111 * rtDW.Integrator[1] * rtDW.Integrator[2];
  tmp[1] = -178.61111111111111 * rtDW.Integrator[0] * rtDW.Integrator[2];
  tmp[2] = 0.0;
  if (w1 < 0.0) {
    w1_0 = -1.0;
  } else if (w1 > 0.0) {
    w1_0 = 1.0;
  } else if (w1 == 0.0) {
    w1_0 = 0.0;
  } else {
    w1_0 = (rtNaN);
  }

  w1_0 *= 0.00588;
  if (w2 < 0.0) {
    w2_0 = -1.0;
  } else if (w2 > 0.0) {
    w2_0 = 1.0;
  } else if (w2 == 0.0) {
    w2_0 = 0.0;
  } else {
    w2_0 = (rtNaN);
  }

  w2_0 *= 0.00588;
  if (w3 < 0.0) {
    w3_0 = -1.0;
  } else if (w3 > 0.0) {
    w3_0 = 1.0;
  } else if (w3 == 0.0) {
    w3_0 = 0.0;
  } else {
    w3_0 = (rtNaN);
  }

  w3_0 *= 0.00588;
  if (rtb_CLOCK1 < 0.0) {
    rtb_CLOCK1_0 = -1.0;
  } else if (rtb_CLOCK1 > 0.0) {
    rtb_CLOCK1_0 = 1.0;
  } else if (rtb_CLOCK1 == 0.0) {
    rtb_CLOCK1_0 = 0.0;
  } else {
    rtb_CLOCK1_0 = (rtNaN);
  }

  rtb_CLOCK1_0 *= 0.00588;
  for (i = 0; i < 3; i++) {
    B_2 = B_0[i];
    tmp_0 = B_2 * w1_0;
    B_3 = B_2 * (real_T)T1;
    B_2 = B_0[i + 3];
    tmp_0 += B_2 * w2_0;
    B_3 += B_2 * (real_T)T2;
    B_2 = B_0[i + 6];
    tmp_0 += B_2 * w3_0;
    B_3 += B_2 * (real_T)T3;
    B_2 = B_0[i + 9];
    tmp_0 += B_2 * rtb_CLOCK1_0;
    B_3 += B_2 * (real_T)T4;
    B_1[i] = (B_3 - tmp[i]) - tmp_0;
  }

  for (i = 0; i < 3; i++) {
    rtDW.Q_2dot[i] = 0.0;
    rtDW.Q_2dot[i] += a[i] * B_1[0];
    rtDW.Q_2dot[i] += a[i + 3] * B_1[1];
    rtDW.Q_2dot[i] += a[i + 6] * B_1[2];
  }

  /* Outport: '<Root>/w' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function1'
   */
  rtY.w[0] = w1;
  rtY.w[1] = w2;
  rtY.w[2] = w3;
  rtY.w[3] = rtb_CLOCK1;
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
      /* Update absolute timer for sample time: [0.1s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.1, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void moment_OL2_genC_derivatives(void)
{
  XDot *_rtXdot;
  _rtXdot = ((XDot *) rtM->derivs);

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = rtDW.Q_2dot[0];

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = rtDW.Integrator[0];

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE[1] = rtDW.Q_2dot[1];

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[1] = rtDW.Integrator[1];

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE[2] = rtDW.Q_2dot[2];

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[2] = rtDW.Integrator[2];
}

/* Model initialize function */
void moment_OL2_genC_initialize(void)
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
  rtM->Timing.stepSize0 = 0.1;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  rtX.Integrator_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  rtX.Integrator1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  rtX.Integrator_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  rtX.Integrator1_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  rtX.Integrator_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  rtX.Integrator1_CSTATE[2] = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
