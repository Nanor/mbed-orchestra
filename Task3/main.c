#include "adc.h"
#include "lcd.h"
#include "debug.h"
#include "dac.h"

#include <math.h>

void outputSinWave(float amp, float freq)
{
	float calcAmp = 512 * amp / 3.3;
	float calcFreq = 3800 / freq;
	
	int i;
	for(i=0;i<(314*2*calcFreq);i++)
	{
		DAC_send(calcAmp*(sin(i/calcFreq)+1)-1);
	}
}

void main(void)
{
	ADC_init();
	DAC_init();
	LCD_init();
	DEBUG_init();
	
	while(1)
	{
		outputSinWave(1, 6.2);
	}
			
}



