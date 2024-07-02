/*
 * gpio.c
 *
 *  Created on: Jun 14, 2024
 *      Author: SF
 */
#include "User_gpio.h"

void GPIO_Init(GPIO_Config_Type *GPIO_Config)
{
	//Port Data Direction Register
	if(GPIO_Config->pddr)
	{	//Output
		GPIO_Config->GPIOx->PDDR |= (1U << GPIO_Config->PIN);
	}
	else if(!GPIO_Config->pddr)
	{
		GPIO_Config->GPIOx->PDDR &=  ~(1U << GPIO_Config->PIN);
	}
}

