/*
 * File: last8.c
 *
 * Code generated for Simulink model 'last8'.
 *
 * Model version                  : 7.90
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed Jun  5 09:42:40 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "last8.h"
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

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL* const rtM = &rtM_;

/* private model entry point functions */
extern void last8_derivatives(void);
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
    }
    else {
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
    }
    else {
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
    }
    else {
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
    (void)(realSize);
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
    return (boolean_T)((value == rtInf || value == rtMinusInf) ? 1U : 0U);
}

/* Test if single-precision value is infinite */
static boolean_T rtIsInfF(real32_T value)
{
    return (boolean_T)(((value) == rtInfF || (value) == rtMinusInfF) ? 1U : 0U);
}

/* Test if value is not a number */
static boolean_T rtIsNaN(real_T value)
{
    boolean_T result = (boolean_T)0;
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    if (bitsPerReal == 32U) {
        result = rtIsNaNF((real32_T)value);
    }
    else {
        union {
            LittleEndianIEEEDouble bitVal;
            real_T fltVal;
        } tmpVal;

        tmpVal.fltVal = value;
        result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) == 0x7FF00000 &&
            ((tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                (tmpVal.bitVal.words.wordL != 0)));
    }

    return result;
}

/* Test if single-precision value is not a number */
static boolean_T rtIsNaNF(real32_T value)
{
    IEEESingle tmp;
    tmp.wordL.wordLreal = value;
    return (boolean_T)((tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
        (tmp.wordL.wordLuint & 0x007FFFFF) != 0);
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo* si)
{
    time_T t = rtsiGetT(si);
    time_T tnew = rtsiGetSolverStopTime(si);
    time_T h = rtsiGetStepSize(si);
    real_T* x = rtsiGetContStates(si);
    ODE4_IntgData* id = (ODE4_IntgData*)rtsiGetSolverData(si);
    real_T* y = id->y;
    real_T* f0 = id->f[0];
    real_T* f1 = id->f[1];
    real_T* f2 = id->f[2];
    real_T* f3 = id->f[3];
    real_T temp;
    int_T i;
    int_T nXc = 6;
    rtsiSetSimTimeStep(si, MINOR_TIME_STEP);

    /* Save the state values at time t in y, we'll use x as ynew. */
    (void)memcpy(y, x,
        (uint_T)nXc * sizeof(real_T));

    /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
    /* f0 = f(t,y) */
    rtsiSetdX(si, f0);
    last8_derivatives();

    /* f1 = f(t + (h/2), y + (h/2)*f0) */
    temp = 0.5 * h;
    for (i = 0; i < nXc; i++) {
        x[i] = y[i] + (temp * f0[i]);
    }

    rtsiSetT(si, t + temp);
    rtsiSetdX(si, f1);
    last8_step();
    last8_derivatives();

    /* f2 = f(t + (h/2), y + (h/2)*f1) */
    for (i = 0; i < nXc; i++) {
        x[i] = y[i] + (temp * f1[i]);
    }

    rtsiSetdX(si, f2);
    last8_step();
    last8_derivatives();

    /* f3 = f(t + h, y + h*f2) */
    for (i = 0; i < nXc; i++) {
        x[i] = y[i] + (h * f2[i]);
    }

    rtsiSetT(si, tnew);
    rtsiSetdX(si, f3);
    last8_step();
    last8_derivatives();

    /* tnew = t + h
       ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
    temp = h / 6.0;
    for (i = 0; i < nXc; i++) {
        x[i] = y[i] + temp * (f0[i] + 2.0 * f1[i] + 2.0 * f2[i] + f3[i]);
    }

    rtsiSetSimTimeStep(si, MAJOR_TIME_STEP);
}

/* Model step function */
void last8_step(void)
{
    if (rtmIsMajorTimeStep(rtM)) {
        /* set solver stop time */
        rtsiSetSolverStopTime(&rtM->solverInfo, ((rtM->Timing.clockTick0 + 1) *
            rtM->Timing.stepSize0));
    }                                    /* end MajorTimeStep */

    /* Update absolute time of base rate at minor time step */
    if (rtmIsMinorTimeStep(rtM)) {
        rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
    }

    {
        static const real_T a_0[9] = { 0.01, 0.0, 0.0, 0.0, 0.01, 0.0, 0.0, 0.0,
          0.01 };

        static const real_T b_a[9] = { 0.0055987558320373249, -0.0, 0.0, -0.0,
          0.0055987558320373249, -0.0, -0.0, -0.0, 0.014814814814814815 };

        static const real_T b_b[9] = { 178.61111111111111, 0.0, 0.0, 0.0,
          178.61111111111111, 0.0, 0.0, 0.0, 67.5 };

        static const int8_T a[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };

        real_T B_0[12];
        real_T y_tmp[12];
        real_T y_tmp_0[12];
        real_T x[9];
        real_T y[9];
        real_T rtb_Saturation[4];
        real_T rtb_Derivative2[3];
        real_T rtb_Derivative2_0[3];
        real_T tmp[3];
        real_T(*lastU)[3];
        real_T B_1;
        real_T B_2;
        real_T B_tmp;
        real_T SineWave1_tmp;
        real_T absx11;
        real_T absx11_tmp;
        real_T absx21;
        real_T absx31;
        real_T rtb_Derivative_idx_0;
        real_T rtb_Derivative_idx_1;
        real_T rtb_Derivative_idx_2;
        real_T rtb_Saturation_idx_3;
        real_T tmp_0;
        real_T xm;
        real_T ym;
        int32_T itmp;
        int32_T p1;
        int32_T p2;
        int32_T p3;

        /* Sin: '<Root>/Sine Wave1' incorporates:
         *  Sin: '<Root>/Sine Wave'
         */
        SineWave1_tmp = rtM->Timing.t[0];

        /* Sin: '<Root>/Sine Wave1' */
        rtDW.SineWave1 = sin(0.20943951023931953 * SineWave1_tmp) * 0.5 + 1.5;

        /* Sin: '<Root>/Sine Wave' */
        rtDW.SineWave = sin(0.41887902047863906 * SineWave1_tmp) * 0.5 + 1.2;

        /* Derivative: '<S1>/Derivative1' incorporates:
         *  Derivative: '<S1>/Derivative'
         *  Derivative: '<S1>/Derivative2'
         */
        SineWave1_tmp = rtM->Timing.t[0];
        if ((rtDW.TimeStampA >= SineWave1_tmp) && (rtDW.TimeStampB >= SineWave1_tmp))
        {
            /* Derivative: '<S1>/Derivative1' */
            rtDW.Derivative1[0] = 0.0;
            rtDW.Derivative1[1] = 0.0;
            rtDW.Derivative1[2] = 0.0;
        }
        else {
            xm = rtDW.TimeStampA;
            lastU = &rtDW.LastUAtTimeA;
            if (rtDW.TimeStampA < rtDW.TimeStampB) {
                if (rtDW.TimeStampB < SineWave1_tmp) {
                    xm = rtDW.TimeStampB;
                    lastU = &rtDW.LastUAtTimeB;
                }
            }
            else {
                if (rtDW.TimeStampA >= SineWave1_tmp) {
                    xm = rtDW.TimeStampB;
                    lastU = &rtDW.LastUAtTimeB;
                }
            }

            xm = SineWave1_tmp - xm;

            /* Derivative: '<S1>/Derivative1' incorporates:
             *  Constant: '<Root>/Constant2'
             */
            rtDW.Derivative1[0] = (rtDW.SineWave1 - (*lastU)[0]) / xm;
            rtDW.Derivative1[1] = (rtDW.SineWave - (*lastU)[1]) / xm;
            rtDW.Derivative1[2] = (0.0 - (*lastU)[2]) / xm;
        }

        /* End of Derivative: '<S1>/Derivative1' */

        /* Derivative: '<S1>/Derivative2' */
        if ((rtDW.TimeStampA_m >= SineWave1_tmp) && (rtDW.TimeStampB_i >=
            SineWave1_tmp)) {
            rtb_Derivative2[0] = 0.0;
            rtb_Derivative2[1] = 0.0;
            rtb_Derivative2[2] = 0.0;
        }
        else {
            xm = rtDW.TimeStampA_m;
            lastU = &rtDW.LastUAtTimeA_d;
            if (rtDW.TimeStampA_m < rtDW.TimeStampB_i) {
                if (rtDW.TimeStampB_i < SineWave1_tmp) {
                    xm = rtDW.TimeStampB_i;
                    lastU = &rtDW.LastUAtTimeB_o;
                }
            }
            else {
                if (rtDW.TimeStampA_m >= SineWave1_tmp) {
                    xm = rtDW.TimeStampB_i;
                    lastU = &rtDW.LastUAtTimeB_o;
                }
            }

            xm = SineWave1_tmp - xm;
            rtb_Derivative2[0] = (rtDW.Derivative1[0] - (*lastU)[0]) / xm;
            rtb_Derivative2[1] = (rtDW.Derivative1[1] - (*lastU)[1]) / xm;
            rtb_Derivative2[2] = (rtDW.Derivative1[2] - (*lastU)[2]) / xm;
        }

        /* Sum: '<S1>/Sum' incorporates:
         *  Constant: '<Root>/Constant2'
         *  Inport: '<Root>/Q'
         */
        rtDW.Sum[0] = rtDW.SineWave1 - rtU.Q[0];
        rtDW.Sum[1] = rtDW.SineWave - rtU.Q[1];
        rtDW.Sum[2] = 0.0 - rtU.Q[2];

        /* Derivative: '<S1>/Derivative' */
        if ((rtDW.TimeStampA_o >= SineWave1_tmp) && (rtDW.TimeStampB_g >=
            SineWave1_tmp)) {
            rtb_Derivative_idx_0 = 0.0;
            rtb_Derivative_idx_1 = 0.0;
            rtb_Derivative_idx_2 = 0.0;
        }
        else {
            xm = rtDW.TimeStampA_o;
            lastU = &rtDW.LastUAtTimeA_k;
            if (rtDW.TimeStampA_o < rtDW.TimeStampB_g) {
                if (rtDW.TimeStampB_g < SineWave1_tmp) {
                    xm = rtDW.TimeStampB_g;
                    lastU = &rtDW.LastUAtTimeB_on;
                }
            }
            else {
                if (rtDW.TimeStampA_o >= SineWave1_tmp) {
                    xm = rtDW.TimeStampB_g;
                    lastU = &rtDW.LastUAtTimeB_on;
                }
            }

            xm = SineWave1_tmp - xm;
            rtb_Derivative_idx_0 = (rtDW.Sum[0] - (*lastU)[0]) / xm;
            rtb_Derivative_idx_1 = (rtDW.Sum[1] - (*lastU)[1]) / xm;
            rtb_Derivative_idx_2 = (rtDW.Sum[2] - (*lastU)[2]) / xm;
        }

        /* MATLAB Function: '<S1>/control' incorporates:
         *  Inport: '<Root>/Q'
         *  Inport: '<Root>/Q_dot'
         *  Saturate: '<Root>/Saturation'
         */
        SineWave1_tmp = rtU.Q_dot[2];
        ym = cos(rtU.Q[2]);
        absx11 = sin(rtU.Q[2]);
        B_0[0] = (ym + absx11) * 20.833333333333332;
        B_0[3] = (ym - absx11) * 20.833333333333332;
        B_tmp = (cos(rtU.Q[2]) + sin(rtU.Q[2])) * 20.833333333333332;
        B_0[6] = B_tmp;
        B_0[9] = (cos(rtU.Q[2]) - sin(rtU.Q[2])) * 20.833333333333332;
        B_0[1] = (-ym + absx11) * 20.833333333333332;
        B_0[4] = B_tmp;
        B_0[7] = (-cos(rtU.Q[2]) + sin(rtU.Q[2])) * 20.833333333333332;
        B_0[10] = B_tmp;
        B_0[2] = -12.499999999999998;
        B_0[5] = 12.499999999999998;
        B_0[8] = 12.499999999999998;
        B_0[11] = -12.499999999999998;
        xm = ym * rtU.Q_dot[0] + absx11 * rtU.Q_dot[1];
        ym = -absx11 * rtU.Q_dot[0] + ym * rtU.Q_dot[1];
        if (xm > 0.1) {
            xm = 0.1;
        }
        else {
            if (xm < -0.1) {
                xm = -0.1;
            }
        }

        if (ym > 0.1) {
            ym = 0.1;
        }
        else {
            if (ym < -0.1) {
                ym = -0.1;
            }
        }

        if (rtU.Q_dot[2] > 0.1) {
            SineWave1_tmp = 0.1;
        }
        else {
            if (rtU.Q_dot[2] < -0.1) {
                SineWave1_tmp = -0.1;
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
        }
        else {
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

        absx11_tmp = x[1] / x[0];
        x[1] = absx11_tmp;
        B_tmp = x[2] / x[0];
        x[2] = B_tmp;
        x[4] -= absx11_tmp * x[3];
        x[5] -= B_tmp * x[3];
        x[7] -= absx11_tmp * x[6];
        x[8] -= B_tmp * x[6];
        if (fabs(x[5]) > fabs(x[4])) {
            itmp = p2;
            p2 = p3;
            p3 = itmp;
            x[1] = B_tmp;
            x[2] = absx11_tmp;
            absx11 = x[4];
            x[4] = x[5];
            x[5] = absx11;
            absx11 = x[7];
            x[7] = x[8];
            x[8] = absx11;
        }

        absx11_tmp = x[5] / x[4];
        x[8] -= absx11_tmp * x[7];
        absx11 = (absx11_tmp * x[1] - x[2]) / x[8];
        absx21 = -(x[7] * absx11 + x[1]) / x[4];
        y[p1] = ((1.0 - x[3] * absx21) - x[6] * absx11) / x[0];
        y[p1 + 1] = absx21;
        y[p1 + 2] = absx11;
        absx11 = -absx11_tmp / x[8];
        absx21 = (1.0 - x[7] * absx11) / x[4];
        y[p2] = -(x[3] * absx21 + x[6] * absx11) / x[0];
        y[p2 + 1] = absx21;
        y[p2 + 2] = absx11;
        absx11 = 1.0 / x[8];
        absx21 = -x[7] * absx11 / x[4];
        y[p3] = -(x[3] * absx21 + x[6] * absx11) / x[0];
        y[p3 + 1] = absx21;
        y[p3 + 2] = absx11;
        for (p1 = 0; p1 < 3; p1++) {
            for (p2 = 0; p2 < 4; p2++) {
                p3 = p2 + (p1 << 2);
                y_tmp_0[p3] = 0.0;
                y_tmp_0[p3] += y[3 * p1] * y_tmp[p2];
                y_tmp_0[p3] += y[3 * p1 + 1] * y_tmp[p2 + 4];
                y_tmp_0[p3] += y[3 * p1 + 2] * y_tmp[p2 + 8];
            }
        }

        B_tmp = 178.61111111111111 * rtU.Q_dot[1] * rtU.Q_dot[2];
        absx11_tmp = -178.61111111111111 * rtU.Q_dot[0] * rtU.Q_dot[2];
        absx31 = xm - ym;
        absx11 = (absx31 - 0.6 * SineWave1_tmp) * 20.833333333333332;
        ym += xm;
        absx21 = (ym + 0.6 * SineWave1_tmp) * 20.833333333333332;
        absx31 = (absx31 + 0.6 * SineWave1_tmp) * 20.833333333333332;
        xm = (ym - 0.6 * SineWave1_tmp) * 20.833333333333332;
        if (absx11 < 0.0) {
            absx11 = -1.0;
        }
        else if (absx11 > 0.0) {
            absx11 = 1.0;
        }
        else if (absx11 == 0.0) {
            absx11 = 0.0;
        }
        else {
            absx11 = (rtNaN);
        }

        SineWave1_tmp = 0.0058860000000000006 * absx11;
        if (absx21 < 0.0) {
            absx11 = -1.0;
        }
        else if (absx21 > 0.0) {
            absx11 = 1.0;
        }
        else if (absx21 == 0.0) {
            absx11 = 0.0;
        }
        else {
            absx11 = (rtNaN);
        }

        absx21 = 0.0058860000000000006 * absx11;
        if (absx31 < 0.0) {
            absx11 = -1.0;
        }
        else if (absx31 > 0.0) {
            absx11 = 1.0;
        }
        else if (absx31 == 0.0) {
            absx11 = 0.0;
        }
        else {
            absx11 = (rtNaN);
        }

        ym = 0.0058860000000000006 * absx11;
        if (xm < 0.0) {
            absx11 = -1.0;
        }
        else if (xm > 0.0) {
            absx11 = 1.0;
        }
        else if (xm == 0.0) {
            absx11 = 0.0;
        }
        else {
            absx11 = (rtNaN);
        }

        xm = 0.0058860000000000006 * absx11;
        for (p1 = 0; p1 < 3; p1++) {
            absx11 = b_a[p1 + 3];
            absx31 = b_a[p1 + 6];
            for (p2 = 0; p2 < 4; p2++) {
                p3 = p1 + 3 * p2;
                y_tmp[p3] = 0.0;
                y_tmp[p3] += B_0[3 * p2] * b_a[p1];
                y_tmp[p3] += B_0[3 * p2 + 1] * absx11;
                y_tmp[p3] += B_0[3 * p2 + 2] * absx31;
            }

            /* MATLAB Function: '<S1>/x2r' */
            tmp[p1] = ((((real_T)a[p1 + 3] * rtDW.Sum[1] + (real_T)a[p1] * rtDW.Sum[0])
                + (real_T)a[p1 + 6] * rtDW.Sum[2]) + rtDW.Derivative1[p1]) -
                rtU.Q_dot[p1];
            rtb_Derivative2_0[p1] = ((((a_0[p1 + 3] * rtb_Derivative_idx_1 + a_0[p1] *
                rtb_Derivative_idx_0) + a_0[p1 + 6] * rtb_Derivative_idx_2) +
                rtb_Derivative2[p1]) + (absx31 * 0.0 + (absx11 * absx11_tmp + b_a[p1] *
                    B_tmp))) + (((y_tmp[p1 + 3] * absx21 + y_tmp[p1] * SineWave1_tmp) +
                        y_tmp[p1 + 6] * ym) + y_tmp[p1 + 9] * xm);
        }

        for (p1 = 0; p1 < 3; p1++) {
            for (p2 = 0; p2 < 4; p2++) {
                p3 = p2 + (p1 << 2);
                y_tmp[p3] = 0.0;
                y_tmp[p3] += b_b[3 * p1] * y_tmp_0[p2];
                y_tmp[p3] += b_b[3 * p1 + 1] * y_tmp_0[p2 + 4];
                y_tmp[p3] += b_b[3 * p1 + 2] * y_tmp_0[p2 + 8];
            }

            rtb_Derivative2[p1] = (real_T)a[p1 + 6] * tmp[2] + ((real_T)a[p1 + 3] *
                tmp[1] + (real_T)a[p1] * tmp[0]);
        }

        B_tmp = rtb_Derivative2_0[0] + rtb_Derivative2[0];
        SineWave1_tmp = rtb_Derivative2_0[1] + rtb_Derivative2[1];
        absx11_tmp = rtb_Derivative2_0[2] + rtb_Derivative2[2];
        for (p1 = 0; p1 < 4; p1++) {
            absx11 = y_tmp[p1 + 8] * absx11_tmp + (y_tmp[p1 + 4] * SineWave1_tmp +
                y_tmp[p1] * B_tmp);

            /* Saturate: '<Root>/Saturation' */
            if (absx11 > 10.0) {
                absx11 = 10.0;
            }
            else {
                if (absx11 < -10.0) {
                    absx11 = -10.0;
                }
            }

            /* Outport: '<Root>/Tp' */
            rtY.Tp[p1] = absx11;
            rtb_Saturation[p1] = absx11;
        }

        /* End of MATLAB Function: '<S1>/control' */

        /* Integrator: '<S2>/Integrator' */
        rtDW.Integrator[0] = rtX.Integrator_CSTATE[0];
        rtDW.Integrator[1] = rtX.Integrator_CSTATE[1];
        rtDW.Integrator[2] = rtX.Integrator_CSTATE[2];

        /* MATLAB Function: '<S2>/robot' incorporates:
         *  Integrator: '<S2>/Integrator1'
         */
        SineWave1_tmp = rtDW.Integrator[2];
        ym = cos(rtX.Integrator1_CSTATE[2]);
        absx11 = sin(rtX.Integrator1_CSTATE[2]);
        B_0[0] = (ym + absx11) * 20.833333333333332;
        B_0[3] = (ym - absx11) * 20.833333333333332;
        B_tmp = (cos(rtX.Integrator1_CSTATE[2]) + sin(rtX.Integrator1_CSTATE[2])) *
            20.833333333333332;
        B_0[6] = B_tmp;
        B_0[9] = (cos(rtX.Integrator1_CSTATE[2]) - sin(rtX.Integrator1_CSTATE[2])) *
            20.833333333333332;
        B_0[1] = (-ym + absx11) * 20.833333333333332;
        B_0[4] = B_tmp;
        B_0[7] = (-cos(rtX.Integrator1_CSTATE[2]) + sin(rtX.Integrator1_CSTATE[2])) *
            20.833333333333332;
        B_0[10] = B_tmp;
        B_0[2] = -12.499999999999998;
        B_0[5] = 12.499999999999998;
        B_0[8] = 12.499999999999998;
        B_0[11] = -12.499999999999998;
        xm = ym * rtDW.Integrator[0] + absx11 * rtDW.Integrator[1];
        ym = -absx11 * rtDW.Integrator[0] + ym * rtDW.Integrator[1];
        if (xm > 0.1) {
            xm = 0.1;
        }
        else {
            if (xm < -0.1) {
                xm = -0.1;
            }
        }

        if (ym > 0.1) {
            ym = 0.1;
        }
        else {
            if (ym < -0.1) {
                ym = -0.1;
            }
        }

        if (rtDW.Integrator[2] > 0.1) {
            SineWave1_tmp = 0.1;
        }
        else {
            if (rtDW.Integrator[2] < -0.1) {
                SineWave1_tmp = -0.1;
            }
        }

        absx11_tmp = xm - ym;
        absx11 = (absx11_tmp - 0.6 * SineWave1_tmp) * 20.833333333333332;
        B_tmp = xm + ym;
        absx21 = (B_tmp + 0.6 * SineWave1_tmp) * 20.833333333333332;
        absx31 = (absx11_tmp + 0.6 * SineWave1_tmp) * 20.833333333333332;
        SineWave1_tmp = (B_tmp - 0.6 * SineWave1_tmp) * 20.833333333333332;
        rtb_Derivative_idx_0 = rtb_Saturation[0];
        rtb_Derivative_idx_1 = rtb_Saturation[1];
        rtb_Derivative_idx_2 = rtb_Saturation[2];
        rtb_Saturation_idx_3 = rtb_Saturation[3];
        tmp[0] = 178.61111111111111 * rtDW.Integrator[1] * rtDW.Integrator[2];
        tmp[1] = -178.61111111111111 * rtDW.Integrator[0] * rtDW.Integrator[2];
        tmp[2] = 0.0;
        if (absx11 < 0.0) {
            B_tmp = -1.0;
        }
        else if (absx11 > 0.0) {
            B_tmp = 1.0;
        }
        else if (absx11 == 0.0) {
            B_tmp = 0.0;
        }
        else {
            B_tmp = (rtNaN);
        }

        B_tmp *= 0.0058860000000000006;
        if (absx21 < 0.0) {
            absx11_tmp = -1.0;
        }
        else if (absx21 > 0.0) {
            absx11_tmp = 1.0;
        }
        else if (absx21 == 0.0) {
            absx11_tmp = 0.0;
        }
        else {
            absx11_tmp = (rtNaN);
        }

        absx11_tmp *= 0.0058860000000000006;
        if (absx31 < 0.0) {
            ym = -1.0;
        }
        else if (absx31 > 0.0) {
            ym = 1.0;
        }
        else if (absx31 == 0.0) {
            ym = 0.0;
        }
        else {
            ym = (rtNaN);
        }

        ym *= 0.0058860000000000006;
        if (SineWave1_tmp < 0.0) {
            xm = -1.0;
        }
        else if (SineWave1_tmp > 0.0) {
            xm = 1.0;
        }
        else if (SineWave1_tmp == 0.0) {
            xm = 0.0;
        }
        else {
            xm = (rtNaN);
        }

        xm *= 0.0058860000000000006;
        for (p1 = 0; p1 < 3; p1++) {
            B_1 = B_0[p1];
            tmp_0 = B_1 * B_tmp;
            B_2 = B_1 * rtb_Derivative_idx_0;
            B_1 = B_0[p1 + 3];
            tmp_0 += B_1 * absx11_tmp;
            B_2 += B_1 * rtb_Derivative_idx_1;
            B_1 = B_0[p1 + 6];
            tmp_0 += B_1 * ym;
            B_2 += B_1 * rtb_Derivative_idx_2;
            B_1 = B_0[p1 + 9];
            tmp_0 += B_1 * xm;
            B_2 += B_1 * rtb_Saturation_idx_3;
            rtb_Derivative2_0[p1] = (B_2 - tmp[p1]) - tmp_0;
        }

        for (p1 = 0; p1 < 3; p1++) {
            rtDW.Q_2dot[p1] = 0.0;
            rtDW.Q_2dot[p1] += b_a[p1] * rtb_Derivative2_0[0];
            rtDW.Q_2dot[p1] += b_a[p1 + 3] * rtb_Derivative2_0[1];
            rtDW.Q_2dot[p1] += b_a[p1 + 6] * rtb_Derivative2_0[2];
        }

        /* Outport: '<Root>/w1' incorporates:
         *  MATLAB Function: '<S2>/robot'
         */
        rtY.w1 = absx11;

        /* Outport: '<Root>/w2' incorporates:
         *  MATLAB Function: '<S2>/robot'
         */
        rtY.w2 = absx21;

        /* Outport: '<Root>/w3' incorporates:
         *  MATLAB Function: '<S2>/robot'
         */
        rtY.w3 = absx31;

        /* Outport: '<Root>/w4' incorporates:
         *  MATLAB Function: '<S2>/robot'
         */
        rtY.w4 = SineWave1_tmp;
    }

    if (rtmIsMajorTimeStep(rtM)) {
        real_T(*lastU)[3];

        /* Update for Derivative: '<S1>/Derivative1' incorporates:
         *  Constant: '<Root>/Constant2'
         */
        if (rtDW.TimeStampA == (rtInf)) {
            rtDW.TimeStampA = rtM->Timing.t[0];
            lastU = &rtDW.LastUAtTimeA;
        }
        else if (rtDW.TimeStampB == (rtInf)) {
            rtDW.TimeStampB = rtM->Timing.t[0];
            lastU = &rtDW.LastUAtTimeB;
        }
        else if (rtDW.TimeStampA < rtDW.TimeStampB) {
            rtDW.TimeStampA = rtM->Timing.t[0];
            lastU = &rtDW.LastUAtTimeA;
        }
        else {
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
        }
        else if (rtDW.TimeStampB_i == (rtInf)) {
            rtDW.TimeStampB_i = rtM->Timing.t[0];
            lastU = &rtDW.LastUAtTimeB_o;
        }
        else if (rtDW.TimeStampA_m < rtDW.TimeStampB_i) {
            rtDW.TimeStampA_m = rtM->Timing.t[0];
            lastU = &rtDW.LastUAtTimeA_d;
        }
        else {
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
        }
        else if (rtDW.TimeStampB_g == (rtInf)) {
            rtDW.TimeStampB_g = rtM->Timing.t[0];
            lastU = &rtDW.LastUAtTimeB_on;
        }
        else if (rtDW.TimeStampA_o < rtDW.TimeStampB_g) {
            rtDW.TimeStampA_o = rtM->Timing.t[0];
            lastU = &rtDW.LastUAtTimeA_k;
        }
        else {
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
            /* Update absolute timer for sample time: [0.05s, 0.0s] */
            /* The "clockTick1" counts the number of times the code of this task has
             * been executed. The resolution of this integer timer is 0.05, which is the step size
             * of the task. Size of "clockTick1" ensures timer will not overflow during the
             * application lifespan selected.
             */
            rtM->Timing.clockTick1++;
        }
    }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void last8_derivatives(void)
{
    XDot* _rtXdot;
    _rtXdot = ((XDot*)rtM->derivs);

    /* Derivatives for Integrator: '<S2>/Integrator' */
    _rtXdot->Integrator_CSTATE[0] = rtDW.Q_2dot[0];

    /* Derivatives for Integrator: '<S2>/Integrator1' */
    _rtXdot->Integrator1_CSTATE[0] = rtDW.Integrator[0];

    /* Derivatives for Integrator: '<S2>/Integrator' */
    _rtXdot->Integrator_CSTATE[1] = rtDW.Q_2dot[1];

    /* Derivatives for Integrator: '<S2>/Integrator1' */
    _rtXdot->Integrator1_CSTATE[1] = rtDW.Integrator[1];

    /* Derivatives for Integrator: '<S2>/Integrator' */
    _rtXdot->Integrator_CSTATE[2] = rtDW.Q_2dot[2];

    /* Derivatives for Integrator: '<S2>/Integrator1' */
    _rtXdot->Integrator1_CSTATE[2] = rtDW.Integrator[2];
}

/* Model initialize function */
void last8_initialize(void)
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
        rtsiSetContStatesPtr(&rtM->solverInfo, (real_T**)&rtM->contStates);
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
    rtM->contStates = ((X*)&rtX);
    rtsiSetSolverData(&rtM->solverInfo, (void*)&rtM->intgData);
    rtsiSetSolverName(&rtM->solverInfo, "ode4");
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

    /* InitializeConditions for Integrator: '<S2>/Integrator' */
    rtX.Integrator_CSTATE[0] = 0.0;

    /* InitializeConditions for Integrator: '<S2>/Integrator1' */
    rtX.Integrator1_CSTATE[0] = 1.5;

    /* InitializeConditions for Integrator: '<S2>/Integrator' */
    rtX.Integrator_CSTATE[1] = 0.0;

    /* InitializeConditions for Integrator: '<S2>/Integrator1' */
    rtX.Integrator1_CSTATE[1] = 1.2;

    /* InitializeConditions for Integrator: '<S2>/Integrator' */
    rtX.Integrator_CSTATE[2] = 0.0;

    /* InitializeConditions for Integrator: '<S2>/Integrator1' */
    rtX.Integrator1_CSTATE[2] = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
