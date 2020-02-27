/*
 * CFile1.c
 *
 * Created: 2020-02-25 13:21:28
 *  Author: mat15mal
 */ 

#include <atmel_start.h>
#include <usart_serial.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


uint8_t adc_buffer[2] = {0, 0};
uint16_t res = 0;
uint8_t sign_res = 0;



uint8_t thou = 0;
uint8_t hund = 0;
uint8_t tens = 0;
uint8_t ones = 0;
uint8_t temp[2] = {0, 0};
uint8_t adc_res[4] = {0, 0, 0, 0};
uint8_t adc_rest[4] = {0, 0, 0, 0};
char res_string;

void usart_done(void);
void usart_return(uint8_t rx[], uint8_t tx[]);
void usart_send(uint8_t *str1);



// Handles the usart command
void usart_done(void)
{
	
	if(rx_buffer[0] == 'o' && rx_buffer[1] == 'n'){
		gpio_set_pin_level(relay_signal, true);
		usart_send("Relay ON");
		delay_ms(50);
		usart_send("Relay test");
	}
	
	else if(rx_buffer[0] == 'o' && rx_buffer[1] == 'f' && rx_buffer[2] =='f')
	{
		gpio_set_pin_level(relay_signal, false);
		usart_send("LED OFF");
		
	 }
	 
	 else if (rx_buffer[0] == 'a' && rx_buffer[1] == 'd' && rx_buffer[2] =='c')
	 {
		 gpio_set_pin_level(led_1, true);
		// usart_send(" ADC value is:");
		// delay_ms(50);
		 //usart_send("1GA");
		 usart_return(rx_buffer[1], tx_buffer);
	 }
	 else if (rx_buffer[0] == 't' && rx_buffer[1] == 'e' && rx_buffer[2] =='s')
	 {
		 
		 gpio_set_pin_level(led_1, true);
		 usart_send(rx_buffer);
	 }
	 else if (rx_buffer[0] == '1')
	 {
		adc_sync_read_channel(&ADC_0, 0, adc_buffer, 2);
		//usart_send(adc_buffer);
		temp[1] = adc_buffer[1];
		temp[0] = adc_buffer[0];
		res = (temp[1] << 8) | temp[0];
		usart_send(res);
	 }
	  else if (rx_buffer[0] == '2')
	 {
		adc_sync_read_channel(&ADC_0, 0, adc_buffer, 2);
		//usart_send(adc_buffer);
		temp[1] = adc_buffer[1];
		temp[0] = adc_buffer[0];
		res = (temp[1] << 8) | temp[0];
		
		thou = res / 1000 % 10;
		hund = res / 100  % 10;
		tens = res / 10   % 10;
		ones = res % 10;

		adc_rest[0] = thou + 48;
		adc_rest[1] = hund + 48;
		adc_rest[2] = tens + 48;
		adc_rest[3] = ones + 48;
		
		usart_return(adc_rest, tx_buffer);
		
	 }
	 
	 
	 
	 
	 
	 else
	 {	 
		 //send back
		 usart_send("Error: No such command");
	 }
		//reset flags
	 	serial_receiving = 0;
	 	serial_complete = 0;
}

//sends an the rx array on usart
void usart_return(uint8_t rx[], uint8_t tx[])
{
		//copy message to tx buffer
		memcpy(&tx[17], &rx[0], SERIAL_BUF_SIZE);

		//print
		io_write(&USART_0.io, tx, strlen(rx) + 17);
		//io_write(&USART_0.io, msg, total_bytes + 16);
		
		//clear memory
		memset(&rx, 0x00, SERIAL_BUF_SIZE);
	
}

//sends a the string on usart (might work with arrays aswell)
void usart_send(uint8_t *str1)
{
	//Copy the string to the tx_buffer, so that it can be sent using io_write
	memcpy(&tx_buffer[17], &str1[0], SERIAL_BUF_SIZE);
	
	//print to the serialcom port
	io_write(&USART_0.io, tx_buffer, (17  + strlen(str1)));
	//io_write(&USART_0.io, msg, total_bytes + 16);
	
	//clear memory, so that there is a clean buffer for next message
	memset(&rx_buffer, 0x00, SERIAL_BUF_SIZE);
	
}











// 		adc_res[3] = (res/1000)%10;
// 		adc_res[2] = (res/100)%10;
// 		adc_res[1] = (res/10)%10;
// 		adc_res[0] = res % 10;
//
// 		res_string = (char) res;
//
//
// 		thou = res / 1000 % 10;
// 		hund = res / 100  % 10;
// 		tens = res / 10   % 10;
// 		ones = res % 10;
//
//
//
//
// 		adc_rest[3] = thou + 48;
// 		adc_rest[2] = hund + 48;
// 		adc_rest[1] = tens + 48;
// 		adc_rest[0] = ones + 48;
//
// 		usart_send(res_string);
//usart_return(adc_res, tx_buffer);



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
