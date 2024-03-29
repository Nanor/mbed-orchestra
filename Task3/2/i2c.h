#ifndef LCD_INCLUDED

#define LCD_INCLUDED

#include "lpc_types.h"

#define KBD 33
#define LCD 59

void I2C_init();
int I2C_send(uint32_t, uint8_t*, uint32_t);
int I2C_tr(uint32_t address, uint8_t* t_data, uint32_t t_length, uint8_t* r_data, uint32_t r_length);

#endif
