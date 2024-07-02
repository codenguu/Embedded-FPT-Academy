/*
 * PIT.c
 *
 *  Created on: Jun 27, 2024
 *      Author: SF
 */
#include "PIT.h"
#include "system_MKL46Z4.h"
#include "stdio.h"

PIT_IRQHandlerCallBack PIT_IRQcallBack = NULL;

void PIT_init_ms(uint32_t ms)
{
	SystemCoreClockUpdate();
	//Enable Clock
	SIM->SCGC6 |= SIM_SCGC6_PIT(1);

	//enable PIT
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;
	//RELOAD VALUE
	PIT->CHANNEL[0].LDVAL = ms*(SystemCoreClock/1000) - 1;
}

void PIT_Interrupt_En(PIT_IRQHandlerCallBack callBack)
{
	//Interrupt will be requested whenever TIF is set
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;
	//Enable NVIC for PIT
	NVIC->ISER[0] |= (1 << 22);
	PIT_IRQcallBack = callBack;
}
void PIT_IRQHandler(void)
{
	PIT_IRQcallBack();
	PIT_ClearFlag();
}
