#include "i2c.h"
#include "debug.h"
#include "lcd.h"
#include "synth.h"
#include "keypad.h"

int main()
{
	I2C_init();
	DEBUG_init();	
	LCD_init();

	synth_init();

	int down = 0;
	int key = -1;
	
	while(1)
	{
		//LCD_clear();
		key = KEYPAD_get_key();
		//LCD_write_int("%d",key);

		if ((key != -1) && !down)
		{
			//int note = 21 + (key * (33-21));
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
	}
	
	while(1);
	return(1);
}
