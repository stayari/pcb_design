/*
 * usart_serial.h
 *
 * Created: 2020-02-25 13:24:06
 *  Author: mat15mal
 */ 


#ifndef USART_SERIAL_H_
#define USART_SERIAL_H_

#define SERIAL_BUF_SIZE 200

volatile uint8_t serial_receiving;
volatile uint8_t serial_complete;

volatile uint8_t serial_received_bytes_counter;
volatile uint8_t total_bytes;

volatile uint8_t rx_buffer[SERIAL_BUF_SIZE];
volatile uint8_t tx_buffer[SERIAL_BUF_SIZE + 18];



static void serial_rx_cb(const struct usart_async_descriptor *const io_descr);

static void serial_tx_cb(const struct usart_async_descriptor *const io_descr);

void uart_init();

#endif /* USART_SERIAL_H_ */