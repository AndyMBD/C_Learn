/*------------------------------prevent recursive inclusion -------------------*/
#ifndef __PARAMETER_H
#define __PARAMETER_H

#include "stdint.h"
#include "stdbool.h"

/* -----------------------------Hardware Parameter---------------------------- */
#define ADC_REF_VOLTAGE (3.6) /* Unit:V  ADC Referance Voltage 3.6*/
/*ADC Resistor 5.1KR 200:10.4=(200/(10+5.1)=13.245 */
#define AMPLIFICATION_GAIN (13.245) /* Amplifer Gain*/

#define RSHUNT (0.05)                             /* Unit:ohm Current sense resistor resistance*/
#define VOLTAGE_SHUNT_RATIO (4.3 / (20.5 + 4.3)) //(6.8/(20 + 6.8))    /* Battery Voltage sense Ratio*/
// #define DC_BUS_RESISTOR         				28.0              //Value in KOhms; 1:28 is the voltage divider scale in HW
// #define BEMF_SHUNT_RATIO               (1.0/(10.0 + 1.0))  /* BEMF Voltage Sense Ratio*/

/*

$\frac{ADC}{1024}=\frac{V*\frac{6.8}{20+6.8}}{3.6}$
$V=ADC*\frac{3.6*26.8}{1024*6.8}$
$V=ADC*\frac{3.6*26.8}{1024*6.8}$
$V=ADC*0.01385$
*/
    /* data */
#define OVER_VOLTAGE_ENTRY_THRESHOLD        (16500)//mV
#define OVER_VOLTAGE_EXIT_THRESHOLD         (15500)//mV
#define UNDER_VOLTAGE_ENTRY_THRESHOLD       (6500)///mv
#define UNDER_VOLTAGE_EXIT_THRESHOLD        (7500)//mv
#define OVER_TEMPERATURE_ENTRY_THRESHOLD    (140)
#define OVER_TEMPERATURE_EXIT_THRESHOLD     (130)
// #define Left_Short_GND_Flag
// #define Left_Short_BAT_Flag
// #define Right_Short_GND_Flag
// #define Right_Short_BAT_Flag
#define OVER_CURRENT_ENTRY_THRESHOLD        (3.5)
#define OVER_CURRENT_EXIT_THRESHOLD         (3)
#define UNDER_CURRENT_ENTRY_THRESHOLD       (0.1)
#define UNDER_CURRENT_EXIT_THRESHOLD        (0.2)

// #define CURRENT_LOW_LIMIT            (-24320) /* 0A */
// #define CURRENT_HIGH_LIMIT            (24320) /* 2.5A 95<<8*/

#define REQ_POSITION_LPF_COEFF              (65535)  /* 65535*0.2 */
#define ACT_POSITION_LPF_COEFF              (65535)  /* 65535*0.003 */
#define POSITION_KP                         (500) /*Current loop Kp, Final Kp calculate according to this parameter and motor parameter*/
#define POSITION_KI                         (0) /*Current loop Ki, Final Ki calculate according to this parameter and motor parameter*/
#define SPEED_HIGH_LIMIT                    (65535*500)       /* 20*65535= 1310700*/
#define SPEED_LOW_LIMIT                     (-65535*500)       /*-20*65535  */

#define REQ_SPEED_LPF_COEFF                 (65535)  /* 65535*0.003 */
#define ACT_SPEED_LPF_COEFF                 (65535)  /* 65535*0.003 */
#define SPEED_KP                            (8000) /*Current loop Kp, Final Kp calculate according to this parameter and motor parameter*/
#define SPEED_KI                            (800) /*Current loop Ki, Final Ki calculate according to this parameter and motor parameter*/
#define CURRENT_HIGH_LIMIT                  (65535*500)   /* 65535*500mA */
#define CURRENT_LOW_LIMIT                   (-65535*500)//(-65535*500) /* 65535*500mA 2.5A 458ADC */
/* R_Sense = 0.01R */
/* OP_Gain = 12.9 */
/* I_Current = 1A */
/* ADC = I_Current*R_Sense*OP_Gain=1*(0.05*12.9*1023/3.6)*=1*183.28*/
/* 0.6A, the gear broken when crash with hard stop */
#define REQ_CURRENT_LPF_COEFF               (65535)  /* 65535*0.03 */
#define ACT_CURRENT_LPF_COEFF               (65535)  /* 65535*0.1 */
#define CURRENT_KP                          (8000) /*Current loop Kp, Final Kp calculate according to this parameter and motor parameter*/
#define CURRENT_KI                          (200)  /*Current loop Ki, Final Ki calculate according to this parameter and motor parameter*/
#define PWM_DUTYCYCLE_HIGH_LIMIT            (65535*2400*0.95)                  /* 95%*2400=2280 */
#define PWM_DUTYCYCLE_LOW_LIMIT             (-65535*2400*0.95) /* 5%*2400=120 */ /* 2400*0.95*65535=149419800.0 */

