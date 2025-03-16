/*
 * File: digitaltwins_3.h
 *
 * Code generated for Simulink model 'digitaltwins_3'.
 *
 * Model version                  : 7.72
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Sat May 18 19:59:42 2024
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Linux 64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_digitaltwins_3_h_
#define RTW_HEADER_digitaltwins_3_h_
#include <math.h>
#include <string.h>
#include <stddef.h>
#ifndef digitaltwins_3_COMMON_INCLUDES_
#define digitaltwins_3_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* digitaltwins_3_COMMON_INCLUDES_ */

#include "digitaltwins_3_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"

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

/* Block signals (default storage) */
typedef struct {
  real_T SineWave1;                    /* '<Root>/Sine Wave1' */
  real_T SineWave;                     /* '<Root>/Sine Wave' */
  real_T Derivative1[3];               /* '<S1>/Derivative1' */
  real_T Sum[3];                       /* '<S1>/Sum' */
  real_T Integrator1[3];               /* '<S2>/Integrator1' */
  real_T Derivative1_j[3];             /* '<S7>/Derivative1' */
  real_T Sum_m[3];                     /* '<S7>/Sum' */
  real_T Integrator[3];                /* '<S2>/Integrator' */
  real_T Integrator_k[3];              /* '<S9>/Integrator' */
  real_T Qp_2dot[3];                   /* '<S9>/Virtual robot' */
  real_T Q_2dot[3];                    /* '<S2>/MATLAB Function1' */
} B_digitaltwins_3_T;

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
  real_T TimeStampA_j;                 /* '<S7>/Derivative1' */
  real_T LastUAtTimeA_f[3];            /* '<S7>/Derivative1' */
  real_T TimeStampB_m;                 /* '<S7>/Derivative1' */
  real_T LastUAtTimeB_o2[3];           /* '<S7>/Derivative1' */
  real_T TimeStampA_g;                 /* '<S7>/Derivative2' */
  real_T LastUAtTimeA_b[3];            /* '<S7>/Derivative2' */
  real_T TimeStampB_d;                 /* '<S7>/Derivative2' */
  real_T LastUAtTimeB_c[3];            /* '<S7>/Derivative2' */
  real_T TimeStampA_g5;                /* '<S7>/Derivative' */
  real_T LastUAtTimeA_o[3];            /* '<S7>/Derivative' */
  real_T TimeStampB_a;                 /* '<S7>/Derivative' */
  real_T LastUAtTimeB_e[3];            /* '<S7>/Derivative' */
} DW_digitaltwins_3_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator_CSTATE_c[3];       /* '<S9>/Integrator' */
  real_T Integrator1_CSTATE_n[3];      /* '<S9>/Integrator1' */
} X_digitaltwins_3_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator_CSTATE_c[3];       /* '<S9>/Integrator' */
  real_T Integrator1_CSTATE_n[3];      /* '<S9>/Integrator1' */
} XDot_digitaltwins_3_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator1_CSTATE[3];     /* '<S2>/Integrator1' */
  boolean_T Integrator_CSTATE[3];      /* '<S2>/Integrator' */
  boolean_T Integrator_CSTATE_c[3];    /* '<S9>/Integrator' */
  boolean_T Integrator1_CSTATE_n[3];   /* '<S9>/Integrator1' */
} XDis_digitaltwins_3_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T Q[3];                         /* '<Root>/Q' */
  real_T Q_dot[3];                     /* '<Root>/Q_dot' */
  real_T Qv[3];                        /* '<Root>/Qv' */
  real_T Qv_dot[3];                    /* '<Root>/Qv_dot' */
} ExtU_digitaltwins_3_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T w1;                           /* '<Root>/w1' */
  real_T w2;                           /* '<Root>/w2' */
  real_T w3;                           /* '<Root>/w3' */
  real_T w4;                           /* '<Root>/w4' */
  real_T w5;                           /* '<Root>/w5' */
  real_T w6;                           /* '<Root>/w6' */
  real_T w7;                           /* '<Root>/w7' */
  real_T w8;                           /* '<Root>/w8' */
  real_T Tp[4];                        /* '<Root>/Tp' */
  real_T Tv[4];                        /* '<Root>/Tv' */
} ExtY_digitaltwins_3_T;

/* Real-time Model Data Structure */
struct tag_RTM_digitaltwins_3_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_digitaltwins_3_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[12];
  real_T odeF[3][12];
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
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block signals (default storage) */
extern B_digitaltwins_3_T digitaltwins_3_B;

/* Continuous states (default storage) */
extern X_digitaltwins_3_T digitaltwins_3_X;

/* Block states (default storage) */
extern DW_digitaltwins_3_T digitaltwins_3_DW;

/* External inputs (root inport signals with default storage) */
extern __declspec(dllexport) ExtU_digitaltwins_3_T digitaltwins_3_U;

__declspec(dllexport) ExtU_digitaltwins_3_T* get_rtU() {
    return &digitaltwins_3_U;
}

/* External outputs (root outports fed by signals with default storage) */
extern __declspec(dllexport) ExtY_digitaltwins_3_T digitaltwins_3_Y;

__declspec(dllexport) ExtY_digitaltwins_3_T* get_rtY() {
    return &digitaltwins_3_Y;
}

/* Model entry point functions */
extern __declspec(dllexport) void digitaltwins_3_initialize(void);
extern __declspec(dllexport) void digitaltwins_3_step(void);
extern void digitaltwins_3_terminate(void);

/* Real-time Model object */
extern RT_MODEL_digitaltwins_3_T *const digitaltwins_3_M;

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
 * '<Root>' : 'digitaltwins_3'
 * '<S1>'   : 'digitaltwins_3/CONTROL'
 * '<S2>'   : 'digitaltwins_3/Physical Plant'
 * '<S3>'   : 'digitaltwins_3/Virtual Plant'
 * '<S4>'   : 'digitaltwins_3/CONTROL/MATLAB Function'
 * '<S5>'   : 'digitaltwins_3/CONTROL/x2r'
 * '<S6>'   : 'digitaltwins_3/Physical Plant/MATLAB Function1'
 * '<S7>'   : 'digitaltwins_3/Virtual Plant/CONTROL 2'
 * '<S8>'   : 'digitaltwins_3/Virtual Plant/Qv_'
 * '<S9>'   : 'digitaltwins_3/Virtual Plant/Virtual Plant'
 * '<S10>'  : 'digitaltwins_3/Virtual Plant/CONTROL 2/MATLAB Function'
 * '<S11>'  : 'digitaltwins_3/Virtual Plant/CONTROL 2/x2r'
 * '<S12>'  : 'digitaltwins_3/Virtual Plant/Virtual Plant/Virtual robot'
 */
#endif                                 /* RTW_HEADER_digitaltwins_3_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
