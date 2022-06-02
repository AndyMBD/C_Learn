#include "scheduler.h"
#include "mavlink.h"
#include "port.h"
#include "Led_Blink.h"

volatile bool b1msTick;
/** This is the Scheduler loop */
void scheduler(void)
{
	/* 1m tick counter */
	static uint8 u81msCounter = 0;

	/* every 1ms */
	if(true == b1msTick)
	{
      // Every 1ms interrupt set b1msTick,
		b1msTick = false;

		u81msCounter++;


		switch(u81msCounter)
		{
		case 1:
			// Add Task here
//                  PORT_ChangePin(0x02,PORT_ACTION_TOGGLE);
                  WDT1_Service();
                  Led_Blink_step();
                  PORT_ChangePin(0x01,Led_Blink_Y.Out1);
                  PORT_ChangePin(0x03,PORT_ACTION_SET);
                  
			break;
		case 2:
                  PORT_ChangePin(0x03,PORT_ACTION_CLEAR);
			// Add Task here
			break;
		case 3:
//                  PORT_ChangePin(0x02,PORT_ACTION_CLEAR);
			// Add Task here
			break;
		case 4:
//                  PORT_ChangePin(0x02,PORT_ACTION_CLEAR);
			// Add Task here
			break;
		case 5:
//                  PORT_ChangePin(0x02,PORT_ACTION_CLEAR);
			// Add Task here
			break;
		default:
			u81msCounter = 0;
         // add task function here
			break;
		}

	}

}
/* Callback funtion for systick 1ms overflow */
void Task_1ms(void)
{
  b1msTick = true;
//  PORT_ChangePin(LED1, PORT_ACTION_TOGGLE);
}