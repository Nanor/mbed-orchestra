#include "lpc17xx_timer.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_gpio.h"
#include "tim.h"
#include "synth.h"
#include "john.h"

int waveSynth = 0;

void TIM_init()
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
	
	TIM_UpdateMatchValue(LPC_TIM0, 0, UPDATE);

	/* Enable interrupt for timer 0 */
	NVIC_EnableIRQ(TIMER0_IRQn);
	
	TIM_Cmd(LPC_TIM0,ENABLE);
}

void TIM_update_match(int freq)
{
	TIM_UpdateMatchValue(LPC_TIM0, 0, (int)(UPDATE));
	TIM_ResetCounter(LPC_TIM0);
	TIM_Cmd(LPC_TIM0,ENABLE);
}

int getWaveSynthStatus()
{
	return(waveSynth);
}


void switchSynth(int synth)
{
	waveSynth = synth;
	if(!waveSynth)
	{
		// Clean up samples
		WAVE_disable();
	}
	else
	{
		// Clean up synth.
	}
}

void TIMER0_IRQHandler()
{
	if (TIM_GetIntStatus(LPC_TIM0, TIM_MR0_INT)== SET)
	{
		if(waveSynth)
		{
			WAVE_synthtick();
		}
		else
		{
			synth_tick();	
		}
	}
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);	
}