#define PEAK_PHASE_CURRENT (120)      /*Phase Current Peak Setting:mA According to Minebea Current Waveform Test result Vpp 0.227V,current peak is half 135mA */
#define PEAK_PHASE_CURRENT_ACC (10.0) /*Phase Current Increase Slop:Unit 1mA/10ms, Minum0.001*/
#define PEAK_PHASE_CURRENT_ECC (10.0) /*Phase Current Decrease Slop:Unit 1mA/10ms, Minum0.001*/
#define SPEED_CURR_VALUE (((float)PEAK_PHASE_CURRENT * 0x7ff0 * AMPLIFICATION_GAIN * RSHUNT * 512) / (ADC_REF_VOLTAGE * 1000))
#define SPEED_CURR_VALUE_ACC (((float)PEAK_PHASE_CURRENT_ACC * 0x7ff0 * AMPLIFICATION_GAIN * RSHUNT * 512) / (ADC_REF_VOLTAGE * 1000))
#define SPEED_CURR_VALUE_ECC (((float)PEAK_PHASE_CURRENT_ECC * 0x7ff0 * AMPLIFICATION_GAIN * RSHUNT * 512) / (ADC_REF_VOLTAGE * 1000))

#define ABNORMAL_CURRENT (FALSE) /*Phase current abnormal,not use. TRUE = Enable,FALSE =Disable*/

/*------------------------------------FaultDetection---------------------------*/

/* Over Current Protection Parameter */
#define I_PH_OVERCURRENT_FAULT (0.5)      /* Unit:A Over Current Set Point */
#define CURRENT_FAULT_RECOVER_TIME (2000) /* Unit:ms Over Current Recovery Time */

/* Over Under Voltage Protection Parameter */
#define VOLT_STATUS (FALSE)              /* Over/Under Voltage Detect Protection, TRUE =Enable FALSE =Disable*/
#define U_DCB_OVERVOLTAGE_FAULT (18)     /* Unit:V Over Voltage Entry Set Point */
#define U_DCB_OVERVOLTAGE_RECOVER (17)   /* Unit:V Over Voltage Recovery Set Point */
#define U_DCB_UNDERVOLTAGE_FAULT (8.0)   /* Unit:V Under Voltage Entry Set Point */
#define U_DCB_UNDERVOLTAGE_RECOVER (9.0) /* Unit:V Under Voltage Recovery Set Point */
#define VOLT_FAULT_RECOVER_TIME (2000)   /* Unit:ms Over/Under Voltage Recovery Time */

/* Over Temperature Protection Parameter*/
#define TEMP_STATUS (TRUE)             /* Over Temperature Protection, TRUE = Enable�� FALSE = Disable*/
#define TEMP_FAULT (1200)              /* Unit: 0.1 Degree Over Temperature Entry Point*/
#define TEMP_RECOVER (1000)            /* Unit: 0.1 Degree Over Temperature Exit Point*/
#define TEMP_FAULT_RECOVER_TIME (2000) /* Unit:ms Over Temperature Recovery Time*/

/* Stall Protection Parameter*/
//  TODO: Shall be test
//  FIXME:
//  BUG:
//  [1] :
#define STALL_STATUS (FALSE)    /* Stall Detection Protection, TRUE = Enable FALSE = Disable*/
#define TIME_PH_STALL_FAULT (0) /*unit : 5ms��start stall filter time*/
#define I_PH_STALL_FAULT (180)  /*unit:? shall set according to the test stall detection threshold*/
#define Eq_PH_Low_FAULT (300)
#define Eq_TH__FAULT (20)
#define STALL_ThresholdValue (60)       /* stall detection phase current Threshold,select a middle value between stall and normal running*/
#define STALL_FAULT_RECOVER_TIME (2000) /* Unit:ms Stall Fault Recovery Time*/

