/*
 * spi_serial.c
 *
 * Created: 2020-03-03 13:32:52
 *  Author: mat15mal
 */ 
#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "spi_serial.h"
#include "spi_pec.h"



void spi_init(void)
{

spi_m_sync_get_io_descriptor(&SPI_0, &spi_io);
spi_m_sync_enable(&SPI_0);
}



void SPI_test(void)
{

	static uint8_t example_SPI_0[2] = {0b00000000, 0b00010000};
	
	struct io_descriptor *spi_io;
	spi_m_sync_get_io_descriptor(&SPI_0, &spi_io);

	spi_m_sync_enable(&SPI_0);
		
		
	gpio_set_pin_level(spi_cs, false);
	io_write(spi_io, example_SPI_0, 2);
	gpio_set_pin_level(spi_cs, true);	
		
		
		
		
}





/* 
Generic function to write 68xx commands and write payload data. 
Function calculates PEC for tx_cmd data and the data to be transmitted.
 */
void write_68(uint8_t total_ic, //Number of ICs to be written to 
			  uint8_t tx_cmd[2], //The command to be transmitted 
			  uint8_t data[] // Payload Data
			  )
{
	const uint8_t BYTES_IN_REG = 6;
	const uint8_t CMD_LEN = 4+(8*total_ic);
	uint8_t *cmd;
	uint16_t data_pec;
	uint16_t cmd_pec;
	uint8_t cmd_index;
	
	cmd = (uint8_t *)malloc(CMD_LEN*sizeof(uint8_t));
	cmd[0] = tx_cmd[0];
	cmd[1] = tx_cmd[1];
	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);
	
	cmd_index = 4;
	for (uint8_t current_ic = total_ic; current_ic > 0; current_ic--)               // Executes for each LTC681x, this loops starts with the last IC on the stack.
    {	                                                                            //The first configuration written is received by the last IC in the daisy chain
		for (uint8_t current_byte = 0; current_byte < BYTES_IN_REG; current_byte++)
		{
			cmd[cmd_index] = data[((current_ic-1)*6)+current_byte];
			cmd_index = cmd_index + 1;
		}
		
		data_pec = (uint16_t)pec15_calc(BYTES_IN_REG, &data[(current_ic-1)*6]);    // Calculating the PEC for each ICs configuration register data
		cmd[cmd_index] = (uint8_t)(data_pec >> 8);
		cmd[cmd_index + 1] = (uint8_t)data_pec;
		cmd_index = cmd_index + 2;
	}
	


	
	gpio_set_pin_level(spi_cs, false);
	io_write(spi_io, cmd, CMD_LEN);
	gpio_set_pin_level(spi_cs, true);
}


void LTC681x_adcv( uint8_t MD, //ADC Mode
uint8_t DCP, //Discharge Permit
uint8_t CH //Cell Channels to be measured
)
{
	uint8_t cmd[2];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x02;
	md_bits = (MD & 0x01) << 7;
	cmd[1] =  md_bits + 0x60 + (DCP<<4) + CH;
	gpio_set_pin_level(led_1, true);
	cmd_68(cmd);
}

void cmd_68(uint8_t tx_cmd[2]) //The command to be transmitted
{
	uint8_t cmd[4];
	uint16_t cmd_pec;
	uint8_t md_bits;
	gpio_set_pin_level(led_2, true);
	cmd[0] = tx_cmd[0];
	cmd[1] =  tx_cmd[1];
	cmd_pec = pec15_calc(2, cmd);
	cmd[2] = (uint8_t)(cmd_pec >> 8);
	cmd[3] = (uint8_t)(cmd_pec);
	gpio_set_pin_level(led_3, true);
	
	gpio_set_pin_level(spi_cs, false);
	io_write(spi_io, cmd, 4);
	gpio_set_pin_level(spi_cs, true);
	
	
}


uint16_t pec15_calc(uint8_t len, //Number of bytes that will be used to calculate a PEC
uint8_t *data //Array of data that will be used to calculate  a PEC
)
{
	uint16_t remainder,addr;
	remainder = 16;//initialize the PEC
	
	for (uint8_t i = 0; i<len; i++) // loops for each byte in data array
	{
		addr = ((remainder>>7)^data[i])&0xff;//calculate PEC table address
		
		remainder = (remainder<<8)^crc15Table[addr];
		
	}
	
	return(remainder*2);//The CRC15 has a 0 in the LSB so the remainder must be multiplied by 2
}


/* Start ADC Conversion for GPIO and Vref2  */
void LTC681x_adax(uint8_t MD, //ADC Mode
uint8_t CHG //GPIO Channels to be measured
)
{
	uint8_t cmd[4];
	uint8_t md_bits;
	
	md_bits = (MD & 0x02) >> 1;
	cmd[0] = md_bits + 0x04;
	md_bits = (MD & 0x01) << 7;
	cmd[1] = md_bits + 0x60 + CHG ;
	
	cmd_68(cmd);
}