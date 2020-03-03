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
	
	static uint8_t example_SPI_0[12] = "1111111111111";
	struct io_descriptor *spi_io;
	spi_m_sync_get_io_descriptor(&SPI_0, &spi_io);

	spi_m_sync_enable(&SPI_0);
	io_write(spi_io, example_SPI_0, 12);
}