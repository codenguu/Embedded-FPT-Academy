/*
 * UART.h
 *
 *  Created on: Jun 29, 2024
 *      Author: SF
 */

#ifndef UART_H_
#define UART_H_

#include "MKL46Z4.h"
#include "User_port.h"
#include "User_Clock.h"

typedef void (*UART0_IRQHandlerCallback)();

void UART_Init(PORT_Config_t *pin_TX, PORT_Config_t *pin_RX, UART0_IRQHandlerCallback uartAddrCallF);
void UART_SendChar(char ch);
void UART_SendString(char *str, uint8_t length);
void UART_RecverInterrupt();
uint8_t UART_RecverPoll();
uint8_t UART_DataReceive();


#endif /* UART_H_ */
