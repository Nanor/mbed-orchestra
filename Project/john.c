#include "debug.h"
#include "keypad.h"
#include "lcd.h"
#include "dac.h"


void JOHN_wait(char* str){
	LCD_clear();
	LCD_write(str);
	
	while(1){
		int key = KEYPAD_get_key();
		
		if(key == 10){
			key = -1;
			return;
		}
	}
}


void JOHN_serialTest(){
	JOHN_wait("Waiting...");
	
	uint8_t inp;
	uint8_t lengthArray[2];
	int i;
	
	// Get length of datastream
	for(i = 0; i < 2; i++){
		lengthArray[i] = USB_readByte();
		if(lengthArray[i] == 255){
			//lengthArray[i] = 0;
		}		
	}
	
	for(i = 0; i < 2; i++){
		USB_writeByte(lengthArray[i]);
	}
	
	uint16_t length = ((lengthArray[0] == 255 ? 0 : lengthArray[0]) << 8) + lengthArray[1];
	
	// Confirm received length
	USB_writeByte('a');
	
	// Get data
	uint8_t dataArray[19];
	for(i = 0; i < 19; i++){
		inp = 0;
		while(inp == 0){
			inp = USB_readByte();
		}
		dataArray[i] = inp;
		
	}

	// Confirm reveived data
	USB_writeByte('b');
	
	char *data;
	
	/*
	for(i = 1; i < 20; i++){
		data[i] = i;
	}
	*/
	

	// Debug
	for(i = 0; i < 19; i++){
		USB_writeByte(dataArray[i]);
		//USB_writeByte('c');
	}
	
	
	
}

