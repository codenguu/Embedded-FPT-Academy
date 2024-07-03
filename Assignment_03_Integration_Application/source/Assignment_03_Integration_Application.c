/**
 * @file    Assignment_03_Integration_Application.c
 */
#include "MKL46Z4.h"
#include "stdio.h"
#include "ADC.h"
#include "User_port.h"
#include "User_gpio.h"
#include "UART.h"
#include "PIT.h"
#include "Middleware.h"

/*DEFINE*/


/*PROTOTYPE*/
void ADC_ISR_handle();
void PIT_ISR_handle();
void UART0_ISR_Recievehandle();
void BTN_ISR_handle(uint8_t pin);

static void LED_Config();
static void ADC0_Config();
static void UART0_Config();
static void BTN_Config();
void SendDatatoPC();;


/*========GREEN LED=========*/
PORT_Config_t PortGreenLed;
GPIO_Config_Type GpioGreenLed;

/*=========RED LED===========*/
PORT_Config_t PortRedLed;
GPIO_Config_Type GpioRedLed;

/*========BUTTON=========*/
PORT_Config_t PortSW2;
GPIO_Config_Type GpioSW2;
/*=========ADC LIGHSS===========*/
ADC_Config_t adcconfig_LightSNS;

/*==========CONFIG PORT UART TO PC=========*/
PORT_Config_t Pin_uart0_Rx;
PORT_Config_t Pin_uart0_Tx;


/*Value ADC*/
uint16_t valueADC;
typedef union
{
	float floatData;
	uint8_t Data[4];
}float_convert_type;

float_convert_type vontage;

/*Data Receive*/
uint8_t Data_Rx;

/*STATE */
typedef enum
{
	PIT_ON = 0U,
	PIT_OFF = 1
}State_PIT_t;

State_PIT_t statePIT = PIT_ON;

int main(void) {
	//Initialize LED
	LED_Config();

	//Initialize BUTTON
	BTN_Config();

	//Initialize ADC
	ADC0_Config();

	//Initialize UART0
	UART0_Config();

	//Initialize PIT
	PIT_init_ms(500);
	PIT_Interrupt_En(&PIT_ISR_handle);


	while(1)
	{
		switch(Data_Rx)
		{
			case 'C':
				if(statePIT == PIT_OFF)
				{
					SendDatatoPC();
				}
				else
				{
					UART_SendString("Disabled Convert!", 17);
				}
				Data_Rx = 0;
				break;
			case 'D':
				switch(statePIT)
				{
					case PIT_ON:
						statePIT = PIT_OFF;
						PIT_StartTimer();
						UART_SendString("Enable Convert: ", 16);
						Data_Rx = 0;
						break;
					case PIT_OFF:
						statePIT = PIT_ON;
						PIT_DisableTimer();
						UART_SendString("Disable Convert: ", 17);
						break;
				}
				Data_Rx = 0;
				break;
			default:
				if(valueADC < 55000)
				{
					LED_OFF(&GpioRedLed);
				}
				else
				{
					LED_ON(&GpioRedLed);
				}
		}
	}
    return 0 ;
}

/*HANDLE DATA ANALOG*/
void SendDatatoPC()
{
	vontage.floatData = (float)(65535 - valueADC)/65535 * 3.3;	//V
	UART_SendString("voltage: ", 9);
	UART_SendString(vontage.Data, 4);
	UART_SendChar(0xA);
}

/*HANDLE INTERRUPT*/
void UART0_ISR_Recievehandle()
{
	Data_Rx = UART_DataReceive();
}
void ADC_ISR_handle()
{
	valueADC = ADC_ReadDigital();
	Data_Rx = 'C';
}
void PIT_ISR_handle()
{
	LED_TogglePin(&GpioGreenLed);
}
void BTN_ISR_handle(uint8_t pin)
{
	if(pin == 12)
	{
		Data_Rx = 'D';
	}
}
/*****END****/
/*
 * Initialization Function
 */
static void LED_Config()
{
	//LED Green
	PortGreenLed.PORTx = PORTD;
	PortGreenLed.PIN = 5;
	PortGreenLed.mux = PORT_MUX_GPIO;
	GpioGreenLed.GPIOx = GPIOD;
	GpioGreenLed.PIN = 5;
	GpioGreenLed.pddr = GPIO_OUTPUT;
	LED_Init(&PortGreenLed, &GpioGreenLed);
	//LED Red
	PortRedLed.PORTx = PORTE;
	PortRedLed.PIN = 29;
	PortRedLed.mux = PORT_MUX_GPIO;
	GpioRedLed.GPIOx = GPIOE;
	GpioRedLed.PIN = 29;
	GpioRedLed.pddr = GPIO_OUTPUT;
	LED_Init(&PortRedLed, &GpioRedLed);
}
static void ADC0_Config()
{
	adcconfig_LightSNS.PORTx = PORTE;
	adcconfig_LightSNS.PIN = 22;
	adcconfig_LightSNS.trigger = ADC_TRIGGER_HW;
	adcconfig_LightSNS.channel = ADC_CHANNEL_DADP3;
	adcconfig_LightSNS.bit_mode = ADC_16BIT_CONVERTION;
	adcconfig_LightSNS.output_mode = ADC_SINGLE_END;
	adcconfig_LightSNS.adcCallfunc = &ADC_ISR_handle;
	ADC_Init(&adcconfig_LightSNS);
	ADC_ReadInterrupt(&adcconfig_LightSNS);
}
static void UART0_Config()
{
	Pin_uart0_Rx.PORTx = PORTA;
	Pin_uart0_Rx.PIN = 1;
	Pin_uart0_Rx.mux = PORT_MUX_ALTERNATIVE2;	//UART_RX.
	Pin_uart0_Rx.pull = PORT_PULL_UP;

	Pin_uart0_Tx.PORTx = PORTA;
	Pin_uart0_Tx.PIN = 2;
	Pin_uart0_Tx.mux = PORT_MUX_ALTERNATIVE2;	//UART_TX.
	Pin_uart0_Tx.pull = PORT_PULL_UP;
	UART_Init(&Pin_uart0_Tx, &Pin_uart0_Rx, &UART0_ISR_Recievehandle);
}
static void BTN_Config()
{
	//SW2
	PortSW2.PORTx = PORTC;
	PortSW2.PIN = 12;
	PortSW2.mux = PORT_MUX_GPIO;
	PortSW2.pull = PORT_PULL_UP;
	PortSW2.irqc = PORT_INTERRUPT_ON_FALLING_EDGE;
	PortSW2.CallBack = BTN_ISR_handle;

	GpioSW2.GPIOx = GPIOC;
	GpioSW2.PIN = 12;
	GpioSW2.pddr = GPIO_INPUT;
	BTN_Init(&PortSW2, &GpioSW2);
}
