#include <leds.h>

#define LED0 1, 1 << 18
#define LED1 1, 1 << 20
#define LED2 1, 1 << 21
#define LED3 1, 1 << 23

void LED_binDisplay(short i)
{
	GPIO_Set(LED0, i%2);
	i = i >> 1;
	GPIO_Set(LED1, i%2);
	i = i >> 1;
	GPIO_Set(LED2, i%2);
	i = i >> 1;
	GPIO_Set(LED3, i%2);
}

void LED_loop(int n)
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
