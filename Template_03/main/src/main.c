#include <windows.h>
#include "stdio.h"
#include "stdint.h"
#include "mc_Parameter.h"
#include "mc_control.h"
// #include "cJSON_Utils.h"
// #include "my_lib.h"
#include "my_dll.h"
#include "my_lib.h"
// #pragma comment(lib,"my_lib.lib")
// extern uint32_t multiply(uint16_t a,uint16_t b);
// __declspec(dllimport) uint32_t add(uint16_t a,uint16_t b);
// __declspec(dllimport) uint32_t multiply(uint16_t a,uint16_t b);

uint8_t Set_Position_Percentage_Out(uint16_t Act_Position);
uint16_t get_Req_Position(uint8_t Motor_TargetPosition_Percentage);
int main()
{
	
	Soft_Start_ADC	=  (uint16_t)(HARD_START_TO_SOFT_START_DEGREE*(HARD_END_POSITION_ADC-HARD_START_POSITION_ADC)/HARD_START_TO_HARD_END_DEGREE+HARD_START_POSITION_ADC);
	Soft_End_ADC	=  (uint16_t)((HARD_START_TO_HARD_END_DEGREE-HARD_END_TO_SOFT_END_DEGREE)*(HARD_END_POSITION_ADC-HARD_START_POSITION_ADC)/HARD_START_TO_HARD_END_DEGREE+HARD_START_POSITION_ADC);
    printf("Soft_Start_ADC=%d,  Soft_End_ADC=%d\n",Soft_Start_ADC,Soft_End_ADC);/* code */
    for (uint16_t i = 0; i < 255; i++)
    {
        printf("LIN_Req_Percentage= %d get_Req_Position=%d\n",i,get_Req_Position(i));/* code */
    }
    // printf("add=%d\n",add
    printf("/*******************************************************/\n");/* code */
    for (uint16_t i = 100; i < 750; i++)
    {
        printf("Current_Position_ADC =%d Position_Percentage_Out=%d\n",i,Set_Position_Percentage_Out(i));/* code */
    }


 #if 0 
    uint16_t a = 30;
    uint16_t b = 34;
    uint16_t c = 48;
    for (uint16_t i = 20; i < 50; i++)
    {
        c=i;
        // if (a<=c<=b)
        if ((c>=a)&&(c<=b))
        {
            printf("a=%d,  b=%d,  c=%d,",a,b,c);/* code */
            printf("correct\n");/* code */
        }
        else
        {
            printf("a=%d,  b=%d,  c=%d,",a,b,c);/* code */
            printf("error\n");
        }
        
        /* code */
    }
 #endif
return 0;
}
uint8_t Set_Position_Percentage_Out(uint16_t Act_Position)
{
	int16_t Act_Position_Percentage_Temp;
	uint8_t Act_Position_Percentage;

	Act_Position_Percentage_Temp = (Act_Position-Soft_Start_ADC ) * 255 / (Soft_End_ADC-Soft_Start_ADC);
	if (Act_Position_Percentage_Temp >= 255)
	{
		Act_Position_Percentage = 255;
	}
	else if (Act_Position_Percentage_Temp <= 0)
	{
		Act_Position_Percentage = 0;
	}
	else
	{
		Act_Position_Percentage = (uint8_t) (Act_Position_Percentage_Temp);
	}
return Act_Position_Percentage;
}

uint16_t get_Req_Position(uint8_t Motor_TargetPosition_Percentage)
{
	uint16_t temp_Req_Position_ADC;
#if 0 
	End_Position_Res_ADC	=82;
	// uint16_t temp_ratio;
	u64 temp_1,temp_2,temp_3,temp_4,temp_ratio,temp_ratio_1;
	temp_ratio=PL_Effect_Angle*Potentionmeter_Total_Res*128;
	temp_ratio_1=(temp_ratio/(Potentionmeter_Total_Angle*100))/128;
	temp_1=(Start_Position_Res-Motor_TargetPosition_Percentage*temp_ratio_1)*1422;
	temp_2=temp_1*128;
	/* 10 bit */
	temp_3	=	(temp_2)/(Total_Res);
	temp_4= (temp_3/128);
#endif
#if 0 
	temp_Req_Position_ADC = (Motor_TargetPosition_Percentage * (End_Position_Res_ADC-Start_Position_Res_ADC)) / 255+Start_Position_Res_ADC;
#endif

	temp_Req_Position_ADC = (Motor_TargetPosition_Percentage * (Soft_End_ADC-Soft_Start_ADC)) / 255+Soft_Start_ADC;
	return (temp_Req_Position_ADC);
}