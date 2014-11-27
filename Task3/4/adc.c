# include "adc.h"

void ADC_init()
{
	PINSEL_CFG_Type PinCfg;
 
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Funcnum = 1;
	PinCfg.Portnum = 0;
	PinCfg.Pinnum = 24;
	PINSEL_ConfigPin(&PinCfg);
	
	ADC_Init(LPC_ADC, 20000);
	ADC_ChannelCmd(LPC_ADC, 1, ENABLE);
	
	ADC_ChannelGetData(LPC_ADC, 1);
}

uint16_t ADC_read()
{
	ADC_StartCmd(LPC_ADC, ADC_START_NOW);
	while(!ADC_ChannelGetStatus(LPC_ADC, 1, 1));
	
	return(ADC_ChannelGetData(LPC_ADC, 1));
}



