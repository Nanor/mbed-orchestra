#include "lpc17xx_gpio.h"

#include <gpio.h>

void GPIO_set(int port, int pin, int value)
{
	GPIO_SetDir(port, pin, 1);
	
	if (value) {
		GPIO_SetValue(port, pin);
	}
	else
	{
		GPIO_ClearValue(port, pin);
	}
}
