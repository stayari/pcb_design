/*
 * adc.c
 *
 * Created: 2020-02-26 15:42:41
 *  Author: mat15mal
 */ 


struct adc_module adc_instance;
#define ADC_SAMPLES 128
uint16_t adc_result_buffer[ADC_SAMPLES];


void configure_adc(void)
{
	struct adc_config config_adc;
	adc_get_config_defaults(&config_adc);