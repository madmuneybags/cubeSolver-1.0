#include "stm32l476xx.h"
#include "motor.h"
#include <string.h>

void initMotors(){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; // Enable GPIOC clock (keep this though)
	
	GPIOC->MODER &= 0xF3555555; //PC13 User push button input, 0-11 Output for motors
	GPIOC->MODER |= 0x03555555;
}
void delay(unsigned int m){
	volatile unsigned int i,j;
	for(i=0; i<m; i++)
		for(j=0; j<20; j++);
}

void turn90(int direction, int motor){
				if(direction == 0){
					GPIOC->ODR |= 0x00000555; // Set direction 1
				}
				else if(direction == 1){
					GPIOC->ODR &= 0xFFFFFAAA; // Set direction 0
				}
	        // Generate pulses on the Pulse pins
				if(motor == 0){ //D
					for (int i = 0; i < 50; i++) { // 50 steps for 90 degrees
							GPIOC->ODR |= 0x00000002; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFFFD; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 1){ // F
					for (int i = 0; i < 50; i++) { // 50 steps for 90 degrees
							GPIOC->ODR |= 0x00000008; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFFF7; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 2){ // L
					for (int i = 0; i < 50; i++) { // 50 steps for 90 degrees
							GPIOC->ODR |= 0x00000020; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFFDF; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 3){ // B
					for (int i = 0; i < 50; i++) { // 50 steps for 90 degrees
							GPIOC->ODR |= 0x00000080; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFF7F; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 4){ // R
					for (int i = 0; i < 50; i++) { // 50 steps for 90 degrees
							GPIOC->ODR |= 0x00000200; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFDFF; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 5){ // U
					for (int i = 0; i < 50; i++) { // 50 steps for 90 degrees
							GPIOC->ODR |= 0x00000800; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFF7FF; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
}

void turn180(int direction, int motor){
				if(direction == 0){
					GPIOC->ODR |= 0x00000555; // Set direction 1
				}
				else if(direction == 1){
					GPIOC->ODR &= 0xFFFFFAAA; // Set direction 0
				}
	        // Generate pulses on the Pulse pins
				if(motor == 0){ //D
					for (int i = 0; i < 100; i++) {
							GPIOC->ODR |= 0x00000002; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFFFD; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 1){ // F
					for (int i = 0; i < 100; i++) {
							GPIOC->ODR |= 0x00000008; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFFF7; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 2){ // L
					for (int i = 0; i < 100; i++) {
							GPIOC->ODR |= 0x00000020; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFFDF; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 3){ // B
					for (int i = 0; i < 100; i++) {
							GPIOC->ODR |= 0x00000080; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFF7F; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 4){ // R
					for (int i = 0; i < 100; i++) {
							GPIOC->ODR |= 0x00000200; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFFDFF; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
				else if(motor == 5){ // U
					for (int i = 0; i < 100; i++) {
							GPIOC->ODR |= 0x00000800; // Pulse High
							delay(50);             // Adjust delay for step timing
							GPIOC->ODR &= 0xFFFFF7FF; // Pulse Low
							delay(50);             // Adjust delay for step timing
					}
				}
}

void rotateMotor(char* step){
	if(strcmp(step, "D") == 0){
		turn90(0,0);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "F") == 0){
		turn90(0,1);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "L") == 0){
		turn90(0,2);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "B") == 0){
		turn90(0,3);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "R") == 0){
		turn90(0,4);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "U") == 0){
		turn90(0,5);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "D'") == 0){
		turn90(1,0);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "F'") == 0){
		turn90(1,1);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "L'") == 0){
		turn90(1,2);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "B'") == 0){
		turn90(1,3);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "R'") == 0){
		turn90(1,4);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "U'") == 0){
		turn90(1,5);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "D2") == 0){
		turn180(0,0);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "F2") == 0){
		turn180(0,1);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "L2") == 0){
		turn180(0,2);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "B2") == 0){
		turn180(0,3);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "R2") == 0){
		turn180(0,4);
    delay(5000); // Delay before changing direction
	}
	else if(strcmp(step, "U2") == 0){
		turn180(0,5);
    delay(5000); // Delay before changing direction
	}
}

