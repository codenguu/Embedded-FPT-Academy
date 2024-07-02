/*
 * mylib.c
 *
 *  Created on: Jun 7, 2024
 *      Author: SF
 */
#include "User_port.h"

static CallBackType PORTCD_CallBack = NULL;
static CallBackType PORTA_CallBack = NULL;


void PORT_Pin_Init(PORT_Config_t *UserConfig)
{
	UserConfig->PORTx->PCR[UserConfig->PIN] &= ~PORT_PCR_MUX_MASK;
	UserConfig->PORTx->PCR[UserConfig->PIN] |= PORT_PCR_MUX(UserConfig->mux);

	switch(UserConfig->pull)
	{
		case PORT_PULL_DISABLE:
			UserConfig->PORTx->PCR[UserConfig->PIN] |= PORT_PULL_DISABLE;
			break;
		case PORT_PULL_DOWN:
			UserConfig->PORTx->PCR[UserConfig->PIN] |= PORT_PULL_DOWN;
			break;
		case PORT_PULL_UP:
			UserConfig->PORTx->PCR[UserConfig->PIN] |= PORT_PULL_UP;
			break;
	}
}

void PORT_EXTI_Config(PORT_Config_t *UserConfig)
{
	if(PORT_INTERRUPT_DISABLE != UserConfig->irqc)
	{
		UserConfig->PORTx->PCR[UserConfig->PIN] &= ~PORT_PCR_IRQC_MASK;
		UserConfig->PORTx->PCR[UserConfig->PIN] |= PORT_PCR_IRQC(UserConfig->irqc);
		//Config NVIC for PORTA
		if(UserConfig->PORTx == PORTA)
		{
			PORTA_CallBack = UserConfig->CallBack;
			NVIC->ISER[0] = (1 << 30);
		}
		else if((UserConfig->PORTx == PORTC) ||(UserConfig->PORTx == PORTD))//Config NVIC for PORTC,D
		{
			PORTCD_CallBack = UserConfig->CallBack;
			NVIC->ISER[0] = (1 << 31);
		}
	}
}

//Handle interrupt
void PORTC_PORTD_IRQHandler(void)
{
	for(int i = 0; i < 32; i++)
	{
		if (PORTC->ISFR & (1 << i))
		{
			PORTCD_CallBack(i);
			PORT_EXTI_ClearFlag(PORTC, i);//Clear flag
		}
		if (PORTD->ISFR & (1 << i))
		{
			PORTCD_CallBack(i);
			PORT_EXTI_ClearFlag(PORTD, i);//Clear flag
		}
	}
}
void PORTA_IRQHandler(void)
{
	for(int i = 0; i < 32; i++)
	{
		if (PORTA->ISFR & (1 << i))
		{
			PORTA_CallBack(i);
			PORT_EXTI_ClearFlag(PORTA, i); //Clear flag
		}
	}
}

