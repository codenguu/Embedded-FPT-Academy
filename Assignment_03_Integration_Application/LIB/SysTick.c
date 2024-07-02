/*
 * SysTick.c
 *
 *  Created on: Jun 19, 2024
 *      Author: SF
 */
//INCLUDE
#include "SysTick.h"
#include "system_MKL46Z4.h"

SysTick_Handler_CallBack SysTick_CallBack = NULL;

void Systick_Init(uint32_t time_ms)
{
	SystemCoreClockUpdate ();		//Get Clock of core
	//Clock Source - processor clock
	SysTick->CTRL |= (1 << SysTick_CTRL_CLKSOURCE_Pos);
	//Clear the current value register
	SysTick->VAL = 0U;

	//Ensure time_ms does not exceed the maximum allowable value
	uint32_t max_time_ms = (uint32_t)(0xFFFFFFU * 1000) / SystemCoreClock;
	if (time_ms > max_time_ms)
	{
		time_ms = max_time_ms;
	}
	SysTick->LOAD = (time_ms * SystemCoreClock / 1000) - 1;	//time_ms Max ~= 800, F = DEFAULT_SYSTEM_CLOCK = 20971520U
}
void Systick_INTEnable(SysTick_Handler_CallBack systick_callBack)
{
	SysTick_CallBack = systick_callBack;
	SysTick->CTRL |= (1 << SysTick_CTRL_TICKINT_Pos);
}
void SysTick_Handler(void)
{
	SysTick_CallBack();
}
