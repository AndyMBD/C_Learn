/*
 * File: Led_Blink.c
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

#include "Led_Blink.h"
#include "Led_Blink_private.h"

/* Block states (default storage) */
DW_Led_Blink_T Led_Blink_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Led_Blink_T Led_Blink_Y;

/* Model step function */
void Led_Blink_step(void)
{
  int32_T rtb_PulseGenerator;

  /* DiscretePulseGenerator: '<Root>/Pulse Generator' */
  rtb_PulseGenerator = ((Led_Blink_DW.clockTickCounter < 500) &&
                        (Led_Blink_DW.clockTickCounter >= 0));
  if (Led_Blink_DW.clockTickCounter >= 999) {
    Led_Blink_DW.clockTickCounter = 0;
  } else {
    Led_Blink_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<Root>/Pulse Generator' */

  /* Outport: '<Root>/Out1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion'
   */
  Led_Blink_Y.Out1 = (uint8_T)rtb_PulseGenerator;
}

/* Model initialize function */
void Led_Blink_initialize(void)
{
  /* Registration code */

  /* states (dwork) */
  (void) memset((void *)&Led_Blink_DW, 0,
                sizeof(DW_Led_Blink_T));

  /* Start for DiscretePulseGenerator: '<Root>/Pulse Generator' */
  Led_Blink_DW.clockTickCounter = 0;
}

/* Model terminate function */
void Led_Blink_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
