#include "i2c.h"

#include "string.h"

int LCD_init(void);
int LCD_send_char(char c);
int LCD_write(char* string, int line);
int LCD_write_int(int i, int line);
int LCD_write_length(char* string, int line, int length);
int LCD_clear(void);
