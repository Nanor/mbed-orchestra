#include "debug.h"
#include "i2c.h"
#include "systick.h"
#include "lcd.h"
#include "keypad.h"

int eval(char* string, int length)
{
	int i;
	char c;
	
	int total = 0;
	int number = 0;
	char op = '\0';
	
	for (i = 0; i < length; i++)
	{
		c = string[i];
		
		if (c >= '0' && c <= '9')
		{
			number = number * 10 + (c-'0');
		}
		else
		{
			switch (op)
			{
				case '+':
					total += number;
					break;
				case '-':
					total -= number;
					break;
				case '*':
					total *= number;
					break;
				case '/':
					total /= number;
					break;
				default:
					total = number;
			}
			number = 0;

			op = c;
		}
	}
	
	return(total);
	
}

void main(void)
{
	DEBUG_init();
	I2C_init();
	LCD_init();
	
	int count = 0;
	
	int i = 0;
	for (i = 0; i < 128; i++)
	{
		if (I2C_send(i, 1, 1) == SUCCESS)
		{
			DEBUG_write_int("Slave found in address %d.\r\n", i);
						
			count += 1;
		}
	}
	
	DEBUG_write_int("Found %d slaves in total.\r\n", count);
		
	char c = '\0';
	char last = '\0';
	char input[16] = {};
	i = 0;
	
	DEBUG_write("Start\r\n");
	
	while(1)
	{
		c = KEYPAD_get_char();
		if (c != last && c != '\0')
		{
			if (i == 16)
			{
				LCD_clear();
				i = 0;
			}
			if (c == 'A')
			{
				input[i] = '+';
			}
			else if (c == 'B')
			{
				input[i] = '-';
			}
			else if (c == 'C')
			{
				input[i] = '/';
			}
			else if (c == 'D')
			{
				input[i] = '=';	
			}
			else if (c == '#')
			{
				i = -1;
			}
			else
			{
				input[i] = c;
			}
			i++;
			LCD_clear();
			LCD_write_length(input,0,i);
			
			if (input[i-1] == '=')
			{
				LCD_write_int(eval(input,i), 1);
				i = 0;
			}
		}
		last = c;
	}
}
