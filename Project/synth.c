#include "dac.h"
#include "tim.h"
#include <math.h>

#include "waveform.c"

#define WAVELENGTH (sizeof(waveform)/sizeof(waveform[0]))

float amplitude;
int frequency;

int noteDown = 0;

int timer = 0;
//int wavetimer = 0;
int voice = 0;
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
	//TIM_update_match(freq * wavelength);
	amplitude = amp;
	noteDown = 1;
}

void synth_note_off()
{
	noteDown = 0;
}

void synth_tick()
{	
	timer = (timer + 1) % ((INT_ONE_SEC / UPDATE) / frequency);
	
	int value = (int)(waveform[WAVELENGTH * timer / ((INT_ONE_SEC / UPDATE) / frequency)] * amplitude * 512 + 511);
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
	}
	amptimer = (amptimer + 1) % 100;
	//wavetimer = (wavetimer + 1) % wavelength;
}

int note_to_freq(int note)
{ // Convert MIDI note value to audio frequency
	if ((note >= 0) && (note <= 119))
		return 440 * pow(2, (note - 69) / 12.0);
	else
		return -1;
}

float lerp(float a, float b, float t)
{ // Linearly interpolate between 2 values
	return (float)((1-t)*a + t*b);
}
