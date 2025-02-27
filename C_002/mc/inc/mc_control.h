/*******************************************************************************
 * ��Ȩ���� (C)2019, LINKO SEMICONDUCTOR Co.ltd
 *
 * �ļ����ƣ� MC_Stepping.h
 * �ļ���ʶ��
 * ����ժҪ�� �������������??
 * ����˵���� ��
 * ��ǰ�汾�� V1.0
 * ��    �ߣ� HuangMG
 * ������ڣ�?? 2022��11��21��
 *
 *******************************************************************************/
 
/*------------------------------prevent recursive inclusion -------------------*/ 
#ifndef __MC_Stepping_H
#define __MC_Stepping_H

// #include "hardware_config.h"
// #include "state_machine.h"
#include "mc_Parameter.h"

#define ABS(X)                (( (X) >= 0 ) ? (X) : -(X) )	
#define INT32TOF16(x)         ((int16_t) (x))
#define F16TOINT32(x)         ((int32_t) (x))

#define FRAC16(x)             ((int16_t) ((x) < (SFRACT_MAX) ? ((x) >= SFRACT_MIN ? (x)*0x8000 : 0x8000) : 0x7fff))
//saturation operation between up_limitation low_limitation
#define sat(x,low_lim,up_lim) ((x) > (up_lim) ) ? (up_lim) : ( ((x) < (low_lim)) ? (low_lim) : (x) )
//typedef struct 
//{
//  int16_t hCos;
//  int16_t hSin;
//} SinCos_Components_t;

typedef struct 
{
   int16_t hKp_Gain;
   int16_t hKp_Divisor;
   int16_t hKi_Gain;
   int16_t hKi_Divisor;
   int16_t hUpper_Limit_Output;
   int16_t hLower_Limit_Output;
   int32_t wIntegral;

   int32_t wLower_Limit_Integral;   /* Lower Limit for Integral term limitation */
   int32_t wUpper_Limit_Integral;   /* Lower Limit for Integral term limitation */
}Dump_PIparams_t;

#if 0 
typedef struct
{
    /* data */
    uint8_t   Req_Enable;
    uint8_t   Req_Position_Req;
}Req_t;
#endif

typedef struct
{
    uint8_t    Req_Enable;
    uint8_t    Req_Position_LIN;
    uint8_t    Req_Direction;      /* CW CCW */
    uint8_t    Req_Direction_Last;      /* CW CCW */
    uint16_t   Req_Position;      /* Req_Position */
    uint16_t   Req_Position_Last;      /* Req_Position */
    bool   Req_Position_Valid;   /* Req_Position_Valid*/
    uint16_t   Req_Position_Filt;
    int16_t   Req_Speed;
    int16_t   Req_Speed_Filt;
    int16_t   Req_Current;
    int16_t   Req_Current_Filt;
    int16_t   Req_DutyCycle;

}Req_t;

