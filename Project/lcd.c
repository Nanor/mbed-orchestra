#include "lcd.h"

int LCD_init(void)
{
	uint8_t data[] = {0x00,0x35,0x00,0x9F,0x00,0x34,0x00,0x0C,0x00,0x02,0x00,0x01,0x00,0x80};

	if (I2C_send(LCD,data,14) == 0) return 0;

	return (LCD_clear());
}

int LCD_send(char c)
{
	uint8_t buf[] = {0x40,0x00};

	if (c >= '0' && c <= '9')
	{
		buf[1] = 0xB0 + (c-'0');
	}
	else if (c >= 'A' && c <= 'Z')
	{
		buf[1] = 0xC1 + (c-'A');
	}
	else if (c >= 'a' && c <= 'z')
	{
		buf[1] = 0xE1 + (c-'a');
	}
	else if (c >= ' ' && c <= '?')
	{
		buf[1] = 0xA0 + (c-' ');
	}
	
	return(I2C_send(LCD,buf,2));
}

int LCD_write(char* string)
{
	//uint8_t buf[] = {0x00, line ? 0xC0 : 0x80};
	while(*string != '\0')
	{
		int result = LCD_send(*string);
		if (result == 0) return(0);
		string++;
	}
	
	return(1);
}

int LCD_write_int(char* string, int i)
{
	char buf[sizeof(int)*3 + strlen(string)];
	snprintf(buf, sizeof buf, string, i);
	return (LCD_write(buf));
}

int LCD_set_pos(int x, int y)
{
	uint8_t buf[] = {0x00, (y ? 0xC0 : 0x80) + x};
	
	return(I2C_send(LCD,buf,2));
}

int LCD_clear(void)
{
	int i;
	for (i=0x80;i<0xD0;i++){
		if (LCD_send(' ') == 0) return 0;
	}
	LCD_set_pos(0,0);
	
	return 1;	
}
