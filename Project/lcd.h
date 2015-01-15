#include "i2c.h"

#include "string.h"

int LCD_init(void);
int LCD_send(char c);
int LCD_write(char* string);
int LCD_write_int(char* string, int i);
int LCD_set_pos(int x,int y);
int LCD_clear(void);
