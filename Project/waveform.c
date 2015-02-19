#include "waveform.h"
#include "math.h"

#define WAVELENGTH 500

float waveform[VOICES][WAVELENGTH];

void makeWaves() {
	int x;
	for (x = 0; x < WAVELENGTH; x++) {
		waveform[0][x] = sin(M_PI * 2 * x / WAVELENGTH);
		waveform[1][x] = 0.7*sin(M_PI * 2 * x / WAVELENGTH) + 0.3*sin(M_PI * 2 * 2 * x / WAVELENGTH);
		waveform[2][x] = 0.7*sin(M_PI * 2 * x / WAVELENGTH) + 0.3*sin(M_PI * 2 * 3 * x / WAVELENGTH);
		waveform[3][x] = x < WAVELENGTH/2 ? 0 : 1;
	}
}

float getValue(float point, int voice) {
	return waveform[voice][(int)(WAVELENGTH * point)];
}

