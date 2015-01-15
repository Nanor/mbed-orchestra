#include "debug.h"
#include "lcd.h"

int main()
{
	DEBUG_init();	
	DEBUG_write("Hello");
	DEBUG_write_int("i=%d",4);

	return 0;
}
