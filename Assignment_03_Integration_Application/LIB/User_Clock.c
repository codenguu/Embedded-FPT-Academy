/*
 * User_Clock.c
 *
 *  Created on: Jun 14, 2024
 *      Author: SF
 */
#include "User_Clock.h"

//Initialize Clock for port
void CLOCK_PortInit(PORT_Type *PORTx)
{
    if (PORTx == PORTA)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
    }
    else if (PORTx == PORTB)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    }
    else if (PORTx == PORTC)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
    }
    else if (PORTx == PORTD)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
    }
    else if (PORTx == PORTE)
    {
        SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
    }
    else {
        // Invalid port
    }
}


