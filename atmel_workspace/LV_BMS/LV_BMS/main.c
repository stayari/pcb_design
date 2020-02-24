#include <atmel_start.h>
#comment55

volatile uint8_t serial_receiving = 0;
volatile uint8_t serial_complete = 0;

// Byte received counters
volatile uint8_t serial_received_bytes_counter = 0;
volatile uint8_t total_bytes = 0;

#define SERIAL_BUF_SIZE 200

// RX and TX buffers
volatile uint8_t rx_buffer[SERIAL_BUF_SIZE] = { 0x00 };
volatile uint8_t tx_buffer[SERIAL_BUF_SIZE + 14] = "Your messages : ";


static void serial_rx_cb(const struct usart_async_descriptor *const io_descr)
{
	// Counter
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



