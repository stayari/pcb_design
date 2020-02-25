#include <atmel_start.h>
#include <usart_serial.h>


int main(void)
{
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	uart_init();
	

	/* Replace with your application code */
	while (1) {
		
		if(serial_receiving == 1)
		{
			if(serial_complete == 1)
			{
				//reset flags
				serial_receiving = 0;
				serial_complete = 0;
				
				
				
				
				gpio_set_pin_level(led_1, true);
				
				if(rx_buffer[0] == 'o' && rx_buffer[1] == 'n'){
					gpio_set_pin_level(relay_signal, true);
				}
				if(rx_buffer[0] == 'o' && rx_buffer[1] == 'k' && rx_buffer[2] =='k'){
					gpio_set_pin_level(relay_signal, false);
				}
				
				//copy message to tx buffer
				memcpy(&tx_buffer[14], &rx_buffer[0], SERIAL_BUF_SIZE);
				//print
				io_write(&USART_0.io, tx_buffer, total_bytes + 16);
				//clear memory
				memset(&rx_buffer, 0x00, SERIAL_BUF_SIZE);
			}
		}
	}
}



