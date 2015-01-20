#include "dac.h"
#include "tim.h"
#include <math.h>

#include "waveform.c"

#define ONE_SEC 44100

float amplitude;
int frequency;

int wavetimer = 0;
int wavelength = (sizeof(waveform)/sizeof(waveform[0]));
int amptimer = 0;

void synth_init()
{
	DAC_init();

	TIM_init();
	
	amplitude = 0;
}

void synth_note_on(int freq, float amp)
{
	frequency = freq;
	TIM_update_match(freq * wavelength);
	amplitude = amp;
}

void synth_note_off(float fade)
{
	
}

float lerp(float a, float b, float t)
{
	return (float)((1-t)*a + t*b);
}

void synth_tick()
{	
	int value = (int)(waveform[wavetimer] * amplitude * 512 + 511);
	DAC_send(value);

	if (amptimer == 0)
	{
		amplitude *= 0.95;
	}
	amptimer = (amptimer + 1) % frequency;
	wavetimer = (wavetimer + 1) % wavelength;
}

int note_to_freq(int note)
{
	if ((note >= 0) && (note <= 119))
		return 440 * pow(2, (note - 69) / 12.0);
	else
		return -1;
}
