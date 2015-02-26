#include "debug.h"
#include "keypad.h"
#include "lcd.h"
#include "dac.h"
#include "tim.h"
#include "synth.h"
#include <string.h>


void SERIAL_wait(char* str){
	int key = KEYPAD_get_key();
	LCD_clear();
	LCD_write(str);
	while(1){
		key = KEYPAD_get_key();
		if(key == -1){
			break;
		}
	}
	
	while(1){
		key = KEYPAD_get_key();
		
		if(key == 10){
			key = -1;
			return;
		}
	}
}

void SERIAL_wait_int(int n){
	int key = KEYPAD_get_key();
	LCD_clear();
	LCD_write_int("%d", n);
	while(1){
		key = KEYPAD_get_key();
		if(key == -1){
			break;
		}
	}
	
	while(1){
		key = KEYPAD_get_key();
		
		if(key == 10){
			key = -1;
			return;
		}
	}
}

void SERIAL_readConfirmation(){
	uint8_t conf;
	
	while(1){
		conf = USB_readByte();
		if(conf != 0){
			break;
		}
	}
	
	if(conf != 'a'){
		SERIAL_wait("Confirm Error:");
		SERIAL_wait_int(conf);
	}
	
}


void SERIAL_write2Bytes(uint16_t len){
	
	uint8_t a, b;
	int i;
	
	a = len >> 8;
	b = len % pow(2, 8);
	
	uint8_t lengthArray[2] = {a,b};
	
	for(i = 0; i < 2; i++){
		if(lengthArray[i] == 0){
			lengthArray[i] = 255;
		}
	}

	for(i = 0; i < 2; i++){
		USB_writeByte(lengthArray[i]);
	}

	SERIAL_readConfirmation();
	
}


void SERIAL_write8Bytes(uint8_t data[8]){
	int i;
	
	for (i = 0; i < 8; i++){
		USB_writeByte(data[i]);
	}
	
	SERIAL_readConfirmation();
}


void SERIAL_writeDataBlock(uint8_t * data, uint16_t length){
	uint8_t * current = malloc(8);
	int i;
	
	SERIAL_write2Bytes(length);
	for(i = 0; i < length; i++){
		current[i%8] = data[i];
		if(i % 8 == 7 && i != 0){
			SERIAL_write8Bytes(current);
		}		
	}
}


uint16_t SERIAL_read2Bytes(){
	uint8_t byteArray[2];
	int i;
	uint8_t inp = 0;

	for(i = 0; i < 2; i++){
		while(inp == 0){
			inp = USB_readByte();
		}
		byteArray[i] = inp;
		inp = 0;
	}
	
	uint16_t a;
	a = (byteArray[0] == 255 ? 0 : (byteArray[0] << 8));
	uint16_t dataOut = a + byteArray[1];
	
	USB_writeByte('a');
	
	return(dataOut);
}


void SERIAL_read8Bytes(uint8_t * read8data){
	int i;
	uint8_t inp = 0;

	for (i = 0; i < 8; i++){
		while(inp == 0){
			inp = USB_readByte();
		}
		read8data[i] = inp;
		inp = 0;	
	}
	
	USB_writeByte('a');
}


void SERIAL_readDataBlock(uint8_t * data, uint16_t dataLength){
	uint8_t currentArray[8];
	uint8_t * current = &currentArray;
	int progress = 0;
	int oldprogress = 0;
	if(current == NULL){
		SERIAL_wait("null pointer");
	}
	int i;
	
	LCD_clear();
	LCD_write_int("%d", progress);
	for(i = 0; i < dataLength; i+=8){
		oldprogress = progress;
		progress = (int)(100*((float)i/dataLength));
		
		if(oldprogress != progress){
			LCD_clear();
			LCD_write_int("%d", progress);
		}
		
		SERIAL_read8Bytes(current);
		int j;
		for(j = i; j < i+8; j++){
			data[j] = current[j%8];
		}
	}
	
	data[dataLength] = '\0';
}


struct waveMetadata {
	uint8_t waveInit;
	uint16_t waveStart;
	uint16_t waveLength;
	uint16_t waveSampleRate;
	float waveInc;
	float waveReadPos;
};

uint8_t waveData[28000];
struct waveMetadata waveInfo[4];
uint16_t dataMarker = 1;

void WAVE_readWave(struct waveMetadata * waveMeta){
	USB_writeByte('z');
	waveMeta->waveInit = 1;
	waveMeta->waveStart = dataMarker;
	waveMeta->waveLength = SERIAL_read2Bytes();
	waveMeta->waveSampleRate = SERIAL_read2Bytes();
	waveMeta->waveInc = (float)(waveMeta->waveSampleRate / (float)(INT_ONE_SEC / UPDATE));
	waveMeta->waveReadPos = 0;
	
	SERIAL_readDataBlock(&waveData[dataMarker], waveMeta->waveLength);
	dataMarker += waveMeta->waveLength;
}


void WAVE_synthtick(){
	uint8_t i, wavesDown;
	uint16_t waveOut = 0;
	wavesDown = 0;
	for(i = 0; i < 4; i++){
		if(waveInfo[i].waveInit){
			if(waveInfo[i].waveReadPos != 0){
				wavesDown++;
				waveOut += waveData[(int)waveInfo[i].waveReadPos] * ((float)(getVolume())/10);
				waveInfo[i].waveReadPos += waveInfo[i].waveInc;
				if(waveInfo[i].waveReadPos >= (waveInfo[i].waveStart+waveInfo[i].waveLength)){
					waveInfo[i].waveReadPos = 0;
					//waveInfo[i].waveReadPos = waveInfo[i].waveStart;
				}
			}
		}
	}
	DAC_send((waveOut));
}

void WAVE_noteOn(int n){
	waveInfo[n].waveReadPos = waveInfo[n].waveStart;
}

uint8_t notes[120];
int i;

void WAVE_addToArray(int n){
	notes[n-1] = 1;
}

void WAVE_disable(){
	int i;
	for(i = 0; i < 4; i++){
		waveInfo[i].waveReadPos = 0;
	}
}

void WAVE_init(){
	WAVE_readWave(&waveInfo[0]);
	for(i = 0; i < 120; i++){
		notes[i] = 0;
	}
}

