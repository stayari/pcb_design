/*
 * uart.c
 *
 * Created: 2020-02-21 21:01:36
 *  Author: mat15mal
 */ 

#include "uart.h"

//void uart_init(){
	//
	//usart_async_register_callback(&USART_0, USART_ASYNC_TXC_CB, serial_tx_cb);
	//usart_async_register_callback(&USART_0, USART_ASYNC_TXC_CB, serial_rx_cb);
	//usart_async_enable(&USART_0);
	//
//}
//
//static void serial_rx_cb(const struct usart_async_descriptor *const io_descr) {
	//// Counter
	//uint8_t ch, count;
	//count = io_read(&USART_0.io,&ch, 1);
	//
	//io_write(&USART_0,"Hej",1);
	//
//}
//
//static void serial_tx_cb(const struct usart_async_descriptor *const io_descr) {
	//
	//// Do nothing when tx interrupt is called
	//
//}