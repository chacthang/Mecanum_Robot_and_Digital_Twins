/*
 * File: dynamic_8_g.h
 *
 * Code generated for Simulink model 'dynamic_8_g'.
 *
 * Model version                  : 7.82
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Sun Jun  2 00:17:03 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_dynamic_8_g_h_
#define RTW_HEADER_dynamic_8_g_h_
#include <stddef.h>
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef dynamic_8_g_COMMON_INCLUDES_
#define dynamic_8_g_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* dynamic_8_g_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Derivative1[3];               /* '<S1>/Derivative1' */
  real_T Sum[3];                       /* '<S1>/Sum' */
  real_T Integrator[3];                /* '<S2>/Integrator' */
  real_T Q_2dot[3];                    /* '<S2>/robot' */
  real_T LastUAtTimeA[3];              /* '<S1>/Derivative1' */
  real_T LastUAtTimeB[3];              /* '<S1>/Derivative1' */
  real_T LastUAtTimeA_d[3];            /* '<S1>/Derivative2' */
  real_T LastUAtTimeB_o[3];            /* '<S1>/Derivative2' */
  real_T LastUAtTimeA_k[3];            /* '<S1>/Derivative' */
  real_T LastUAtTimeB_on[3];           /* '<S1>/Derivative' */
  real_T SineWave1;                    /* '<Root>/Sine Wave1' */
  real_T SineWave;                     /* '<Root>/Sine Wave' */
  real_T TimeStampA;                   /* '<S1>/Derivative1' */
  real_T TimeStampB;                   /* '<S1>/Derivative1' */
  real_T TimeStampA_m;                 /* '<S1>/Derivative2' */
  real_T TimeStampB_i;                 /* '<S1>/Derivative2' */
  real_T TimeStampA_o;                 /* '<S1>/Derivative' */
  real_T TimeStampB_g;                 /* '<S1>/Derivative' */
  int_T Integrator1_IWORK;             /* '<S2>/Integrator1' */
} DW;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
} X;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<S2>/Integrator' */
  boolean_T Integrator1_CSTATE[3];     /* '<S2>/Integrator1' */
} XDis;

#ifndef ODE5_INTG
#define ODE5_INTG

/* ODE5 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[6];                        /* derivatives */
} ODE5_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T x;                            /* '<Root>/x' */
  real_T y;                            /* '<Root>/y' */
  real_T theta;                        /* '<Root>/theta' */
  real_T vx;                           /* '<Root>/vx' */
  real_T vy;                           /* '<Root>/vy' */
  real_T theta_dot;                    /* '<Root>/theta_dot' */
  real_T x0;                           /* '<Root>/x0' */
  real_T y0;                           /* '<Root>/y0' */
  real_T theta0;                       /* '<Root>/theta0' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T w1;                           /* '<Root>/w1' */
  real_T w2;                           /* '<Root>/w2' */
  real_T w3;                           /* '<Root>/w3' */
  real_T w4;                           /* '<Root>/w4' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[6];
  real_T odeF[6][6];
  ODE5_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    boolean_T firstInitCondFlag;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Continuous states (default storage) */
extern X rtX;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void dynamic_8_g_initialize(void);
extern void dynamic_8_g_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'dynamic_8_g'
 * '<S1>'   : 'dynamic_8_g/CONTROL'
 * '<S2>'   : 'dynamic_8_g/Physical Plant'
 * '<S3>'   : 'dynamic_8_g/CONTROL/control'
 * '<S4>'   : 'dynamic_8_g/CONTROL/x2r'
 * '<S5>'   : 'dynamic_8_g/Physical Plant/robot'
 */
#endif                                 /* RTW_HEADER_dynamic_8_g_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
