#include "systick.h"
#include "lpc17xx_systick.h"

void SYSTICK_init()
{
	SYSTICK_ClearCounterFlag();
	SYSTICK_InternalInit(100);
	SYSTICK_Cmd(ENABLE);
	SYSTICK_IntCmd(ENABLE);
}

int time = -1;

void SysTick_Handler(void)
{
	if (time > -1)
	{
		time += 1;
	}
}

void SYSTICK_wait(float time)
{
	int count = (int) (time * 10);
	time = 0;
	
	while (time < count);
	
	time = -1;
}
