#include "i2c.h"

#define Key1 0x8000
#define Key4 0x4000
#define Key7 0x2000
#define KeyS 0x1000
#define Key2 0x0800
#define Key5 0x0400
#define Key8 0x0200
#define Key0 0x0100
#define Key3 0x0080
#define Key6 0x0040
#define Key9 0x0020
#define KeyH 0x0010
#define KeyA 0x0008
#define KeyB 0x0004
#define KeyC 0x0002
#define KeyD 0x0001

uint16_t KEYPAD_get_keys();
char KEYPAD_get_char();
