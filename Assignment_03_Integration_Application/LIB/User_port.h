#ifndef _USER_PORT_H_
#define _USER_PORT_H_

#include "MKL46Z4.h"
#include "stdint.h"
#include "stdio.h"

typedef void (*CallBackType)(uint8_t );

//PORT Pin Initialize
typedef enum
{
	PORT_PULL_DISABLE = 0,
	PORT_PULL_DOWN = 2U, //010
	PORT_PULL_UP = 3U //011
}PORT_PULL_t;

typedef enum
{
	PORT_MUX_DISABLE_OR_ANALOG 	= 0U,
	PORT_MUX_GPIO				= 1U,
	PORT_MUX_ALTERNATIVE2		= 2U,
	PORT_MUX_ALTERNATIVE3		= 3U,
	PORT_MUX_ALTERNATIVE4		= 4U,
	PORT_MUX_ALTERNATIVE5		= 5U,
	PORT_MUX_ALTERNATIVE6		= 6U,
	PORT_MUX_ALTERNATIVE7		= 7U
}PORT_MUX_t;

typedef enum
{
	PORT_INTERRUPT_DISABLE 					= 0U,
	PORT_INTERRUPT_ON_WHEN_LOGIC_ZERO 		= (0b1000),
	PORT_INTERRUPT_ON_RISING_EDGE 			= (0b1001),
	PORT_INTERRUPT_ON_FALLING_EDGE 			= (0b1010),
	PORT_INTERRUPT_ON_WHEN_EITHER_EDGE 		= (0b1011),
	PORT_INTERRUPT_ON_WHEN_LOGIC_ONE 		= (0b1100)
}PORT_IRQC_t;


typedef struct
{
	PORT_Type *PORTx;
	uint8_t PIN;
	PORT_MUX_t	 mux;
	PORT_PULL_t	 pull;
	PORT_IRQC_t	 irqc;
	CallBackType CallBack;
}PORT_Config_t;


void PORT_Pin_Init(PORT_Config_t *UserConfig);
void PORT_EXTI_Config(PORT_Config_t *UserConfig);
static inline void PORT_EXTI_ClearFlag(PORT_Type *PORTx, uint8_t PIN)
{
	PORTx->PCR[PIN] |= (1 << 24);
}

#endif
