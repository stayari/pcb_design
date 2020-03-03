/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMC21 has 9 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7
#define GPIO_PIN_FUNCTION_I 8

#define v_sense GPIO(GPIO_PORTA, 2)
#define relay_signal GPIO(GPIO_PORTA, 5)
#define spi_miso GPIO(GPIO_PORTA, 8)
#define spi_cs GPIO(GPIO_PORTA, 9)
#define spi_mosi GPIO(GPIO_PORTA, 10)
#define spi_sck GPIO(GPIO_PORTA, 11)
#define can_tx GPIO(GPIO_PORTA, 24)
#define can_rx GPIO(GPIO_PORTA, 25)
#define led_3 GPIO(GPIO_PORTA, 27)
#define led_4 GPIO(GPIO_PORTA, 28)
#define button_1 GPIO(GPIO_PORTB, 2)
#define button_2 GPIO(GPIO_PORTB, 3)
#define usb_tx GPIO(GPIO_PORTB, 8)
#define usb_rx GPIO(GPIO_PORTB, 9)
#define led_1 GPIO(GPIO_PORTB, 22)
#define led_2 GPIO(GPIO_PORTB, 23)

#endif // ATMEL_START_PINS_H_INCLUDED
