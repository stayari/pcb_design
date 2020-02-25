/*
 * CFile1.c
 *
 * Created: 2020-02-25 13:21:28
 *  Author: mat15mal
 */ 

#include <atmel_start.h>
#include <usart_serial.h>
#include <string.h>
//char msg[200];

void usart_done(void)
{
	//reset flags
	serial_receiving = 0;
	serial_complete = 0;
	
	
	if(rx_buffer[0] == 'o' && rx_buffer[1] == 'n'){
		gpio_set_pin_level(relay_signal, true);
	}
	
	if(rx_buffer[0] == 'o' && rx_buffer[1] == 'f' && rx_buffer[2] =='f'){
		gpio_set_pin_level(relay_signal, false);
	 }
	 
	 if(rx_buffer[0] == 'a' && rx_buffer[1] == 'd' && rx_buffer[2] =='c'){
		 gpio_set_pin_level(led_1, true);
	 }

	//copy message to tx buffer
	memcpy(&tx_buffer[14], &rx_buffer[0], SERIAL_BUF_SIZE);
	//print
	io_write(&USART_0.io, tx_buffer, total_bytes + 16);
	//io_write(&USART_0.io, msg, total_bytes + 16);
	//clear memory
	memset(&rx_buffer, 0x00, SERIAL_BUF_SIZE);
	
	
	
}


	
// 
// 	char command[SERIAL_BUF_SIZE];
// 	strcpy(command, rx_buffer);
// 	
// 	
// 	char on[] = "on";
// 	
// 	
// 	if(comp(command, "on") == 1){
// 		gpio_set_pin_level(led_1, true);
// 
// 	}


// int comp(char str_in[], char str_cmp[]){
// 	int len = strlen(str_cmp);
// 	int i = 0;
// 	gpio_set_pin_level(led_2, true);
// 	while(i<strlen)
// 	{
// 		if(str_in[i] != str_cmp[i]){
// 			gpio_set_pin_level(led_3, true);
// 			if(i == 0)
// 			return 0;
// 		}
// 	i++;
// 	}
// 	gpio_set_pin_level(led_4, true);
// 	return 1;
//
//
// 	};
