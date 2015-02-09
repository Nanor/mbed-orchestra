#include "dac.h"
#include "tim.h"
#include <math.h>
#include "synth.h"

#include "waveform.c"

#define TRACKS 3

float amplitude[TRACKS];
int frequency[TRACKS];
int targetFreq[TRACKS];

int noteDown[TRACKS];
int wavelength = (sizeof(waveform)/sizeof(waveform[0]));

int timer = 0;
int amptimer = 0;

int track = 0;

void synth_init()
{
	DAC_init();
	TIM_init();
}

void synth_note_on(int freq, float amp)
{
	//if (!noteDown) frequency = freq;
	targetFreq[track] = freq;
	amplitude[track] = amp;
	noteDown[track] = 1;
	
	track = (track + 1) % TRACKS;
}

void synth_note_off(int freq)
{
	int i;
	for (i = 0; i < TRACKS; i++) {
		if (targetFreq[i] == freq || freq == -1)
			noteDown[i] = 0;
	}
}

void synth_tick()
{	
	int i;
	float value = 0;
	for (i = 0; i < TRACKS; i++) {
		int maxValue = ((INT_ONE_SEC / UPDATE) / frequency[i]);
	
		value += waveform[(int)lerp(0, wavelength, (float)(timer % maxValue) / maxValue)] * amplitude[i];

		if (amptimer == 0)
		{
			frequency[i] = lerp(frequency[i], targetFreq[i], 0.5);
	
			if (noteDown[i])
			{
				amplitude[i] *= 0.995;
			}
			else
			{
				amplitude[i] *= 0.95;
			}
		}
	}
	amptimer = (amptimer + 1) % 100;
	timer = (timer + 1) % (INT_ONE_SEC / UPDATE);
	DAC_send((int)((value / TRACKS) * 512 + 511));
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
