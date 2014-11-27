#include "lpc17xx_pinsel.h"
#include "lpc17xx_dac.h"

#include "dac.h"

void DAC_init()
{
	PINSEL_CFG_Type PinCfg;
 
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Funcnum = 2;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 26;
	PINSEL_ConfigPin(&PinCfg);
	
	DAC_Init(LPC_DAC);
}

void DAC_send(uint16_t value)
{
	DAC_UpdateValue(LPC_DAC, value);
}
