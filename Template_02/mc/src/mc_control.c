
#include "mc_control.h"
#include "mc_Parameter.h"

#define RAMP_HAS_OPEN_LOOP 0
#define SPEED_IS_CONST_ENABLE 0
#define LOWPASS_FILTER_ENABLE 1
#define PI_CONTROL_ENABLE 1

MC_t MC;
stru_RC_t			stru_RC_Req_Position={
					.yk_1					=	0,
					.coef					=	REQ_POSITION_LPF_COEFF,
};
stru_RC_t			stru_RC_Act_Position={
					.yk_1					=	0,
					.coef					=	ACT_POSITION_LPF_COEFF,
};
stru_RC_t			stru_RC_Req_Speed={
					.yk_1					=	0,
					.coef					=	REQ_SPEED_LPF_COEFF,
};
stru_RC_t			stru_RC_Act_Speed={
					.yk_1					=	0,
					.coef					=	ACT_SPEED_LPF_COEFF,
};
stru_RC_t			stru_RC_Req_Curr={
					.yk_1					=	0,
					.coef					=	REQ_CURRENT_LPF_COEFF,
};
stru_RC_t			stru_RC_Act_Curr={
					.yk_1					=	0,
					.coef					=	ACT_CURRENT_LPF_COEFF,
};
stru_PIRegulator_t	stru_PIRegulator_Position={
					.wUpperLimitOutput		=	SPEED_HIGH_LIMIT,       /* Lower Limit for Output limitation */
					.wLowerLimitOutput		=	SPEED_LOW_LIMIT,       /* Lower Limit for Output limitation */
					.KP						=	POSITION_KP,            /* KP */
					.KI						=	POSITION_KI,            /* KI */
					.KD						=	0,                      /* KD */
					.wIntegral				=	0,               /* Integra */
					.wInError				=	0,                /* Input error */
					.wLastError				=	0,              /* Last Error*/
					.wErrorC				=	0,
};
stru_PIRegulator_t	stru_PIRegulator_Speed={
					.wUpperLimitOutput		=	CURRENT_HIGH_LIMIT,       /* Lower Limit for Output limitation */
					.wLowerLimitOutput		=	CURRENT_LOW_LIMIT,       /* Lower Limit for Output limitation */
					.KP						=	SPEED_KP,                      /* KP */
					.KI						=	SPEED_KI,                      /* KI */
					.KD						=	0,                      /* KD */
					.wIntegral				=	0,               /* Integra */
					.wInError				=	0,                /* Input error */
					.wLastError				=	0,              /* Last Error*/
					.wErrorC				=	0,
};
stru_PIRegulator_t	stru_PIRegulator_Current={
					.wUpperLimitOutput		=	PWM_DUTYCYCLE_HIGH_LIMIT,       /* Lower Limit for Output limitation */
					.wLowerLimitOutput		=	PWM_DUTYCYCLE_LOW_LIMIT,       /* Lower Limit for Output limitation */
					.KP						=	POSITION_KP,            /* KP */
					.KI						=	POSITION_KI,            /* KI */
					.KD						=	0,                      /* KD */
					.wIntegral				=	0,               /* Integra */
					.wInError				=	0,                /* Input error */
					.wLastError				=	0,              /* Last Error*/
					.wErrorC				=	0,
};
uint16_t Soft_Start_ADC;
uint16_t Soft_End_ADC;

void MC_StateInit(void);
void ramp_start(void);
void ramp_stop(void);
void normal_mode(void);
int16_t PIRegulator_Increment(stru_PIRegulator_t *Reg);
int16_t lowPass_filter(stru_RC_t *rc, int16_t signal);
void Motor_CCW(int16_t duty);
void Motor_CW(int16_t duty);
void Motor_BRAKE(void);
void Motor_Soft_Stop(void);
void io_test_toggle(void);

void MC_StateInit()
{
	MC.Status.Position_Error_Tolerance		=	Position_Tolerance;
}

/*******************************************************************************
 ?????????    void Curr_Slope1ms(void)
 ??????????    ????��??

 -----------------------------------------------------------------------------
 2022/11/21      V1.0         HuangMG            ????
 *******************************************************************************/
void ramp_start(void)
{}
void ramp_stop(void)
{}
void normal_mode(void)
{}


void Position_loop_100ms(void)
{
	MC.Status.Act_Position_100ms		=	MC.Status.Act_Position_Filt;
	MC.Status.Act_Position_100ms_Delta	=	MC.Status.Act_Position_100ms-MC.Status.Act_Position_100ms_Last;
	MC.Status.Act_Speed					=	MC.Status.Act_Position_100ms_Delta	;
	// MC.Status.Act_Speed_Filt			=	lowPass_filter(&stru_RC_Act_Speed,	MC.Status.Act_Speed);
	MC.Status.Act_Position_100ms_Last	=	MC.Status.Act_Position_100ms;
	if(MC.State.Motor_State		==	MOTOR_RUN)
	{
		// MC.Req.Req_Position_Filt			=	lowPass_filter(&stru_RC_Req_Position,		(int16_t)MC.Req.Req_Position);
		// MC.Status.Act_Position_Filt			=	lowPass_filter(&stru_RC_Act_Position,		(int16_t)MC.Status.Act_Position);
		// MC.Status.Position_Error			=	MC.Req.Req_Position_Filt	-	MC.Status.Act_Position_Filt;
		MC.Status.Position_Error			=	MC.Req.Req_Position	-	MC.Status.Act_Position_Filt;
		stru_PIRegulator_Position.wInError	=	MC.Status.Position_Error;
		// stru_PIRegulator_Current.wInError	=	MC.Status.Speed_PI_Output	-	MC.Status.Act_Current;
		MC.Req.Req_Speed					=	PIRegulator_Increment(&stru_PIRegulator_Position);
	}
	else
	{
		// MC.Req.Req_Speed				=	0;
	}
}

