#include "adc.h"
#include "lcd.h"
#include "systick.h"
#include "keypad.h"
#include "i2c.h"

float c;
float a = 0.1;

void calibrate(float* x, float a)
{
	while(KEYPAD_get_keys());
	LCD_write("Place object at ", 0);
	LCD_write("10cm, press key.",1);
	while(!KEYPAD_get_keys());
	float y = ADC_read();
	while(KEYPAD_get_keys());
	
	*x = y * a;
}

void main(void)
{
	ADC_init();
	LCD_init();
	I2C_init();
	
	calibrate(&c, a);
	SYSTICK_init(100);
}

void SysTick_Handler()
{
	float value = c * 1/(float)ADC_read();
	
	LCD_write_int(value*100, 0);
	LCD_send_char('c');
	LCD_send_char('m');
	int x;
	for (x=0;x<20;x++)
		LCD_send_char(' ');
	LCD_write("Key = Calibrate",1);
	if(KEYPAD_get_keys())
	{
		calibrate(&c,a);
	}
	
}
