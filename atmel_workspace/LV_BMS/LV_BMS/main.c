#include <atmel_start.h>
#include <usart_serial.h>
#include <usart_handler.h>


int main(void)
{
	
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	uart_init();
	gpio_set_pin_level(relay_signal, true);


	/* Replace with your application code */
	while (1) {

		
		if(serial_receiving == 1)
		{
			if(serial_complete == 1)
			{
				usart_done();
				
				
			}
		}
	}
}



