#include "lpc17xx_i2c.h"
#include "lpc17xx_pinsel.h"

#include "i2c.h"

void I2C_init()
{
	PINSEL_CFG_Type PinCfg; // declare data struct with param members
 
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Funcnum = 3;
	PinCfg.Portnum = 0;
	
	PinCfg.Pinnum = 0;
	PINSEL_ConfigPin(&PinCfg); // configure pin 0 of port0
	
	PinCfg.Pinnum = 1;
	PINSEL_ConfigPin(&PinCfg); // configure pin 1 of port0
	
	I2C_Init(LPC_I2C1, 100000); // Initialize I2C peripheral
	I2C_Cmd(LPC_I2C1, ENABLE); // Enable I2C1 operation 
}

int I2C_send(uint32_t address, uint8_t* data, uint32_t length)
{
	I2C_M_SETUP_Type i2c_setup;
	i2c_setup.sl_addr7bit = address;
	i2c_setup.tx_data = data;
	i2c_setup.tx_length = length;
	i2c_setup.rx_length = 0;
	i2c_setup.rx_data = NULL;
	i2c_setup.retransmissions_max = 3;

	return(I2C_MasterTransferData(LPC_I2C1, &i2c_setup, I2C_TRANSFER_POLLING));
}

int I2C_tr(uint32_t address, uint8_t* t_data, uint32_t t_length, uint8_t* r_data, uint32_t r_length)
{
	I2C_M_SETUP_Type i2c_setup;
	i2c_setup.sl_addr7bit = address;
	i2c_setup.tx_data = t_data;
	i2c_setup.tx_length = t_length;
	i2c_setup.rx_length = r_length;
	i2c_setup.rx_data = r_data;
	i2c_setup.retransmissions_max = 3;

	return(I2C_MasterTransferData(LPC_I2C1, &i2c_setup, I2C_TRANSFER_POLLING));
}

