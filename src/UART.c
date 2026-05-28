#include "stm32l476xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void USART_Write (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes);
void ESP_Write (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes);
void USART_Read (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes);
void UART_Init(USART_TypeDef *USARTx);
void ack(USART_TypeDef *USARTx);
void USART_Ack (USART_TypeDef *USARTx, char buffer);
void UART2_init(void);
void puttyWrite(char* buffer);
void ackd(USART_TypeDef *USARTx);
void ESP_Read (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes);


void UART_Init(USART_TypeDef *USARTx){
	
	
	//GPIOA UART1 INIT

	GPIOA->MODER &= 0xFF28FFFF;
	GPIOA->MODER |= 0x00280000;
	
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL9_0 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_2;
	GPIOA->AFR[1] |= GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2;
	
	// Configure PA11 as USART1_CTS, PA12 as USART1_RTS
//	GPIOA->MODER &= ~(GPIO_MODER_MODE11 | GPIO_MODER_MODE12);
//	GPIOA->MODER |= (GPIO_MODER_MODE11_1 | GPIO_MODER_MODE12_1);  // Set to AF mode
	
	// Set Alternate Function (AF7 for PA11 AND 12)
//GPIOA->AFR[1] |= GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2;
//GPIOA->AFR[1] |= GPIO_AFRH_AFSEL11_0 | GPIO_AFRH_AFSEL11_1 | GPIO_AFRH_AFSEL11_2;
	
	GPIOA->OSPEEDR |= 0x003C0000; // High speed PA9/PA10
	
	GPIOA->PUPDR |= 0x00280000; // Pull DOWN
	GPIOA->PUPDR &= 0xFF28FFFF;
	
	GPIOA->OTYPER &= 0xFFFFFFF3; // Push Pull
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	
	RCC->CCIPR &= ~(RCC_CCIPR_USART1SEL); // Sys clock
	RCC->CCIPR |= RCC_CCIPR_USART1SEL_0;
	
	
	USARTx->CR1 &= ~USART_CR1_UE;			//Disable uart
	USARTx->CR1 &= ~USART_CR1_M;			//set data bits
	USARTx->CR2 &= ~USART_CR2_STOP;		//set  STOP BITS
	USARTx->CR1 &= ~USART_CR1_PCE;		//disable parity control
	USARTx->CR1 &= ~USART_CR1_OVER8;	// set oversampling by 16
	USARTx->BRR = 0x683;							//BAUD = 9600
	//USART1->CR3 |= (USART_CR3_RTSE | USART_CR3_CTSE);		//enable hardwar flow control
	USARTx->CR1 |= USART_CR1_TE | USART_CR1_RE; // Trans/Rec enable
	USARTx->CR1 |= USART_CR1_UE;
	while((USARTx->ISR & USART_ISR_TEACK) == 0); // Ready for transmission
	while((USARTx->ISR & USART_ISR_REACK) == 0); // Ready for reception	
}

void UART2_init(void){
	GPIOA->MODER &= 0xFFFFFFAF; // PA2, PA3 Alt function
	GPIOA->MODER |= 0x000000A0;
	
	GPIOA->AFR[0] &= 0xFFFFF00F;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL2_0 | GPIO_AFRL_AFSEL2_1 | GPIO_AFRL_AFSEL2_2;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL3_0 | GPIO_AFRL_AFSEL3_1 | GPIO_AFRL_AFSEL3_2;
	
	GPIOA->OSPEEDR |= 0x000000F0; // High speed PA2/PA3
	
	GPIOA->PUPDR |= 0x00000050; // Pull up
	GPIOA->PUPDR &= 0xFFFFFF5F;
	
	GPIOA->OTYPER &= 0xFFFFFFF3; // Push Pull
	
	RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN; // Enable clock for USART2
	
	RCC->CCIPR &= ~(RCC_CCIPR_USART2SEL); // Sys clock
	RCC->CCIPR |= RCC_CCIPR_USART2SEL_0;
	
	// Init USART2
	USART2->CR1 &= ~USART_CR1_UE;			//Disable uart
	USART2->CR1 &= ~USART_CR1_M;			//set data bits
	USART2->CR2 &= ~USART_CR2_STOP;		//set  STOP BITS
	USART2->CR1 &= ~USART_CR1_PCE;		//disable parity control
	USART2->CR1 &= ~USART_CR1_OVER8;	// set oversampling by 16
	//USART2->BRR = 0x208D; 						// Baud 9600
	USART2->BRR = 0x683;
	USART2->CR1 |= USART_CR1_TE | USART_CR1_RE; // Trans/Rec enable
	USART2->CR1 |= USART_CR1_UE;
	while((USART2->ISR & USART_ISR_TEACK) == 0); // Ready for transmission
	while((USART2->ISR & USART_ISR_REACK) == 0); // Ready for reception
	
}

void USART_Write (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes){
	uint32_t i;
		
	for (i = 0; i < nBytes; i++){
		while(!(USARTx->ISR & USART_ISR_TXE)); //Wait
		USARTx->TDR = buffer[i];
	}
	
	// Wait
	while(!(USARTx->ISR & USART_ISR_TC));
	
	// Clear Flag
	USARTx->ICR |= USART_ICR_TCCF;
}

void ESP_Write (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes){
	uint32_t i;
		
	for (i = 0; i < nBytes; i++){

		while(!(USARTx->ISR & USART_ISR_TXE)); //Wait
		USARTx->TDR = buffer[i];
	}
	// Wait
	while(!(USARTx->ISR & USART_ISR_TC));
	
	// Clear Flag
	USARTx->ICR |= USART_ICR_TCCF;
	ackd(USART1);
}



void USART_Read (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes) {
	uint32_t i;
	//while ((USART1->ISR & USART_ISR_RXNE) != 0) {  // Check if RDR contains data
 //   volatile uint8_t temp = (uint8_t)(USART1->RDR);  // Read to clear
//}
	for (i = 0; i < nBytes; i++){
		while(!(USARTx->ISR & USART_ISR_RXNE)); //Wait
		buffer[i] = USARTx->RDR;
		puttyWrite(&buffer[i]);
		ack(USARTx);
		if (buffer[i] == ')') return;
	}
}

void ESP_Read (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes) {
	uint32_t i;
	for (int j = 0; j < 56; j++){
		while(!(USARTx->ISR & USART_ISR_RXNE)); //Wait
		buffer[j] = USARTx->RDR;
}
	for (i = 0; i < nBytes; i++){
		while(!(USARTx->ISR & USART_ISR_RXNE)); //Wait
		buffer[i] = USARTx->RDR;
		ack(USARTx);
		if (buffer[i] == ')') return;
	}
}



void ack(USART_TypeDef *USARTx){
	volatile char p = 'A';
	USART_Ack(USARTx, p);
}

void USART_Ack (USART_TypeDef *USARTx, char buffer){
		
		while(!(USARTx->ISR & USART_ISR_TXE)); //Wait
		USARTx->TDR = buffer;
	
	// Wait
	while(!(USARTx->ISR & USART_ISR_TC));
	
	// Clear Flag
	USARTx->ICR |= USART_ICR_TCCF;
}

void ackd(USART_TypeDef *USARTx){
	char buffer[] = "b";
	USART_Read(USARTx, buffer, 2);
	if(buffer[0] == 'A'){
		return;
	}else{
		puttyWrite("FAILED acknowledge\n");
	}
}

void puttyWrite(char* buffer){
	USART_Write(USART2, buffer, strlen(buffer) + 1); 
}
