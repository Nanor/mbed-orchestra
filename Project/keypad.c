#include "keypad.h"

uint16_t KEYPAD_get_keys()
{
	uint8_t t_buf[] = {0x7F};
	uint8_t r_buf[] = {0xFF};

	uint16_t output = 0;

	int i;
	for (i = 0; i < 4; i++)
	{
		output = output << 4;
		I2C_tr(KBD, t_buf, 1, r_buf, 1);
		output = output | (~r_buf[0] & 0x0F);
		t_buf[0] = (t_buf[0] >> 1) | 0x80;
		r_buf[0] = 0xFF;
	}
	
	t_buf[0] = 0x0F;
	I2C_send(KBD, t_buf, 1);
	
	return(output);
}

int KEYPAD_get_key()
{
	uint16_t keys = KEYPAD_get_keys();
	
	if (keys & Key1)
		return(1);
	if (keys & Key2)
		return(2);
	if (keys & Key3)
		return(3);
	if (keys & Key4)
		return(4);
	if (keys & Key5)
		return(5);
	if (keys & Key6)
		return(6);
	if (keys & Key7)
		return(7);
	if (keys & Key8)
		return(8);
	if (keys & Key9)
		return(9);
	if (keys & Key0)
		return(0);
	if (keys & KeyA)
		return(10);
	if (keys & KeyB)
		return(11);
	if (keys & KeyC)
		return(12);
	if (keys & KeyD)
		return(13);
	if (keys & KeyS)
		return(20);
	if (keys & KeyH)
		return(21);
		
	return(-1);
		
}
