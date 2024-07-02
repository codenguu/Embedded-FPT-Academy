/*
 * Middleware.c
 *
 *  Created on: Jun 16, 2024
 *      Author: SF
 */
#include "Middleware.h"


void LED_Init(PORT_Config_t *PortConfig, GPIO_Config_Type *GpioConfig)
{
	CLOCK_PortInit(PortConfig->PORTx);
	PORT_Pin_Init(PortConfig);
	GPIO_Init(GpioConfig);
}


void BTN_Init(PORT_Config_t *PortConfig, GPIO_Config_Type *GpioConfig)
{
	CLOCK_PortInit(PortConfig->PORTx);
	PORT_Pin_Init(PortConfig);
	GPIO_Init(GpioConfig);
	PORT_EXTI_Config(PortConfig);
}

void Delay(uint32_t time_ms)
{
	Systick_Init(time_ms);
	Systick_Enable();
	while(Systick_ReadFlag() == 0);
	Systick_Disable();
}
