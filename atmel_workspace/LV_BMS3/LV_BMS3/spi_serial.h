/*
 * spi_serial.h
 *
 * Created: 2020-03-03 13:33:12
 *  Author: mat15mal
 */ 


#ifndef SPI_SERIAL_H_
#define SPI_SERIAL_H_
struct io_descriptor *spi_io;

void SPI_test(void);
void write_68(uint8_t total_ic, //Number of ICs to be written to
uint8_t tx_cmd[2], //The command to be transmitted
uint8_t data[] // Payload Data
);

void LTC681x_adcv( uint8_t MD, //ADC Mode
uint8_t DCP, //Discharge Permit
uint8_t CH //Cell Channels to be measured
);


void spi_init(void);
//The command to be transmitted
 
void cmd_68(uint8_t tx_cmd[2]);

uint16_t pec15_calc(uint8_t len, //Number of bytes that will be used to calculate a PEC
uint8_t *data //Array of data that will be used to calculate  a PEC
);

/* Start ADC Conversion for GPIO and Vref2  */
void LTC681x_adax(uint8_t MD, //ADC Mode
uint8_t CHG //GPIO Channels to be measured
);


#endif /* SPI_SERIAL_H_ */


