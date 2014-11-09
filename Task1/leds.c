// Serial code
#include "lpc17xx_gpio.h"
#include "lpc17xx_systick.h"

#define LED0 1, 1 << 18
#define LED1 1, 1 << 20
#define LED2 1, 1 << 21
#define LED3 1, 1 << 23

#define ONE_SECOND 6736842

void GPIO_Set(int port, int pin, int value)
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

void binDisplay(short i)
{
	GPIO_Set(LED0, i%2);
	i = i >> 1;
	GPIO_Set(LED1, i%2);
	i = i >> 1;
	GPIO_Set(LED2, i%2);
	i = i >> 1;
	GPIO_Set(LED3, i%2);
}

void setDelay()
{
	SYSTICK_ClearCounterFlag();
	SYSTICK_InternalInit(100);
	SYSTICK_Cmd(ENABLE);
	SYSTICK_IntCmd(ENABLE);
}

int i = 0;

void SysTick_Handler(void)
{
	i = i++ % 160;
	
	binDisplay(i/10);
}

void delay(float t)
{
	long i = 0;
	for(; i < t * 1000000; i++);
}

void loop(int n)
{
	int i = 0;
	for(i; i < n; i++)
	{
		int j;
		for (j = 1; j < 16; j = j << 1)
		{
			binDisplay(j);
			delay(0.25);
		}
	}
}

// Entry point for the program
void main(void)
{	
	loop(5);
	setDelay();

	return 0;
}
