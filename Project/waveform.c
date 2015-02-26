#include "waveform.h"
#include "math.h"

#define WAVELENGTH 500

int voice;
int waveform[WAVELENGTH];
int safe = 0;

void makeWave() {
	safe = 0;
	int values[VOICES][5] =	{
														{10, 0, 0, 0, 0},
														{ 7, 3, 0, 0, 0},
														{ 7, 0, 3, 0, 0},
														{ 0, 0, 0, 0, 0},
														{ 8, 0, 0, 1, 1},
													};

	int x;
	int harmonic;
	if (voice != 3)
	{
		for (x = 0; x < WAVELENGTH; x++)
		{
			float val = 0;
			for (harmonic = 0; harmonic < 5; harmonic++)
			{
				val += values[voice][harmonic] * sin(M_PI * 2 * (harmonic+1) * x / WAVELENGTH);
			}
			waveform[x] = (int)((val) * 12);
		}
	}
	else
	{
		for (x = 0; x < WAVELENGTH; x++)
		{
			waveform[x] = 64 * (x < WAVELENGTH/2 ? -1 : 1);
		}
	}
	safe = 1;
}

int getValue(float point) {
	if (safe)
		return (waveform[(int)(WAVELENGTH * point)]);
	else
		return 0;
}

void incVoice() {
	if (voice < VOICES+1)
	{
		voice++;
	
		makeWave();
	}
	
}

void decVoice() {
	if (voice > 0)
	{
		voice--;
		makeWave();
	}
}

int getVoice() {
	return voice;
}

