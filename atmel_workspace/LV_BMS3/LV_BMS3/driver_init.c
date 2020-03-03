/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>

#include <hpl_adc_base.h>

/*! The buffer size for USART */
#define USART_0_BUFFER_SIZE 16

struct spi_m_sync_descriptor  SPI_0;
struct usart_async_descriptor USART_0;
struct can_async_descriptor   CAN_0;

static uint8_t USART_0_buffer[USART_0_BUFFER_SIZE];

struct adc_sync_descriptor ADC_0;

struct temp_sync_descriptor TEMPERATURE_SENSOR_0;

void ADC_0_PORT_init(void)
{

	// Disable digital pin circuitry
	gpio_set_pin_direction(v_sense, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(v_sense, PINMUX_PA02B_ADC0_AIN0);
}

void ADC_0_CLOCK_init(void)
{
	hri_mclk_set_APBCMASK_ADC0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, ADC0_GCLK_ID, CONF_GCLK_ADC0_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, ADC0, _adc_get_adc_sync());
}

void SPI_0_PORT_init(void)
{

	// Set pin direction to input
	gpio_set_pin_direction(spi_miso, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(spi_miso,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(spi_miso, PINMUX_PA08D_SERCOM2_PAD0);

	gpio_set_pin_level(spi_mosi,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(spi_mosi, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(spi_mosi, PINMUX_PA10D_SERCOM2_PAD2);

	gpio_set_pin_level(spi_sck,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(spi_sck, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(spi_sck, PINMUX_PA11D_SERCOM2_PAD3);
}

void SPI_0_CLOCK_init(void)
{
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM2_GCLK_ID_CORE, CONF_GCLK_SERCOM2_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM2_GCLK_ID_SLOW, CONF_GCLK_SERCOM2_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBCMASK_SERCOM2_bit(MCLK);
}

void SPI_0_init(void)
{
	SPI_0_CLOCK_init();
	spi_m_sync_init(&SPI_0, SERCOM2);
	SPI_0_PORT_init();
}

/**
 * \brief USART Clock initialization function
 *
 * Enables register interface and peripheral clock
 */
void USART_0_CLOCK_init()
{

	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM4_GCLK_ID_CORE, CONF_GCLK_SERCOM4_CORE_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_gclk_write_PCHCTRL_reg(GCLK, SERCOM4_GCLK_ID_SLOW, CONF_GCLK_SERCOM4_SLOW_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	hri_mclk_set_APBCMASK_SERCOM4_bit(MCLK);
}

/**
 * \brief USART pinmux initialization function
 *
 * Set each required pin to USART functionality
 */
void USART_0_PORT_init()
{

	gpio_set_pin_function(usb_tx, PINMUX_PB08D_SERCOM4_PAD0);

	gpio_set_pin_function(usb_rx, PINMUX_PB09D_SERCOM4_PAD1);
}

/**
 * \brief USART initialization function
 *
 * Enables USART peripheral, clocks and initializes USART driver
 */
void USART_0_init(void)
{
	USART_0_CLOCK_init();
	usart_async_init(&USART_0, SERCOM4, USART_0_buffer, USART_0_BUFFER_SIZE, (void *)NULL);
	USART_0_PORT_init();
}

void CAN_0_PORT_init(void)
{

	gpio_set_pin_function(can_rx, PINMUX_PA25G_CAN0_RX);

	gpio_set_pin_function(can_tx, PINMUX_PA24G_CAN0_TX);
}
/**
 * \brief CAN initialization function
 *
 * Enables CAN peripheral, clocks and initializes CAN driver
 */
void CAN_0_init(void)
{
	hri_mclk_set_AHBMASK_CAN0_bit(MCLK);
	hri_gclk_write_PCHCTRL_reg(GCLK, CAN0_GCLK_ID, CONF_GCLK_CAN0_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
	can_async_init(&CAN_0, CAN0);
	CAN_0_PORT_init();
}

void TEMPERATURE_SENSOR_0_CLOCK_init(void)
{
	hri_mclk_set_APBAMASK_TSENS_bit(MCLK);

	hri_gclk_write_PCHCTRL_reg(GCLK, TSENS_GCLK_ID, CONF_GCLK_TSENS_SRC | (1 << GCLK_PCHCTRL_CHEN_Pos));
}

void TEMPERATURE_SENSOR_0_init(void)
{
	TEMPERATURE_SENSOR_0_CLOCK_init();
	temp_sync_init(&TEMPERATURE_SENSOR_0, TSENS);
}

void system_init(void)
{
	init_mcu();

	// GPIO on PA05

	gpio_set_pin_level(relay_signal,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(relay_signal, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(relay_signal, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA09

	gpio_set_pin_level(spi_cs,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(spi_cs, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(spi_cs, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA27

	gpio_set_pin_level(led_3,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(led_3, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(led_3, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PA28

	gpio_set_pin_level(led_4,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(led_4, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(led_4, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB02

	// Set pin direction to input
	gpio_set_pin_direction(button_1, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(button_1,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(button_1, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB03

	// Set pin direction to input
	gpio_set_pin_direction(button_2, GPIO_DIRECTION_IN);

	gpio_set_pin_pull_mode(button_2,
	                       // <y> Pull configuration
	                       // <id> pad_pull_config
	                       // <GPIO_PULL_OFF"> Off
	                       // <GPIO_PULL_UP"> Pull-up
	                       // <GPIO_PULL_DOWN"> Pull-down
	                       GPIO_PULL_OFF);

	gpio_set_pin_function(button_2, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB22

	gpio_set_pin_level(led_1,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(led_1, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(led_1, GPIO_PIN_FUNCTION_OFF);

	// GPIO on PB23

	gpio_set_pin_level(led_2,
	                   // <y> Initial level
	                   // <id> pad_initial_level
	                   // <false"> Low
	                   // <true"> High
	                   false);

	// Set pin direction to output
	gpio_set_pin_direction(led_2, GPIO_DIRECTION_OUT);

	gpio_set_pin_function(led_2, GPIO_PIN_FUNCTION_OFF);

	ADC_0_init();

	SPI_0_init();
	USART_0_init();
	CAN_0_init();

	TEMPERATURE_SENSOR_0_init();
}
