#include "stm32l476xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "motor.h"

void readSteps(char* steps, char* unfiltered);
void scanCube(void);
void sendCube(USART_TypeDef *USARTx, char* buffer);
void filterSteps(char* input, char*output);