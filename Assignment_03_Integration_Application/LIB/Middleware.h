/*
 * Middleware.h
 *
 *  Created on: Jun 16, 2024
 *      Author: SF
 */

#ifndef MIDDLEWARE_H_
#define MIDDLEWARE_H_

#include "SysTick.h"
#include "User_Clock.h"
#include "User_gpio.h"
#include "User_port.h"



void LED_Init(PORT_Config_t *PortConfig, GPIO_Config_Type *GpioConfig);
void BTN_Init(PORT_Config_t *PortConfig, GPIO_Config_Type *GpioConfig);
void Delay(uint32_t time_ms);
static inline void LED_ON(GPIO_Config_Type *GpioConfig)
{
	GPIO_ClearPin(GpioConfig->GPIOx, GpioConfig->PIN);
}
static inline void LED_OFF(GPIO_Config_Type *GpioConfig)
{
	GPIO_SetPin(GpioConfig->GPIOx, GpioConfig->PIN);
}
static inline void LED_TogglePin(GPIO_Config_Type *GpioConfig)
{
	GPIO_TogglePin(GpioConfig->GPIOx, GpioConfig->PIN);
}

#endif /* MIDDLEWARE_H_ */
