
#include "UART.h"
#include "stdio.h"
/**
 * @file    UART.c
 * @brief   Application entry point.
 */


UART0_IRQHandlerCallback UART0_Callback = NULL;

void UART_Init(PORT_Config_t *pin_TX, PORT_Config_t *pin_RX, UART0_IRQHandlerCallback uartAddrCallF)
{
	uint16_t SBR_temp;
	// Clock for UART0
	SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(0b11);		//MCGIRCLK clock

	MCG->C2 |= MCG_C2_IRCS(1);		//FAST CLCOK
	MCG->SC = (MCG->SC & ~MCG_SC_FCRDIV_MASK) | MCG_SC_FCRDIV(0);
	MCG->C1 |= MCG_C1_IRCLKEN(1);	//ENABLE INTERNAL CLOCK

	//Clock for UART
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;

	// Port:Clock Port, TXpin RxPin - MUX = UART, Enable pull_up
	CLOCK_PortInit(pin_TX->PORTx);
	CLOCK_PortInit(pin_RX->PORTx);
	PORT_Pin_Init(pin_TX);
	PORT_Pin_Init(pin_RX);

	// Baud rate (Clock P 2 divider)
	UART0->C2 &= ~UART0_C2_TE_MASK; // transmitter and receiver are both disabled
	UART0->C2 &= ~UART0_C2_RE_MASK;

	//ConfigOSR
	UART0->C4 = (UART0->C4 & ~UART0_C4_OSR_MASK) | UART0_C4_OSR(15);

	//Baud rate for TX and Rx
	SBR_temp = 4000000/(9600*16); 	//OSR select = 16:
	UART0->BDH = (UART0->BDH & ~UART0_BDH_SBR_MASK) | (SBR_temp >> 8);
	UART0->BDL &= ~UART_BDL_SBR_MASK;
	UART0->BDL |= (uint8_t)SBR_temp;
	//frame
		// Data Length (8/9/10) - 8
		UART0->C1 &= ~UART0_C1_M_MASK;		//8bit mode

		// Parity (None / Odd / Even) — None
		UART0->C1 &= ~UART0_C1_PE_MASK;

		// Number of Stop Bits (1/2) — 1
		UART0->BDH &= ~UART0_BDH_SBNS_MASK;

		// Other(KLSB First, Invert, Loopback, ...)
	//Enable Receiver (RE)
	UART0->C2 |= UART0_C2_RE_MASK;
	//Enable Receiver interrupt
	UART0->C2 |= UART0_C2_RIE_MASK;
	//Enable NVIC for UART0;
	NVIC->ISER[0] = (1 << 12);
	UART0_Callback = uartAddrCallF;  //Call back function
}

void UART_SendChar(char ch)
{
	//Enable Transmitter (TE)
	UART0->C2 |= UART0_C2_TE_MASK;
	//Wait TDRE = 1;
	while((UART0->S1 & UART0_S1_TDRE_MASK) == 0);
	//RxBuffer = ch;
	UART0->D = ch;
	//Wait TC = 1;
	while((UART0->S1 & UART0_S1_TC_MASK) == 0);
	//Disable Transmitter (TE)
	UART0->C2 &= ~UART0_C2_TE_MASK;
}

void UART_SendString(char *str, uint8_t length)
{
	uint8_t idx;
	//Enable Transmitter (TE)
	UART0->C2 |= UART0_C2_TE_MASK;
	for(idx = 0; idx < length; idx++)
	{
		//Wait TDRE = 1;
		while((UART0->S1 & UART0_S1_TDRE_MASK) == 0);
		// RxBuffer = str[idx];
		UART0->D = str[idx];
	}
	//Wait TC = 1;
	while((UART0->S1 & UART0_S1_TC_MASK) == 0);
	//Disable Transmitter (TE)
	UART0->C2 &= ~UART0_C2_TE_MASK;
}

uint8_t UART_RecverPoll()
{
	uint8_t databuff;
	//Enable Receiver (RE)
	UART0->C2 |= UART0_C2_RE_MASK;
	//Wait RDRF = 1;
	while((UART0->S1 & UART0_S1_RDRF_MASK) == 0);
	//read data
	databuff = UART0->D;
	//Disable Receiver (RE)
	UART0->C2 &= ~UART0_C2_TE_MASK;
	return databuff;
}

uint8_t UART_DataReceive()
{
	uint8_t Data = UART0->D;
	return Data;
}

void UART0_IRQHandler(void)
{
	//Receive interrupt
	if(UART0->S1 & UART0_S1_RDRF_MASK)
	{
		UART0_Callback();
	}
}
