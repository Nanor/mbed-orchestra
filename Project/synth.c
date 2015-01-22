#include "dac.h"
#include "tim.h"
#include <math.h>

#include "waveform.c"

#define ONE_SEC 44100
#define WAVE_SKIP 3

float amplitude;
int frequency;

int noteDown = 0;

int wavetimer = 0;
int wavelength = (sizeof(waveform)/sizeof(waveform[0]))/WAVE_SKIP;
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
	noteDown = 1;
}

void synth_note_off(float fade)
{
	noteDown = 0;
}

float lerp(float a, float b, float t)
{
	return (float)((1-t)*a + t*b);
}

void synth_tick()
{	
	int value = (int)(waveform[wavetimer*WAVE_SKIP] * amplitude * 512 + 511);
	DAC_send(value);

	if (amptimer == 0)
	{
		if (noteDown)
		{
			amplitude *= 0.995;
		}
		else
		{
			amplitude *= 0.95;
		}
		//amplitude *= 0.95;
		/*
		if (targetAmp == 0)
		{
			amplitude = lerp(amplitude, targetAmp, 0.05);
		}
		else
		{
			amplitude = lerp(amplitude, targetAmp, 0.5);
		}*/
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