# include "adc.h"

void ADC_init()
{
	PINSEL_CFG_Type PinCfg;
 
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Funcnum = 3;
	PinCfg.Portnum = 1;
	PinCfg.Pinnum = 30;
	PINSEL_ConfigPin(&PinCfg);
	
	ADC_Init(LPC_ADC, 20000);
	ADC_ChannelCmd(LPC_ADC, 4, ENABLE);
	
	ADC_ChannelGetData(LPC_ADC, 4);
}

uint16_t ADC_read()
{
	ADC_StartCmd(LPC_ADC, ADC_START_NOW);
	while(!ADC_ChannelGetStatus(LPC_ADC, 4, 1));
	
	return(ADC_ChannelGetData(LPC_ADC, 4));
}



