#include "debug.h"
#include "i2c.h"
#include "systick.h"
#include "lcd.h"
#include "keypad.h"

int eval(char* string, int i)
{
	return(4);
}

void main(void)
{
	DEBUG_init();
	I2C_init();
	//SYSTICK_init();
	LCD_init();
	
	char c = '\0';
	char last = '\0';
	char input[16] = {};
	int i = 0;
	
	while(1)
	{
		c = KEYPAD_get_char();			
		if (c != last && c != '\0')
		{
			if(i == 17)
			{
				LCD_clear();
				i = 0;
			}
			else if (c == 'D')
			{
				LCD_send_char('=');
				int ans = eval(input, i);
				LCD_write_int(ans,1);
				i = 17;
			}
			else if (c >= '0' && c <= '9')
			{
				LCD_send_char(c);
			}
			else if (c != '#')
			{
				if (c == 'A') LCD_send_char('+');
				if (c == 'B') LCD_send_char('-');
				if (c == 'C') LCD_send_char('/');
			}
			
		}
		last = c;

	
	}
	
	
/*	while(1)
	{
		
		c = KEYPAD_get_char();			
		if (c != last && c != '\0')
		{
			LCD_send_char(c);
		}
		last = c;
	}

	/*int count = 0;
	
	int i = 0;
	for (i = 0; i < 128; i++)
	{
		if (I2C_send(i, 1, 1) == SUCCESS)
		{
			DEBUG_write_int("Slave found in address %d.\r\n", i);
						
			count += 1;
		}
	}
	
	DEBUG_write_int("Found %d slaves in total.\r\n", count);*/
}
