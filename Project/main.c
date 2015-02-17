#include "i2c.h"
#include "debug.h"
#include "lcd.h"
#include "synth.h"
#include "keypad.h"
#include "can.h"
#include "menu.h"
#include "john.h"

int main()
{
	// Peripheral initialisation
	I2C_init();
	DEBUG_init();	
	LCD_init();

	// Function initialisation
	synth_init();
	CAN_init();
	
	//JOHN_serialTest();
	
	menu_display();	

	while (1)
	{
		menu_update();
	}
	
	// Keypad for synth debugging
	/*int down = 0;
	int key = -1;
	
	while(1)
	{
		key = KEYPAD_get_key();

		if ((key != -1) && !down)
		{
			int note = 69+key;
			synth_note_on(note_to_freq(note),1.0);
			LCD_write_int("%d",note_to_freq(note));
			down = 1;
		}
		if ((key == -1) && down)
		{
			synth_note_off(1.0);
			LCD_clear();
			down = 0;
		}
	}*/
	
	// Loop to allow interupts
	while(1);
	return(1);
	
}


