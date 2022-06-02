/*
 ***********************************************************************************************************************
 *
 * Copyright (c) 2015, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 **********************************************************************************************************************/

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** BG           Blandine Guillot                                              **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V1.0.0: 2020-04-15, BG:   Initial version of revision history              **
** V1.0.1: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V1.0.2: 2020-08-04, BG:   EP-431: Fixed ARMCC v6 compiler warnings         **
*******************************************************************************/

/*******************************************************************************
**                                  Abstract                                  **
********************************************************************************
** systick: 1ms                                                             **
********************************************************************************
** sys is configured as timer with a runtime of 1ms. For each overflow,  **
** the interrupt routine Task_1ms is called scheduler.               **
*******************************************************************************/

#include "tle_device.h"
#include "eval_board.h"
#include "scheduler.h"

int main(void)
{
  /* Initialization of hardware modules based on Config Wizard configuration */
  TLE_Init();
  Led_Blink_initialize();
  /* Start Timer2 */
//  TIMER2_Start();

  for (;;)
  {
    
    
    scheduler();
  }
}


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wmissing-prototypes"
#endif

void Task_100ms(void)
{
//  b1msTick = true;
    PORT_ChangePin(LED1, PORT_ACTION_TOGGLE);
}
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6000000)
  #pragma clang diagnostic pop
#endif
