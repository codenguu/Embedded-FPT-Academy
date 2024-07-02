/*
 * gpio.h
 *
 *  Created on: Jun 14, 2024
 *      Author: SF
 */

#ifndef USER_GPIO_H_
#define USER_GPIO_H_

#include "MKL46Z4.h"
#include "stdint.h"
#include "stdio.h"

//GPIO Select Data Direction enumeration
typedef enum
{
	GPIO_INPUT = 0U,	//Set pin is digital input
	GPIO_OUTPUT = 1U		//Set pin is digital output
}GPIO_PDDR_t;

typedef struct
{
	GPIO_Type 	*GPIOx;
	uint8_t 	PIN;
	GPIO_PDDR_t	pddr;
}GPIO_Config_Type;

void GPIO_Init(GPIO_Config_Type *GPIO_Config);

static inline void GPIO_TogglePin(GPIO_Type *GPIOx, uint8_t PIN)
{
	GPIOx->PTOR = (1U << PIN);
}
static inline void GPIO_SetPin(GPIO_Type * GPIOx, uint8_t PIN)
{
	GPIOx->PSOR = (1U << PIN);
}
static inline void GPIO_ClearPin(GPIO_Type * GPIOx, uint8_t PIN)
{
	GPIOx->PCOR = (1U << PIN);
}
static inline uint8_t GPIO_ReadPin(GPIO_Type *GPIOx, uint8_t PIN)
{
	if((GPIOx->PDIR &(1U << PIN))!= 0)
	{
		return 1;
	}
	return 0;
}

#endif /* USER_GPIO_H_ */
