#ifndef TIMER_H_
#define TIMER_H_
#include <avr/io.h>
#include <stdio.h>

void TIMER1_Init(uint16_t Initial_OCR1A);
void TIMER1_ChangeTOP(uint16_t New_OCR1A);
void TIMER1_ON();
void TIMER1_OFF();



#endif /* TIMER_H_ */