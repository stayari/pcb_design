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
	

	
	
	if(rx_buffer[0] == 'o' && rx_buffer[1] == 'n'){
		gpio_set_pin_level(relay_signal, true);
		usart_send("Relay ON");
		delay_ms(50);
		usart_send("Relay test");
		
	}
	
	else if(rx_buffer[0] == 'o' && rx_buffer[1] == 'f' && rx_buffer[2] =='f'){
		gpio_set_pin_level(relay_signal, false);
		usart_send("LED OFF");
		
	 }
	 
	 else if (rx_buffer[0] == 'a' && rx_buffer[1] == 'd' && rx_buffer[2] =='c'){
		 
		 gpio_set_pin_level(led_1, true);
		 usart_send(" ADC value is:");
		 delay_ms(50);
		 //usart_send("1GA");
		 usart_send(rx_buffer[1]);
	 }
	 
	 else{
		 //send back
		 //usart_send("Error: No such command");
		 //delay_ms(50);
		 usart_return(rx_buffer, tx_buffer);
	 
	 }
		//reset flags
	 	serial_receiving = 0;
	 	serial_complete = 0;
}

void usart_return(uint8_t rx[], uint8_t tx[])
{
	
			if(rx[0] == 'o'){
				gpio_set_pin_level(led_2, true);
			}
			
			
		//copy message to tx buffer
		memcpy(&tx[17], &rx[0], SERIAL_BUF_SIZE);

		
		//print
		io_write(&USART_0.io, tx, strlen(rx) + 16);
		//io_write(&USART_0.io, msg, total_bytes + 16);
		//clear memory
		memset(&rx, 0x00, SERIAL_BUF_SIZE);
	
}

void usart_send(uint8_t *str1)
{

	
	
	memcpy(&tx_buffer[17], &str1[0], SERIAL_BUF_SIZE);
	//print
	io_write(&USART_0.io, tx_buffer, (17  + strlen(str1)));
	//io_write(&USART_0.io, msg, total_bytes + 16);
	//clear memory
	memset(&rx_buffer, 0x00, SERIAL_BUF_SIZE);
	
}





// //copy message to tx buffer
// memcpy(&tx_buffer[14], &rx_buffer[0], SERIAL_BUF_SIZE);
// //print
// io_write(&USART_0.io, tx_buffer, total_bytes + 16);
// //io_write(&USART_0.io, msg, total_bytes + 16);
// //clear memory
// memset(&rx_buffer, 0x00, SERIAL_BUF_SIZE);
// 	
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
