#include "adc.h"
#include "lcd.h"
#include "debug.h"
#include "dac.h"
#include "rtc.h"
#include "systick.h"

#include <stdlib.h>
#include <math.h>

#define PI 3.141592

float amplitude = 2;
float period = 0.1;

void main(void)
{
	ADC_init();
	DAC_init();
	LCD_init();
	DEBUG_init();
	SYSTICK_init(20);
}

int c = 0;

void SysTick_Handler(void) 
{
	c++;

	int value = ADC_read();
		
	DAC_send(value/4);
	
	if(c % 50 == 0)
	{
		DEBUG_write_float("%f\r\n", value*3.3/4096);
	}
}	

/*
int i = 0;
int j = 0;
int aDir = -1;
int pDir = 1;

void SysTick_Handler(void)
{
	//amplitude += 0.0001 * aDir;
	//period += 0.00001 * pDir;
	
	if (amplitude > 3 || amplitude < 1) aDir *= -1;
	if (period > 0.2 || period < 0.01) pDir *= -1;
	
	if (j++ == period*1000-1) j = 0;
	
	DAC_send(511*(sin(2*PI*j/(period*1000.0))+1) * amplitude / 3.3);
}*/



