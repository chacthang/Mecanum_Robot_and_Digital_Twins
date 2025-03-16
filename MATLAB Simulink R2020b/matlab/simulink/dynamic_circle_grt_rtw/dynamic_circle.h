/*
 * dynamic_circle.h
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

#ifndef RTW_HEADER_dynamic_circle_h_
#define RTW_HEADER_dynamic_circle_h_
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>
#ifndef dynamic_circle_COMMON_INCLUDES_
#define dynamic_circle_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#endif                                 /* dynamic_circle_COMMON_INCLUDES_ */

#include "dynamic_circle_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

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

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T SineWave1;                    /* '<Root>/Sine Wave1' */
  real_T SineWave;                     /* '<Root>/Sine Wave' */
  real_T Derivative1[3];               /* '<S1>/Derivative1' */
  real_T Sum[3];                       /* '<S1>/Sum' */
  real_T Integrator[3];                /* '<S2>/Integrator' */
  real_T Q_2dot[3];                    /* '<S2>/robot' */
} B_dynamic_circle_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T TimeStampA;                   /* '<S1>/Derivative1' */
  real_T LastUAtTimeA[3];              /* '<S1>/Derivative1' */
  real_T TimeStampB;                   /* '<S1>/Derivative1' */
  real_T LastUAtTimeB[3];              /* '<S1>/Derivative1' */
  real_T TimeStampA_m;                 /* '<S1>/Derivative2' */
  real_T LastUAtTimeA_d[3];            /* '<S1>/Derivative2' */
  real_T TimeStampB_i;                 /* '<S1>/Derivative2' */
  real_T LastUAtTimeB_o[3];            /* '<S1>/Derivative2' */
  real_T TimeStampA_o;                 /* '<S1>/Derivative' */
  real_T LastUAtTimeA_k[3];            /* '<S1>/Derivative' */
  real_T TimeStampB_g;                 /* '<S1>/Derivative' */
  real_T LastUAtTimeB_on[3];           /* '<S1>/Derivative' */
} DW_dynamic_circle_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
} X_dynamic_circle_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
} XDot_dynamic_circle_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE[3];     /* '<S2>/Integrator1' */
  boolean_T Integrator_CSTATE[3];      /* '<S2>/Integrator' */
} XDis_dynamic_circle_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T w1;                           /* '<Root>/w1' */
  real_T w2;                           /* '<Root>/w2' */
  real_T w3;                           /* '<Root>/w3' */
  real_T w4;                           /* '<Root>/w4' */
} ExtY_dynamic_circle_T;

/* Real-time Model Data Structure */
struct tag_RTM_dynamic_circle_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_dynamic_circle_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[6];
  real_T odeF[3][6];
  ODE3_IntgData intgData;

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
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_dynamic_circle_T dynamic_circle_B;

/* Continuous states (default storage) */
extern X_dynamic_circle_T dynamic_circle_X;

/* Block states (default storage) */
extern DW_dynamic_circle_T dynamic_circle_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_dynamic_circle_T dynamic_circle_Y;

/* Model entry point functions */
extern void dynamic_circle_initialize(void);
extern void dynamic_circle_step(void);
extern void dynamic_circle_terminate(void);

/* Real-time Model object */
extern RT_MODEL_dynamic_circle_T *const dynamic_circle_M;

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
 * '<Root>' : 'dynamic_circle'
 * '<S1>'   : 'dynamic_circle/CONTROL'
 * '<S2>'   : 'dynamic_circle/Physical Plant'
 * '<S3>'   : 'dynamic_circle/CONTROL/control'
 * '<S4>'   : 'dynamic_circle/CONTROL/x2r'
 * '<S5>'   : 'dynamic_circle/Physical Plant/robot'
 */
#endif                                 /* RTW_HEADER_dynamic_circle_h_ */
