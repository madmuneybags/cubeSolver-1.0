#include "stm32l476xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void USART_Write (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes);
void ESP_Write (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes);
void USART_Read (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes);
void ESP_Read (USART_TypeDef *USARTx, char *buffer, uint32_t nBytes);
void UART_Init(USART_TypeDef *USARTx);
void ack(USART_TypeDef *USARTx);
void ackd(USART_TypeDef *USARTx);
void USART_Ack (USART_TypeDef *USARTx, char buffer);
void UART2_init(void);
void puttyWrite(char* buffer);