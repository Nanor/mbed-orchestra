int DEBUG_write(char* string);
int DEBUG_write_int(char* string, int data);

int read_usb_serial_none_blocking(char *buf,int length);
int write_usb_serial_blocking(char *buf,int length);

