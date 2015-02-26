#include "debug.h"
#include "keypad.h"
#include "lcd.h"
#include "dac.h"
#include <string.h>


void SERIAL_wait(char* str, int trigger){
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
		
		if(key == trigger){
			key = -1;
			return;
		}
	}
}

void SERIAL_wait_int(int n, int trigger){
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
		
		if(key == trigger){
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
		SERIAL_wait("Confirm Error:", 10);
		SERIAL_wait_int(conf, 10);
	}
	
}

uint16_t SERIAL_readLen(){
// read length of datastream
	uint8_t lengthArray[2];
	int i;
	uint8_t inp = 0;

	for(i = 0; i < 2; i++){
		inp = USB_readByte();
		lengthArray[i] = inp;
	}
	
	uint16_t a;
	a = (lengthArray[0] == 255 ? 0 : (lengthArray[0] << 8));
	uint16_t length = a + lengthArray[1];
	
	USB_writeByte('a');
	
	return(length);
}

void SERIAL_writeLen(uint16_t len){
	
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

uint8_t * SERIAL_read8Bytes(uint8_t * read8data){
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
	
	return(read8data);

}

void SERIAL_write8Bytes(uint8_t data[8]){
	int i;
	
	for (i = 0; i < 8; i++){
		USB_writeByte(data[i]);
	}
	
	SERIAL_readConfirmation();
}

uint8_t * SERIAL_readDataBlock(){

	uint16_t length = SERIAL_readLen();
	uint8_t * data = malloc(length+1);
	data[length] = '\0';
	uint8_t * current = malloc(8);
	int i;
	
	for(i = 0; i < length; i+=8){
		current = SERIAL_read8Bytes(current);
		int j;
		for(j = i; j < i+8; j++){
			data[j] = current[j%8];
		}
	}
	
	return(data);
}

void SERIAL_writeDataBlock(uint8_t * data){
	uint8_t * current = malloc(8);
	uint16_t length = strlen(data);
	int i;
	
	SERIAL_writeLen(length);
	for(i = 0; i < length; i++){
		current[i%8] = data[i];
		if(i % 8 == 7 && i != 0){
			SERIAL_write8Bytes(current);
		}		
	}
}


void SERIAL_serialTest(){

	SERIAL_wait("Waiting...", 10);
	
}

