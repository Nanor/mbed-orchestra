void CAN_init();
void CAN_InitMessage(void);
void CAN_IRQHandler();
void set_channel(int);
void set_volume(float);
int find_channel_up(int current);
int find_channel_down(int current);