typedef struct
{
    uint16_t    Bat_Voltage;
    uint16_t    MCU_Temperature;
}Sys_t;
typedef  struct
{
    /* data */
    uint16_t   Act_Position;  /* 10 bit adc */
    uint16_t   Act_Position_Filt;  /* 10 bit adc */
    uint8_t    Act_Position_Percentage;  /* 10 bit adc */
    int16_t   Position_Error;
    uint8_t    Position_Error_Tolerance;
    int16_t   Position_PI_Output;
    int16_t   Act_Speed;     /* 10 bit adc */
    int16_t   Act_Speed_Filt;     /* 10 bit adc */
    int16_t   Speed_Error;
    int16_t   Speed_PI_Output;
    uint16_t   Act_Current;   /* 10 bit adc */
    int16_t   Act_Current_Filt;   /* 10 bit adc */
    int16_t   Current_Error;
    int16_t   Current_PI_Output;
    uint16_t   Act_Position_100ms;
    uint16_t   Act_Position_100ms_Last;
    int16_t   Act_Position_100ms_Delta;
}Status_t;
#if 1 
typedef  struct
{
    /* data */
    uint8_t  Motor_State;
    bool Arrived_Position;
	// uint8_t  Direction_Req;
}State_t;
#endif
typedef  struct
{
    /* data */
    uint8_t   Over_Voltage_Flag;  /* Over_Voltage_Flag */
    uint8_t   Under_Voltage_Flag;  /* Under_Voltage_Flag */
    uint8_t   Over_Temperature_Flag;  /* Over_Temperature_Flag */
    uint8_t   Left_Short_GND_Flag;
    uint8_t   Left_Short_BAT_Flag;
    uint8_t   Right_Short_GND_Flag;
    uint8_t   Right_Short_BAT_Flag;
    uint8_t   Over_Current_Flag;
    uint8_t   Under_Current_Flag;
}Diag_t;
typedef struct
{
    uint8_t    Debug_Enable;
    uint8_t    Debug_Direction;
}Debug_t;
typedef struct
{
    // Req_t    Req;
    Req_t Req;
    Status_t Status;
    State_t State;
    Sys_t Sys;
    Diag_t Diag;
    Debug_t Debug;
}MC_t;


typedef struct 
{
    int32_t wUpperLimitOutput;       /* Lower Limit for Output limitation */
    int32_t wLowerLimitOutput;       /* Lower Limit for Output limitation */
    uint16_t KP;                      /* KP */
    uint16_t KI;                      /* KI */
	uint16_t KD;                      /* KD */
    int32_t wIntegral;               /* Integra */
    int32_t wInError;                /* Input error */
    int32_t wLastError;              /* Last Error*/
    int32_t wErrorC;
}stru_PIRegulator_t;



typedef struct 
{
    int32_t wUpperLimitOutput;       /*�ٶȻ�������ֵ*/
    int32_t wLowerLimitOutput;       /*�ٶȻ������С�?*/
    uint16_t KP;                      /* ����ϵ�� */
    uint16_t KI;                      /* ����ϵ�� */
    int32_t wInError;                /* �������?? */
    int64_t wIntegral;               /* ������ */
    int64_t lACC;                    /* �м�������*/
}stru_SpeedPIRegulator_t;

typedef struct 
{
    int32_t wUpperLimitOutput;       /*�ٶȻ�������ֵ*/
    int32_t wLowerLimitOutput;       /*�ٶȻ������С�?*/
    uint16_t KP;                      /* ����ϵ�� */
    uint16_t KI;                      /* ����ϵ�� */
    int32_t wInError;                /* �������?? */
    int64_t wIntegral;               /* ������ */
    int64_t lACC;                    /* �м�������*/
}stru_PositionPIRegulator_t;

typedef struct
{
    int32_t yk_1;
    uint16_t coef;
} stru_RC_t;
// extern stru_RC_t stru_Curr;
/* ss: start stop
number: low speed number, after low speed number, switch to NSP
 */

#define Number_one                      (32767*32767)
#define Number_Q12_One                  (4000*4000)



// extern stru_RC_t stru_RARC;
extern stru_RC_t stru_RBRC;
extern stru_RC_t stru_IQRC;
extern stru_RC_t stru_IDRC;

extern uint16_t Soft_Start_ADC;
extern uint16_t Soft_End_ADC;

extern MC_t  MC;
extern stru_RC_t 			stru_RC_Act_Position;
extern stru_PIRegulator_t 	stru_PIRegulator_Current;
extern stru_PIRegulator_t 	stru_PIRegulator_Speed;
extern stru_PIRegulator_t 	stru_PIRegulator_Position;
extern int16_t PIRegulator_Increment(stru_PIRegulator_t *Reg);
extern void MC_StateInit();
extern void Motor_Soft_Stop(void);
extern void Speed_loop_1ms(void);
extern void Position_loop_100ms(void);
extern void Current_loop_50us(void);
extern int16_t lowPass_filter(stru_RC_t *rc, int16_t signal);
extern void io_test_toggle(void);

#endif


