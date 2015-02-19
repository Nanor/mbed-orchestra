#include "waveform.h"
#include "math.h"
#include "lpc17xx_pinsel.h"

#define WAVELENGTH 500

int waveform[VOICES][WAVELENGTH];

void makeWaves() {

	float values[VOICES][5] =	{
															{  1,  0,  0,  0,  0},
															{.7f,.3f,  0,  0,  0},
															{.7f,  0,.3f,  0,  0},
															{  0,  0,  0,  0,  0},
															{.8f,  0,  0,.1f,.1f},
														};

	int x;
	int voice;
	int harmonic;
	for (x = 0; x < WAVELENGTH; x++) {
		for (voice = 0; voice < VOICES; voice++) {
			float val = 0;
			for (harmonic = 0; harmonic < 5; harmonic++) {
				val += values[voice][harmonic] * sin(M_PI * 2 * (harmonic+1) * x / WAVELENGTH);
			}
			waveform[voice][x] = (int)(val * 127);
		}
		waveform[3][x] = 64 * (x < WAVELENGTH/2 ? -1 : 1);
	}
}

float getValue(float point, int voice) {
	return (float)(waveform[voice][(int)(WAVELENGTH * point)]) / 127;
}

