/*
 * signalGenerator.c
 *
 * Created: 7/6/2021 17:03:24
 *  Author: Lucas
 */ 

#include "SignalGenerator.h"

/************************************************************************/
/* Funci�n para cambiar el valor de la frecuencia de salida en OC1A		*/
/* Recibe un par�metro entre F_MIN y F_MAX								*/
/************************************************************************/
void SIGNALGENERATOR_ChangeFrec(uint16_t NewFrec){
	uint16_t OCR= (1000000 / NewFrec ) -1;
	TIMER1_ChangeTOP(OCR);
}

/************************************************************************/
/* Apaga el generador de se�ales: la salida OC1A mantendr� su valor hasta 
  que se vuelva a prender el generador									*/
/************************************************************************/
void SIGNALGENERATOR_OFF(){
	TIMER1_OFF();
}

/*************************************************************************/
/* Enciende el generador de se�ales: el pin OC1A alternar� su valor      
generando una frecuencia de salida seg�n la configurada por el usuario*/
/*************************************************************************/
void SIGNALGENERATOR_ON(){
	TIMER1_ON();
}

/************************************************************************/
/* Resetea el generador, es decir que lo apaga y adem�s setea la 
frecuencia de salida en el valor por defecto							*/
/************************************************************************/
void SIGNALGENERATOR_RST(){
	TIMER1_OFF();
	TIMER1_ChangeTOP(DEFAULT_OCR);
}

/************************************************************************/
/* Configuraci�n inicial del generador. Se encarga de inicializar el 
sistema temporizador utilizado para generar la se�al					*/
/************************************************************************/
void SIGNALGENERATOR_Init(){
	TIMER1_Init(DEFAULT_OCR);
}