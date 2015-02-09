#include "lpc17xx_can.h"
#include "can.h"
#include "debug.h"
#include "lpc17xx_pinsel.h"
#include "synth.h"
#include "math.h"

#define NONE 0
#define OFF 2
#define ON 1
#define PAR 3
#define PB 4
#define CHPR 5
#define PRCH 6

#define BAUDRATE 250000

CAN_MSG_Type TXMsg, RXMsg; 
int channel = 1;

float mainVolume = 1.0f;
int canActive[16];

void CAN_init()
{
	// Pinconfig
	PINSEL_CFG_Type PinCfg;
	PinCfg.Funcnum = 2;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Pinnum = 4;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 5;
	PINSEL_ConfigPin(&PinCfg);  
	PinCfg.Pinnum = 10;
	PinCfg.Funcnum = 0;
	PINSEL_ConfigPin(&PinCfg);

	// CAN start	
	CAN_Init(LPC_CAN2, BAUDRATE);

	// Interupt setup
	CAN_IRQCmd(LPC_CAN2, CANINT_RIE, ENABLE);
	CAN_SetAFMode(LPC_CANAF,CAN_AccBP);
	CAN_InitMessage();
	NVIC_SetPriority(CAN_IRQn, ((0x01<<3)|0x01));
	NVIC_EnableIRQ(CAN_IRQn);
	
	int i;
	for(i=0; i < 16; i++)
	{
		canActive[i] = 0;
	}
}

void CAN_InitMessage(void)
{
	// Sending message
	TXMsg.format = EXT_ID_FORMAT;
	TXMsg.id = 0x00001234;
	TXMsg.len = 8;
	TXMsg.type = DATA_FRAME;
	TXMsg.dataA[0] = TXMsg.dataA[1] = TXMsg.dataA[2] = TXMsg.dataA[3] = 0x00000000;
	TXMsg.dataB[0] = TXMsg.dataB[1] = TXMsg.dataB[2] = TXMsg.dataB[3] = 0x00000000;

	// Reciving message
	RXMsg.format = RXMsg.id = RXMsg.len = RXMsg.type = 0x00;
	RXMsg.dataA[0] = RXMsg.dataA[1] = RXMsg.dataA[2] = RXMsg.dataA[3] = 0x00000000;
	RXMsg.dataB[0] = RXMsg.dataB[1] = RXMsg.dataB[2] = RXMsg.dataB[3] = 0x00000000;
}

void CAN_IRQHandler()
{
	// Interupt handling
	uint8_t IntStatus;
	IntStatus = CAN_IntGetStatus(LPC_CAN2);

	if((IntStatus>>0)&0x01)
	{	
		// Import data from CAN bus.
		CAN_ReceiveMsg(LPC_CAN2,&RXMsg);
		
		if (RXMsg.len == 8)
		{
			// Text data
			DEBUG_write_int("%c", RXMsg.dataA[0]);
			DEBUG_write_int("%c", RXMsg.dataA[1]);
			DEBUG_write_int("%c", RXMsg.dataA[2]);
			DEBUG_write_int("%c", RXMsg.dataA[3]);
			DEBUG_write_int("%c", RXMsg.dataB[0]);
			DEBUG_write_int("%c", RXMsg.dataB[1]);
			DEBUG_write_int("%c", RXMsg.dataB[2]);
			DEBUG_write_int("%c", RXMsg.dataB[3]);
		}
		else
		{
			// Note playback
			// Unpack message data for note playback
			uint8_t msgchan = RXMsg.dataA[0];
			uint8_t note = RXMsg.dataA[1];
			uint8_t volume = RXMsg.dataA[2];
			uint8_t type = RXMsg.dataA[3];
			uint8_t control = RXMsg.dataB[0];
	
			//DEBUG_write_int("Note = %3d ", note);
			//DEBUG_write_int("Vol  = %3d ", volume);
			//DEBUG_write_int("Chan = %3d ",msgchan);
			//DEBUG_write_int("Type = %3d", type);
			//DEBUG_write_int("Control = %3d\r\n", control);
	
			if (channel == msgchan)
			{	
				DEBUG_write_int("Note = %3d ", note);
				DEBUG_write_int("Control = %3d\r\n", control);
												
				if (control == ON)
				{
					synth_note_on(note_to_freq(note), ((float)volume / pow(2,8)) * mainVolume);
				}
				else
				{
					synth_note_off(note_to_freq(note));
				}
			}

			if(control == ON)
			{
				int i;
				for(i=0; i < 16; i++)
				{
					if(msgchan-1 == i)
					{
						canActive[i] = 20;
					}
					else
					{
						if (canActive[i])
							canActive[i]--;
					}
				}
			}
		}
	}
}

int find_channel_up(int current)
{
	int i;
	for(i = current-1+1; i < 16; i++)
	{
		if(canActive[i])
		{
			return i+1;
		}
	}
	return current;
}

int find_channel_down(int current)
{
	int i;
	for(i = current-1-1; i >= 0; i--)
	{
		if(canActive[i])
		{
			return i+1;
		}
	}
	return current;
}

void set_volume(float vol)
{
	mainVolume = vol;
}

void set_channel(int chan)
{
	channel = chan;
}
