#include "stm32l476xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "UART.h"
#include "cube.h"
#include "motor.h"





int main(){
	
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY)==0);
	RCC->CFGR |= RCC_CFGR_SW_HSI;

	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	UART2_init();
	UART_Init(USART1);
	
	// Init ADC
	
	initMotors();
	
	char test[] = "RWYGYBBOGRYOOGGOYRWWYRRGBRYYYGWWOOBWWRORBWGBRBGBYOBGOW";
	sendCube(USART1, test);
	ackd(USART1);
	char unfiltered[150];
	char steps[150];
	USART_Read(USART1, unfiltered, 150);
	readSteps(steps, unfiltered);
	USART_Write(USART2, steps, strlen(steps));

	return 0;
}




