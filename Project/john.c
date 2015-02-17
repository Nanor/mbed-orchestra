#include "debug.h"
#include "keypad.h"
#include "lcd.h"


void JOHN_wait(char* str){
	LCD_clear();
	LCD_write(str);
	
	while(1){
		int key = KEYPAD_get_key();
		
		if(key == 10){
			break;
		}
	}
}

void JOHN_serialTest(){
	JOHN_wait("Waiting...");
	uint8_t word[8];
	int i;
	for(i = 0; i < 8; i++){
		word[i] = read_usb_serial_byte();
	}
	
	DEBUG_write(word);
}

