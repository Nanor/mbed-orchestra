#include "lpc17xx_can.h"
#include "can.h"
#include "debug.h"
#include "lpc17xx_pinsel.h"
#include "synth.h"
#include "math.h"

CAN_MSG_Type TXMsg, RXMsg; 

int channel = -1;

#define NONE 0
#define OFF 1
#define ON 2
#define PAR 3
#define PB 4
#define CHPR 5
#define PRCH 6


void CAN_init()
 {
  uint32_t baudrate = 250000;

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

  CAN_Init(LPC_CAN2, baudrate);
  
  CAN_IRQCmd(LPC_CAN2, CANINT_RIE, ENABLE);
  CAN_SetAFMode(LPC_CANAF,CAN_AccBP);
  CAN_InitMessage();
  NVIC_SetPriority(CAN_IRQn, ((0x01<<3)|0x01));
  NVIC_EnableIRQ(CAN_IRQn);

  
 }
  
 void CAN_InitMessage(void) {
   TXMsg.format = EXT_ID_FORMAT;
   TXMsg.id = 0x00001234;
   TXMsg.len = 8;
   TXMsg.type = DATA_FRAME;
   TXMsg.dataA[0] = TXMsg.dataA[1] = TXMsg.dataA[2] = TXMsg.dataA[3] = 0x00000000;
   TXMsg.dataB[0] = TXMsg.dataB[1] = TXMsg.dataB[2] = TXMsg.dataB[3] = 0x00000000;

   RXMsg.format = 0x00;
   RXMsg.id = 0x00;
   RXMsg.len = 0x00;
   RXMsg.type = 0x00;
   RXMsg.dataA[0] = RXMsg.dataA[1] = RXMsg.dataA[2] = RXMsg.dataA[3] = 0x00000000;
   RXMsg.dataB[0] = RXMsg.dataB[1] = RXMsg.dataB[2] = RXMsg.dataB[3] = 0x00000000;
 }

void CAN_IRQHandler()
{
	//DEBUG_write("interrupt\n\r");
	uint8_t IntStatus;
	/* get interrupt status
	* Note that: Interrupt register CANICR will be reset after read.
	* So function "CAN_IntGetStatus" should be call only one time
	*/
	IntStatus = CAN_IntGetStatus(LPC_CAN2);
	//check receive interrupt
	if((IntStatus>>0)&0x01)
	{
		CAN_ReceiveMsg(LPC_CAN2,&RXMsg);
		uint8_t msgchan = RXMsg.dataA[0];
		uint8_t note = RXMsg.dataA[1];
		uint8_t volume = RXMsg.dataA[2];
		uint8_t type = RXMsg.dataA[3];
		uint8_t control = RXMsg.dataB[0];

		//DEBUG_write_int("Channel = %u\r\n", msgchan);
		//DEBUG_write_int("Note = %u\n\r", note);
		if (control == NONE)
		{
			return;
		}
		if (channel == -1)
		{
			channel = msgchan;
		}
	
		if (msgchan == channel)
			{
			if (control == ON)
			{
				synth_note_on(note_to_freq(note), (float)volume / pow(2,8));
			}
			if (control == OFF)
			{
				synth_note_off(1);
			}
		}


	}
}


