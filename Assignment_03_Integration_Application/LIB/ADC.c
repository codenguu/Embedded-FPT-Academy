/*
 * ADC.c
 *
 *  Created on: Jun 27, 2024
 *      Author: SF
 */

#include "ADC.h"

ADC0_IRQHandlerCallback ADC_Callbackfunc = NULL;

void ADC_Init(ADC_Config_t *adcConfig)
{
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; // Enable clock for ADC0
	if(adcConfig->channel != ADC_TEMP_SENSOR)
	{
		CLOCK_PortInit(adcConfig->PORTx); // Enable clock for PORT
	}

	 // Set MUX to ADC function is disable = Analog
	adcConfig->PORTx->PCR[adcConfig->PIN] &= ~PORT_PCR_MUX_MASK;

	// Bus clock
	ADC0->CFG1 |= ADC_CFG1_ADICLK(0); //Sets the ADCK to the input clock ÷ 1

	//Select SW or HW
	if(adcConfig->trigger == ADC_TRIGGER_HW)
	{
		ADC0->SC2 |= ADC_SC2_ADTRG_MASK;
		//Interconect PIT - ADC
		SIM->SOPT7 &= ~SIM_SOPT7_ADC0TRGSEL_MASK;
		SIM->SOPT7 |= SIM_SOPT7_ADC0TRGSEL(0b0100);

		SIM->SOPT7 |= SIM_SOPT7_ADC0ALTTRGEN(1);

		SIM->SOPT7 |= SIM_SOPT7_ADC0PRETRGSEL(0);
	}
	else
	{
		ADC0->SC2 &= ~ADC_SC2_ADTRG_MASK;
	}
	//Select Single ended of differential mode
	ADC0->SC1[0] |= ADC_SC1_DIFF(adcConfig->output_mode);

	// 8, 12, 10, 16-bit mode
	ADC0->CFG1 |= ADC_CFG1_MODE(adcConfig->bit_mode);

	//Continuous Conversion
	ADC0->SC3 &= ~ADC_SC3_ADCO_MASK;

	// voltage reference
	ADC0->SC2 |= ADC_SC2_REFSEL(0u);
}

uint16_t ADC_ReadPolling(ADC_Config_t *adcConfig)
{
	//Select Channel and Start convertion
	ADC0->SC1[0] = (ADC0->SC1[0] & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(adcConfig->channel);
	//Wait EOC = 1;
	while((ADC0->SC1[0] & ADC_SC1_COCO_MASK) == 0);
	//Read
	return ADC0->R[0];
}

void ADC_ReadInterrupt(ADC_Config_t *adcConfig)
{
	ADC0->SC1[0] |= ADC_SC1_AIEN(1);	// configure interrupt  Enable
	NVIC->ISER[0] |= (1 << 15u);		//NVIC
	ADC_Callbackfunc = adcConfig->adcCallfunc;
	//Select Channel and Start convertion
	ADC0->SC1[0] = (ADC0->SC1[0] & ~ADC_SC1_ADCH_MASK) | ADC_SC1_ADCH(adcConfig->channel);
}
uint16_t ADC_ReadDigital()
{
	uint16_t digital;
	digital = ADC0->R[0];
	return digital;
}
void ADC0_IRQHandler(void)
{
	ADC_Callbackfunc();
}




