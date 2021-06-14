#ifndef SIGNALGENERATOR_H_
#define SIGNALGENERATOR_H_

#include <stdint.h>
#include <stdio.h>
#include "Timer.h"

#define DEFAULT_OCR 9999 //Implica que DefaultFrec = 100 

void SIGNALGENERATOR_ChangeFrec(uint16_t NewFrec);
void SIGNALGENERATOR_OFF();
void SIGNALGENERATOR_ON();
void SIGNALGENERATOR_RST();
void SIGNALGENERATOR_Init();



#endif /* SIGNALGENERATOR_H_ */