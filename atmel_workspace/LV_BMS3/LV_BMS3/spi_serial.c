/*
 * spi_serial.c
 *
 * Created: 2020-03-03 13:32:52
 *  Author: mat15mal
 */ 
#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"


void SPI_test(void)
{

	static uint8_t example_SPI_0[4] = {0b11011111, 0b0, 0b11111111, 0b0};
	
	struct io_descriptor *spi_io;
	spi_m_sync_get_io_descriptor(&SPI_0, &spi_io);

	spi_m_sync_enable(&SPI_0);
		
		
	gpio_set_pin_level(spi_cs, false);
	io_write(spi_io, example_SPI_0, 4);
	gpio_set_pin_level(spi_cs, true);	
		
		
		
		
}