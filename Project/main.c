#include "debug.h"
#include "lcd.h"
#include "synth.h"

int main()
{
	DEBUG_init();	
	LCD_init();
	
	DEBUG_write("Peripherals Initialised\r\n");
	
	DEBUG_write("Starting synth\r\n");
	synth_init();
	DEBUG_write("Done\r\n");
	
	while(1);
	return(1);
}
