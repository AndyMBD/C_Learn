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
/**
 * \file     adc1.h
 *
 * \brief    ADC1 low level access library
 *
 * \version  V0.2.8
 * \date     23. Apr 2021
 *
 * \note This file violates [MISRA Rule 45]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** DCM          Dragos C. Molocea                                             **
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.1: 2015-02-10, DM:   Individual header file added                     **
** V0.1.2: 2015-03-10, DM:   MF->REF2_CTRL added                              **
** V0.1.3: 2015-03-22, DM:   ADC Busy function added                          **
** V0.1.4: 2015-11-26, DM:   VAREF enable function added                      **
** V0.1.5: 2017-02-16, DM:   the attenuator for Channel 6 (VDH) voltage       **
**                           calculation added                                **
**                           Adc1 prefix changed to ADC1                      **
** V0.1.6: 2017-03-23, DM:   ADC1 API extended                                **
** V0.1.7: 2017-11-09, DM:   Port2 analog input init added                    **
** V0.1.8: 2017-11-13, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
**                           Replaced macros by INLINE functions              **
**                           Replaced register accesses within functions by   **
**                           function calls                                   **
**                           Replaced __STATIC_INLINE by INLINE               **
** V0.1.9: 2018-03-14, DM:   VAREF_Enable() reworked for MISRA 2012           **
**                           ADC1_MASK_CHx macros rworked for MISRA 2012      **
**                           ADC1_ANON_Sts() converted to infline function    **
**                           due to MISRA 2012                                **
** V0.2.0: 2018-06-27, DCM:  Conversion formula from digital value to         **
**                           millivolts changed based on the software unit    **
**                           test findings and simplified according to the    **
**                           new specifications                               **
** V0.2.1: 2018-07-05, BG:   In adc1.h: ADC1_Chx_Result_Get(),                **
**                           ADC1_EIM_Channel_Set(uint32),                    **
**                           ADC1_SW_Ch_Sel(uint32), ADC1_SOC_Set(),          **
**                           ADC1_ANON_Set(uint32), ADC1_Power_On(),          **
**                           ADC1_EOC_Sts(), ADC1_Busy_Sts(),                 **
**                           ADC1_EIM_Active_Sts(), ADC1_ESM_Active_Sts()     **
**                           reworked for testing lv2 functions               **
** V0.2.2: 2018-08-01, DM:   DoxyGen comments updated,                        **
** V0.2.3: 2018-11-09, JO:   Renamed:                                         **
**                           - ADC1_VDH_Attenuator_Range_0_22V_Set to         **
**                             ADC1_VDH_Attenuator_Range_0_20V_Set            **
**                           - ADC1_VDH_Attenuator_Range_0_28V_Set to         **
**                             ADC1_VDH_Attenuator_Range_0_30V_Set            **
**                           - ADC1_VDH_Attenuator_Range_0_22V to             **
**                             ADC1_VDH_Attenuator_Range_0_20V                **
**                           - ADC1_VDH_Attenuator_Range_0_28V to             **
**                             ADC1_VDH_Attenuator_Range_0_30V                **
** V0.2.4: 2018-11-27, JO:   Moved revision history from adc1.c to adc1.h     **
** V0.2.5: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.6: 2020-07-13, JO:   EP-431: remove ARMCC v6 Compiler warnings        **
**                           - Added typecasts to remove 'implicit typecast'  **
**                             warning                                        **
** V0.2.7: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.2.8: 2021-04-23, BG:   EP-726: Corrected MISRA 2012 violations          **
*******************************************************************************//*
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
/**
 * \file     scheduler.h
 *
 * \brief    ADC1 low level access library
 *
 * \version  V0.0.0
 * \date     8. May 2021
 *
 * \note This file violates [MISRA Rule 45]
 */

/*******************************************************************************
**                             Author(s) Identity                             **
********************************************************************************
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** DM           Daniel Mysliwitz                                              **
** DCM          Dragos C. Molocea                                             **
** BG           Blandine Guillot                                              **
** JO           Julia Ott                                                     **
*******************************************************************************/

