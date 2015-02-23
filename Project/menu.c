#include <keypad.h>
#include <lcd.h>
#include <menu.h>
#include "can.h"
#include "synth.h"

int key_val = -1;

void menu_display()
{
	LCD_clear();
	LCD_write_int("Vol: %2d", getVolume());
	LCD_set_pos(8, 0);
	LCD_write_int("Chan: %2d", getChannel());
	LCD_set_pos(0,1);
	LCD_write_int("Voice: %2d", getVoice());
}

void menu_update()
{
	int key = KEYPAD_get_key();
	if (key == key_val)
	{
		return;
	}
	key_val = key;
	
	switch (key_val)
	{
		case 1:
			changeVolume(-10);
			break;
		case 2:
			changeVolume(-1);
			break;
		case 3:
			changeVolume(1);
			break;
		case 10:
			changeVolume(10);
			break;
		case 5:
			channelDown();	
			break;
		case 6:
			channelUp();
			break;
		case 4:
			find_channel_down();
			synth_note_off(-1);
			break;
		case 11:
			find_channel_up();
			synth_note_off(-1);
			break;
		case 8:
			decVoice();
			break;
		case 9:
			incVoice();
			break;
	}
	menu_display();
}
