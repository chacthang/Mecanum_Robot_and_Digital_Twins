/*
 * File: digitaltwins_2_private.h
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

#ifndef RTW_HEADER_digitaltwins_2_private_h_
#define RTW_HEADER_digitaltwins_2_private_h_
#include "rtwtypes.h"

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

/* private model entry point functions */
extern void digitaltwins_2_derivatives(void);

#endif                                /* RTW_HEADER_digitaltwins_2_private_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