/*******************************************************************************
**                          Revision Control History                          **
********************************************************************************
** V0.1.1: 2015-02-10, DM:   Individual header file added                     **
** V0.1.2: 2015-03-10, DM:   MF->REF2_CTRL added                              **
** V0.1.3: 2015-03-22, DM:   ADC Busy function added                          **
** V0.1.4: 2015-11-26, DM:   VAREF enable function added                      **
** V0.1.5: 2017-02-16, DM:   the attenuator for Channel 6 (VDH) voltage       **
**                           calculation added                                **
**                           Adc1 prefix changed to ADC1                      **
** V0.1.6: 2017-03-23, DM:   ADC1 API extended                                **
** V0.1.7: 2017-11-09, DM:   Port2 analog input init added                    **
** V0.1.8: 2017-11-13, DM:   MISRA 2012 compliance, the following PC-Lint     **
**                           rules are globally deactivated:                  **
**                           - Info 793: ANSI/ISO limit of 6 'significant     **
**                             characters in an external identifier           **
**                           - Info 835: A zero has been given as right       **
**                             argument to operator                           **
**                           - Info 845: The left argument to operator '&'    **
**                             is certain to be 0                             **
**                           Replaced macros by INLINE functions              **
**                           Replaced register accesses within functions by   **
**                           function calls                                   **
**                           Replaced __STATIC_INLINE by INLINE               **
** V0.1.9: 2018-03-14, DM:   VAREF_Enable() reworked for MISRA 2012           **
**                           ADC1_MASK_CHx macros rworked for MISRA 2012      **
**                           ADC1_ANON_Sts() converted to infline function    **
**                           due to MISRA 2012                                **
** V0.2.0: 2018-06-27, DCM:  Conversion formula from digital value to         **
**                           millivolts changed based on the software unit    **
**                           test findings and simplified according to the    **
**                           new specifications                               **
** V0.2.1: 2018-07-05, BG:   In adc1.h: ADC1_Chx_Result_Get(),                **
**                           ADC1_EIM_Channel_Set(uint32),                    **
**                           ADC1_SW_Ch_Sel(uint32), ADC1_SOC_Set(),          **
**                           ADC1_ANON_Set(uint32), ADC1_Power_On(),          **
**                           ADC1_EOC_Sts(), ADC1_Busy_Sts(),                 **
**                           ADC1_EIM_Active_Sts(), ADC1_ESM_Active_Sts()     **
**                           reworked for testing lv2 functions               **
** V0.2.2: 2018-08-01, DM:   DoxyGen comments updated,                        **
** V0.2.3: 2018-11-09, JO:   Renamed:                                         **
**                           - ADC1_VDH_Attenuator_Range_0_22V_Set to         **
**                             ADC1_VDH_Attenuator_Range_0_20V_Set            **
**                           - ADC1_VDH_Attenuator_Range_0_28V_Set to         **
**                             ADC1_VDH_Attenuator_Range_0_30V_Set            **
**                           - ADC1_VDH_Attenuator_Range_0_22V to             **
**                             ADC1_VDH_Attenuator_Range_0_20V                **
**                           - ADC1_VDH_Attenuator_Range_0_28V to             **
**                             ADC1_VDH_Attenuator_Range_0_30V                **
** V0.2.4: 2018-11-27, JO:   Moved revision history from adc1.c to adc1.h     **
** V0.2.5: 2020-04-15, BG:   Updated revision history format                  **
** V0.2.6: 2020-07-13, JO:   EP-431: remove ARMCC v6 Compiler warnings        **
**                           - Added typecasts to remove 'implicit typecast'  **
**                             warning                                        **
** V0.2.7: 2020-07-21, BG:   EP-439: Formatted .h/.c files                    **
** V0.2.8: 2021-04-23, BG:   EP-726: Corrected MISRA 2012 violations          **
*******************************************************************************/
#ifndef SCHEDULER_H_
#define SCHEDULER_H_
/*******************************************************************************
**                                  Includes                                  **
*******************************************************************************/
#include "types.h"
/** is set to 1 by ISR every 1ms. Has to be reset by application */
extern volatile bool b1msTick;	
extern void scheduler(void);
#endif /* SCHEDULER_H_ */