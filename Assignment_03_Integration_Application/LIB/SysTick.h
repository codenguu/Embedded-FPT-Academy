/*
 * SysTick.h
 *
 *  Created on: Jun 19, 2024
 *      Author: SF
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "MKL46Z4.h"
#include "stdio.h"

typedef void (*SysTick_Handler_CallBack)();

void Systick_Init(uint32_t time_ms);

static inline void Systick_Enable()
{
	SysTick->CTRL |= (1 << SysTick_CTRL_ENABLE_Pos);
}
static inline void Systick_Disable()
{
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void Systick_INTEnable(SysTick_Handler_CallBack systick_callBack);

static inline void Systick_INTDisable()
{
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
}
static inline uint8_t Systick_ReadFlag()
{
	return (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) != 0;
}
static inline uint32_t Systick_ReadCurVal()
{
	return SysTick->VAL;
}

#endif /* SYSTICK_H_ */