void Speed_loop_1ms(void)
{
#if 1

	MC.Status.Position_Error = MC.Req.Req_Position - MC.Status.Act_Position;
	MC.Status.Speed_Error			=	MC.Req.Req_Speed-MC.Status.Act_Speed;
	stru_PIRegulator_Speed.wInError	=	MC.Status.Speed_Error;
	MC.Req.Req_Current				=	PIRegulator_Increment(&stru_PIRegulator_Speed);
	if(MC.Req.Req_Enable)
	{
		if (MC.State.Motor_State		!=	MOTOR_STOP)
		{
			if(MC.Req.Req_Direction==CW)
			{
				// Motor_CCW(MC.Status.Current_PI_Output);/* CCW */
				// if ((MC.Status.Position_Error>MC.Status.Position_Error_Tolerance)&&(MC.State.Arrived_Position == false))
				if (MC.State.Arrived_Position == false)
				{
					Motor_CW(MC.Req.Req_Current);/* CW */
				}
				else
				{
					Motor_Soft_Stop();
					MC_StateInit();
				}
				
			}
			else if(MC.Req.Req_Direction==CCW)
			{
				// if ((MC.Status.Position_Error<-MC.Status.Position_Error_Tolerance)&&(MC.State.Arrived_Position == false))
				if (MC.State.Arrived_Position == false)
				{
					Motor_CCW(MC.Req.Req_Current);
				}
				else
				{
					Motor_Soft_Stop();
					MC_StateInit();
				}
			}
		}
		else
		{
				Motor_Soft_Stop();
				MC_StateInit();
				// Motor_BRAKE();
		}
	}
	else
	{
		Motor_Soft_Stop();
		MC_StateInit();
	}

#endif

}

void Current_loop_50us(void)
{
	int16_t	PWM_Duty_Temp;
	// int16_t current_Req_Temp;
	// Current_Req_Temp= lowPass_filter(&stru_Curr,MC.Req.Req_Position_Req);

	MC.Req.Req_Current_Filt				=	lowPass_filter(&stru_RC_Req_Curr,		MC.Req.Req_Current);
	MC.Status.Act_Current_Filt			=	lowPass_filter(&stru_RC_Act_Curr,		MC.Status.Act_Current);
	MC.Status.Current_Error				=	MC.Req.Req_Current_Filt	-	MC.Status.Act_Current_Filt;
	stru_PIRegulator_Current.wInError	=	MC.Status.Current_Error;
	// MC.Req.Req_DutyCycle				=	PIRegulator_Increment(&stru_PIRegulator_Current);
	if (MC.Req.Req_Current_Filt<0)
	{
		MC.Req.Req_Current_Filt=-MC.Req.Req_Current_Filt;
	}
	// MC.Status.Current_PI_Output = sat(MC.Status.Current_PI_Output,PWM_DUTY_LOW_LIMIT,PWM_DUTY_HIGH_LIMIT);
}

int16_t PIRegulator_Increment(stru_PIRegulator_t *Reg)
{
	int32_t ACC;
	int16_t AX;
	ACC = (int32_t)(Reg->wInError - Reg->wLastError) * Reg->KP; 
	ACC = (ACC << 4) + (int32_t)(Reg->wInError) * Reg->KI;		 
	Reg->wIntegral = ACC + Reg->wIntegral;

	if (Reg->wIntegral > Reg->wUpperLimitOutput) 
	{
		Reg->wIntegral = Reg->wUpperLimitOutput;
	}
	else if (Reg->wIntegral < Reg->wLowerLimitOutput) 
	{
		Reg->wIntegral = Reg->wLowerLimitOutput;
	}

	AX = Reg->wIntegral >> 16;

	Reg->wLastError = Reg->wInError; 

	return (AX);
}
int16_t lowPass_filter(stru_RC_t *rc, int16_t signal)
{
	int32_t wkg;
	wkg = (signal - (int16_t)(rc->yk_1 >> 16)) * (rc->coef);
	rc->yk_1 += wkg;
	return (rc->yk_1 >> 16);
}
void Motor_CCW(int16_t duty)
{

}

void Motor_CW(int16_t duty)
{

}

void Motor_BRAKE(void)
{

}
void Motor_Soft_Stop(void)
{

}
/* single test pin for hardware test */
void io_test_toggle(void)
{
	
}