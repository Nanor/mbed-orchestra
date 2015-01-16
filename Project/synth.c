#include "dac.h"
#include "tim.h"
#include <math.h>

#define ONE_SEC 44100
#define PI 3.141592

int frequency;
int amplitude;
int length;

int timer = 0;

void synth_init()
{
	DAC_init();

	TIM_init(ONE_SEC);
	
	frequency = 1;
	amplitude = 1;
	length = 1;
}

void synth_tick()
{
	//DAC_send(timer * 5000);
	DAC_send( (int)((sin(2*PI * ((float)timer/ONE_SEC))+1) * 500.0));
	timer++;
	if (timer >= ONE_SEC)
	{
		timer = 0;
		DEBUG_write("One sec\r\n");
	}
}
