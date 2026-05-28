#include "stm32l476xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "motor.h"
#include "UART.h"

void readSteps(char* steps, char* unfiltered);
void scanCube(void);
void sendCube(USART_TypeDef *USARTx, char* buffer);
void filterSteps(char* input, char*output);


void sendCube(USART_TypeDef *USARTx, char* buffer){
	//check if esp is ready
	puttyWrite("waiting for ESP ready\n");
	ack(USARTx);
//	ackd(USARTx);
	puttyWrite("ESP ready!\n");
	ESP_Write(USARTx, buffer, 57);
	puttyWrite("done writing. waiting to receive");
}


void filterSteps(char* input, char* output){
	for (int i = 0, j = 0; i < 150; i++){
		puttyWrite(&input[i]);
		puttyWrite("\n");
		if(input[i] == ')') return;
		if(!(input[i] == 'A')){
			output[j++] = input[i];
	}
	}
}

void readSteps(char* steps, char* unfiltered){
		filterSteps(unfiltered, steps);\
	int firstQuote = 0;
    char buffer[3] = "--";
	for(unsigned int i = 0, j = 0; i < strlen(steps); i++) {
		if((steps[i] == 'A' || steps[i] == '"' || steps[i] == ')')){
			if(firstQuote == 0 && steps[i] == '"')
			{
				firstQuote = 1;
				continue;
			}
			else if(firstQuote == 1 && steps[i] == '"'){
				
			}
			else{
				continue;
			}
			
		}
		if(i == strlen(steps) - 1) { // Since it only rotates the motor if it sees a ' ', if the string doesn't end in a space it wont make the final move
			buffer[j] = '\0';
			rotateMotor(buffer);
		}
		if(steps[i] == ' ') {
			buffer[j] = '\0';
			rotateMotor(buffer);
			j=0;
		} else {
			buffer[j++] = steps[i];
		}
		
	}
}


void scanCube(void){
/*
YELLOW = UP
RED = FRONT
GREEN = RIGHT
BLUE = LEFT
ORANGE = BACK
WHITE = DOWN

             +------------+
             | U1  U2  U3 |
             |            |
             | U4  U5  U6 |
             |            |
             | U7  U8  U9 |
+------------+------------+------------+------------+
| 41  L2  L3 | 21  22  23 | 10  11  12 | 51  B2  B3 |
|            |            |            |            |
| L4  L5  L6 | 24  25  26 | 14  15  16 | B4  B5  B6 |
|            |            |            |            |
| L7  L8  L9 | 27  28  29 | 17  18  19 | B7  B8  B9 |
+------------+------------+------------+------------+
             | 31  D2  D3 |
             |            |
             | D4  D5  D6 |
             |            |
             | D7  D8  D9 |
             +------------+

YYYBYYBYWOOGGGBYRGOGBRRRWOBGGRWWWRWRGOYRBBBOOOBRWOYWGW
*/

}
