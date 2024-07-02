/*
 * ADC.h
 *
 *  Created on: Jun 27, 2024
 *      Author: SF
 */

#ifndef ADC_H_
#define ADC_H_

#include "MKL46Z4.h"
#include "stdio.h"
#include "User_Clock.h"
#include "User_port.h"
#include "PIT.h"

typedef void (*ADC0_IRQHandlerCallback)();

typedef enum
{
	ADC_TRIGGER_SW = 0U,
	ADC_TRIGGER_HW = 1U
}ADC_Trigger_t;

typedef enum
{
	ADC_8BIT_CONVERTION = 0U,
	ADC_12BIT_CONVERTION = 1U,
	ADC_10BIT_CONVERTION = 2U,
	ADC_16BIT_CONVERTION = 3U
}ADC_Bit_Mode_t;
typedef enum
{
	ADC_SINGLE_END = 0U,	//single-ended 16-bit, 12-bit, 10-bit, and 8-bit modes
	ADC_DIFFERENTIAL = 1U		//differential 16-bit, 13-bit, 11-bit, and 9-bit modes
}ADC_Output_Mode_t;

typedef enum
{
	ADC_CHANNEL_DADP0 = 0U,
	ADC_CHANNEL_DADP1 = 1U,
	ADC_CHANNEL_DADP2 = 2U,
	ADC_CHANNEL_DADP3 = 3U,
	ADC_CHANNEL_AD4,
	ADC_CHANNEL_AD5,
	ADC_CHANNEL_AD6,
	ADC_CHANNEL_AD7,
	ADC_CHANNEL_AD8,
	ADC_CHANNEL_AD9,
	ADC_CHANNEL_AD10,
	ADC_CHANNEL_AD11,
	ADC_CHANNEL_AD12,
	ADC_CHANNEL_AD13,
	ADC_CHANNEL_AD14,
	ADC_CHANNEL_AD15,
	ADC_CHANNEL_AD16,
	ADC_CHANNEL_AD17,
	ADC_CHANNEL_AD18,
	ADC_CHANNEL_AD19,
	ADC_CHANNEL_AD20,
	ADC_CHANNEL_AD21,
	ADC_CHANNEL_AD22,
	ADC_CHANNEL_AD23,
	ADC_TEMP_SENSOR = 26U,

}ADC_Channel_t;


typedef struct
{
	PORT_Type	*PORTx;
	uint8_t		PIN;
	ADC_Trigger_t trigger;
	ADC_Channel_t channel;
	ADC_Output_Mode_t output_mode;
	ADC_Bit_Mode_t bit_mode;
	ADC0_IRQHandlerCallback adcCallfunc;
}ADC_Config_t;

void ADC_Init(ADC_Config_t *adcConfig);
uint16_t ADC_ReadPolling(ADC_Config_t *adcConfig);
void ADC_ReadInterrupt(ADC_Config_t *adcConfig);
uint16_t ADC_ReadDigital();
#endif /* ADC_H_ */
