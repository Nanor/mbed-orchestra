#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "tim.h"
#include "synth.h"

void TIM_init(int freq)
{
	TIM_TIMERCFG_Type config;
	config.PrescaleOption = TIM_PRESCALE_USVAL;
	config.PrescaleValue = 1;

	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &config);

	TIM_MATCHCFG_Type match;
	match.MatchChannel = 0;
	match.IntOnMatch = ENABLE;
	match.StopOnMatch = DISABLE;
	match.ResetOnMatch = ENABLE;
	match.ExtMatchOutputType = TIM_EXTMATCH_TOGGLE;
	
	TIM_ConfigMatch(LPC_TIM0, &match);
	
	TIM_UpdateMatchValue(LPC_TIM0, 0, 1000000.0/freq);

	/* preemption = 1, sub-priority = 1 */
	NVIC_SetPriority(TIMER0_IRQn, ((0x01<<3)|0x01));
	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER0_IRQn);
	// To start timer 0
	TIM_Cmd(LPC_TIM0,ENABLE);
}

void TIMER0_IRQHandler()
{
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)== SET)
	{
		synth_tick();
	}
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);	
}


