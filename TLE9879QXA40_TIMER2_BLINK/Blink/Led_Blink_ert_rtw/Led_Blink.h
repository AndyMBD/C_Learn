/*
 * File: Led_Blink.h
 *
 * Code generated for Simulink model 'Led_Blink'.
 *
 * Model version                  : 7.0
 * Simulink Coder version         : 9.6 (R2021b) 14-May-2021
 * C/C++ source code generated on : Wed Jun  1 21:03:42 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Led_Blink_h_
#define RTW_HEADER_Led_Blink_h_
#include <string.h>
#ifndef Led_Blink_COMMON_INCLUDES_
#define Led_Blink_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Led_Blink_COMMON_INCLUDES_ */

#include "Led_Blink_types.h"

/* Macros for accessing real-time model data structure */

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int32_T clockTickCounter;            /* '<Root>/Pulse Generator' */
} DW_Led_Blink_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T Out1;                        /* '<Root>/Out1' */
} ExtY_Led_Blink_T;

/* Block states (default storage) */
extern DW_Led_Blink_T Led_Blink_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Led_Blink_T Led_Blink_Y;

/* Model entry point functions */
extern void Led_Blink_initialize(void);
extern void Led_Blink_step(void);
extern void Led_Blink_terminate(void);

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
 * '<Root>' : 'Led_Blink'
 */
#endif                                 /* RTW_HEADER_Led_Blink_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