/* Phase Loss Protection Parameter */
#define PHASELOSS_STATUS (FALSE)          /* Phase Loss Protection, TRUE = Enable FALSE = Disable*/
#define PHASELOSS_FAULT_RECOVER_TIME (20) /* Unit:ms Phase Loss Fault Recovery Time*/

/* Fault Recovery Setting */
#define FAULT_RECOVER_STATUS (TRUE) /* Fault Recovery, TRUE = Enable, FALSE = Disable*/
/* potentimeter electronic range 10KR->330deg*/
/* potentimeter middle position is 5KR*/
/* CW  137.5 deg is */
/* CCW 137.5 deg is */
/* Start position is  137.5 deg */
#define Motor_Start_Position (TRUE)        /* Motor Start position ADC value*/
#define Motor_Start_Position_Offset (TRUE) /* Motor Start position ADC offset value,remain for calibration*/
#define Motor_Stop_Position (TRUE)         /* Motor Stop position ADC value*/
#define Motor_Stop_Position_Offset (TRUE)  /* Motor Stop position ADC offset value,remain for calibration*/
#define Potentionmeter_Total_Angle 330     /* Potentionmeter_Total_Angle 330*/
#define Potentionmeter_Pull_Up_Res 5600    /* Potentionmeter_Total_Res 10K*/
#define Potentionmeter_Total_Res 10000     /* Potentionmeter_Total_Res 10K*/
// #define Total_Res                       (Potentionmeter_Pull_Up_Res+Potentionmeter_Total_Res)              	/* Potentionmeter_Total_Res 10K*/
#define Total_Res (15600) /* Potentionmeter_Total_Res 10K*/
#define Position_Tolerance (2)
#define MOTOR_STOP_LOCK_TIME (8)/* moto stop state lock count per 10ms */

#define PL_Effect_Angle 270 /* Pengling valve use 270*/
// #define PL_Effect_Res				   (PL_Effect_Angle*Potentionmeter_Total_Res/Potentionmeter_Total_Angle)              	/* Pengling valve use 270*/
#define PL_Effect_Res (270 * 10000 / 330) /* Pengling valve use 270*/
#define Middle_Position_Res (5000)        /* Pengling valve use 270*/
// #define Start_Position_Res			  		(Middle_Position_Res+PL_Effect_Res/2)              	/* Pengling valve use 270*/
// #define Start_Position_Res			  		(5000(1+270/330))              	/* Pengling valve use 270*/
#define Start_Position_Res (9091)                                  //786 0/* Pengling valve use 270 */
#define End_Position_Res (Middle_Position_Res - PL_Effect_Res / 2) // /* Pengling valve use 270*/
/* 1# Start_Position_Res_ADC 746 */
/* 1# End_Position_Res_ADC 116 */
#define Start_Position_Res_ADC (116) /* Pengling valve use 270 */  
#define End_Position_Res_ADC (753) /* Pengling valve use 270*/
#define HARD_START_TO_HARD_END_DEGREE           (235)
#define HARD_START_TO_SOFT_START_DEGREE         (5)
#define HARD_END_TO_SOFT_END_DEGREE	            (5)
#define Sample_Number                           (1)
#if (Sample_Number==1)
#define HARD_START_POSITION_ADC	                (110)
#define HARD_END_POSITION_ADC                   (758)

#elif (Sample_Number==2)
#define HARD_START_POSITION_ADC	                (114)
#define HARD_END_POSITION_ADC                   (714)
#endif

#define SOFT_START_TO_SOFT_END_DEGREE    (HARD_START_TO_HARD_END_DEGREE-HARD_START_TO_SOFT_START_DEGREE-HARD_END_TO_SOFT_END_DEGREE)
#define MOTOR_STOP 3 /* MOTOR_STOP*/
#define MOTOR_RUN 1  /* MOTOR_RUN */
#define CW   1
#define CCW  2
#endif               /* __PARAMETER_H */

/************************ (C) COPYRIGHT LINKO SEMICONDUCTOR **********************/
/* -----------------------------------END OF FILE------------------------------- */
