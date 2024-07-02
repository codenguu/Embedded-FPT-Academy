/*
 * PIT.h
 *
 *  Created on: Jun 27, 2024
 *      Author: SF
 */
#ifndef PIT_H_
#define PIT_H_
#include "MKL46Z4.h"
typedef void (*PIT_IRQHandlerCallBack)();

void PIT_init_ms(uint32_t ms);
static inline void PIT_StartTimer()
{
	//Start PIT
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN(1U);
}
static inline void PIT_DisableTimer()
{
	//Disable PIT
	PIT->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;
}
static inline void PIT_ClearFlag()
{
	//Writing 1 to this flag clears it. Writing 0 has no effect.
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;
}
void PIT_Interrupt_En(PIT_IRQHandlerCallBack callBack);

#endif /* PIT_H_ */
