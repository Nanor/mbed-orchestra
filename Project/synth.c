#include "dac.h"
#include "tim.h"
#include <math.h>
#include "synth.h"
#include "waveform.h"
#include "lpc17xx_pinsel.h"

#define TRACKS 5

int amplitude[TRACKS];
int frequency[TRACKS];
int targetFreq[TRACKS];

int noteDown[TRACKS];
float fadeIn[TRACKS];

int timer = 0;
int amptimer = 0;

int track = 0;

int voice = 0;
int mainVolume = 10;

void changeVolume(int amount) {
	mainVolume += amount;
	if (mainVolume < 0)
		mainVolume = 0;
	if (mainVolume > MAXVOLUME)
		mainVolume = MAXVOLUME;
}

int getVolume() {
	return mainVolume;
}

void synth_init()
{
	DAC_init();
	TIM_init();
	makeWave();
}

void synth_note_on(int freq, float amp)
{
	frequency[track] = freq;
	fadeIn[track] = 0;
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

void synth_clean()
{
	int i;
	for (i = 0; i < TRACKS; i++)
	{
		amplitude[i] = 0;
	}
}

void synth_tick()
{	
	int i;
	int value = 0;
	for (i = 0; i < TRACKS; i++)
	{
		int maxValue = ((INT_ONE_SEC / UPDATE) / frequency[i]);
	
		value += getValue((float)(timer % maxValue) / maxValue) * amplitude[i] * fadeIn[i];

		if (amptimer == 0)
		{	
			fadeIn[i] = lerp(fadeIn[i], 1, 0.2f);
			amplitude[i] *= noteDown[i] ? 0.99 : 0.95;
		}
	}
	amptimer = (amptimer + 1) % 100;
	timer = (timer + 1) % (INT_ONE_SEC / UPDATE);
	DAC_send( (uint16_t) clamp((((value) * mainVolume) >> 10) + 512, 0, 1023) );
}

int clamp(int value, int min, int max)
{
	if (value < min)
		return min;
	if (value > max)
		return max;
	return value;
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
