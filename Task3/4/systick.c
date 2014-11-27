#include "systick.h"
#include "lpc17xx_systick.h"
#include "debug.h"

void SYSTICK_init(int interval)
{
	SYSTICK_ClearCounterFlag();
	SYSTICK_InternalInit(interval);
	SYSTICK_Cmd(ENABLE);
	SYSTICK_IntCmd(ENABLE);
}
