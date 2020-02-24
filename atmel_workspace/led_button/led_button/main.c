#include <atmel_start.h>

uint8_t btn_new, btn_old;

uint8_t read_button2();

int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();

	/* Replace with your application code */
	while (1) {
		
		
		
		btn_new = gpio_get_pin_level(BTN1);
		
		if (btn_new > btn_old) {
			
			gpio_toggle_pin_level(LED1);
	
		}
		
		btn_old = btn_new;
		
	}
}



