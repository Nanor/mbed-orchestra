#include <keypad.h>
#include <lcd.h>
#include <menu.h>
#include "can.h"
#include "synth.h"

int menu_volume = 10;
int menu_channel = 1;
int key_val = -1;

void menu_display()
{
	LCD_clear();
	LCD_write_int("Vol: %2d", menu_volume);
	LCD_set_pos(8, 0);
	LCD_write_int("Chan: %2d", menu_channel);
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
		case 2:
			if (menu_volume > 0)
			{
				menu_volume--;
				set_volume((float)menu_volume / 10);
				menu_display();
			}
			break;
		case 3:
			if (menu_volume < 10)
			{
				menu_volume++;
				set_volume((float)menu_volume / 10);
				menu_display();
			}
			break;
		case 5:
			if (menu_channel > 1)
			{
				synth_note_off(-1);
				menu_channel--;
				set_channel(menu_channel);
				menu_display();		
			}
			break;
		case 6:
			if (menu_channel < 16)
			{
				synth_note_off(-1);
				menu_channel++;
				set_channel(menu_channel);
				menu_display();		
			}
			break;
		case 4:
			menu_channel = find_channel_down(menu_channel);
			synth_note_off(-1);
			set_channel(menu_channel);
			menu_display();		
			break;
		case 11:
			menu_channel = find_channel_up(menu_channel);
			synth_note_off(-1);
			set_channel(menu_channel);
			menu_display();		
			break;
		case 8:
			decVoice();
			menu_display();
			break;
		case 9:
			incVoice();
			menu_display();
			break;
	}
}
