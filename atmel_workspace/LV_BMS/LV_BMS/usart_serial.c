/*
 * usart_serial.c
 *
 * Created: 2020-02-25 13:23:47
 *  Author: mat15mal
 */ 
#include <atmel_start.h>

#define SERIAL_BUF_SIZE 200
volatile uint8_t serial_receiving = 0;
volatile uint8_t serial_complete = 0;

// Byte received counters
volatile uint8_t serial_received_bytes_counter = 0;
volatile uint8_t total_bytes = 0;

// RX and TX buffers
volatile uint8_t rx_buffer[SERIAL_BUF_SIZE] = { 0x00 };
volatile uint8_t tx_buffer[SERIAL_BUF_SIZE + 18] = "\r\nYour message : ";


static void serial_rx_cb(const struct usart_async_descriptor *const io_descr)
{
	// count - Received bytes counter
	uint8_t ch, count;
	
	//Read a character
	count = io_read(&USART_0.io, &ch, 1);
	
	
	//Check if we are receiving
	if(serial_receiving == 0)
	{
		//Check for newline or char ret
		if (ch != '\r' && ch != '\n')
		{
			//Set Rec Flag
			serial_receiving =1;
			
			//reset byte counter
			serial_received_bytes_counter = 0;
			
			//start filling buffer
			rx_buffer[serial_received_bytes_counter] = ch;
			
			//increment byte buffer
			serial_received_bytes_counter += count;
		}
	}
	else
	{
		//continue filling buffer
		rx_buffer[serial_received_bytes_counter] = ch;
		
		//increment byte buffer
		serial_received_bytes_counter += count;
		
		//check for nl or cr
		if (ch == '\r' || ch == '\n')
		{
			//set flag
			serial_complete = 1;
			
			//total bytes
			total_bytes = serial_received_bytes_counter - 2;
		}
		
		
		//check overflow
		if(serial_received_bytes_counter >= SERIAL_BUF_SIZE)
		{
			serial_received_bytes_counter = 0;
		}
	}
}

static void serial_tx_cb(const struct usart_async_descriptor *const io_descr) {
	
	// Do nothing when tx interrupt is called
	
}

void uart_init(){

	usart_async_register_callback(&USART_0, USART_ASYNC_TXC_CB, serial_tx_cb);
	usart_async_register_callback(&USART_0, USART_ASYNC_RXC_CB, serial_rx_cb);
	usart_async_enable(&USART_0);
	
}