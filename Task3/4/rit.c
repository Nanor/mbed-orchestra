#include "lpc17xx_gpio.h"
#include "lpc17xx_rit.h"
#include "lpc17xx_libcfg_default.h"

#include "rit.h"

void RIT_init(int interval)
{
	RIT_Init(LPC_RIT);	
	RIT_TimerConfig(LPC_RIT, interval);
	RIT_Cmd(LPC_RIT, ENABLE);

    NVIC_EnableIRQ(RIT_IRQn);
}


