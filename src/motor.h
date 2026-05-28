#ifndef MOTOR_H
#define MOTOR_H
void initMotors(void);
void rotateMotor(char* step);
void delay(unsigned int m);
void turn90(int direction, int motor);
void turn180(int direction, int motor);
#endif
