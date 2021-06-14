#include "Timer.h"

/************************************************************************/
/* Configuración inicial del timer. Activo la salida correspondiente al 
canal A (OC1A), utilizo modo CTC con TOP= OCR1A. El parámetro recibido es 
el valor a colocar en el registro de comparación OCR1A con el que iniciará 
el periférico															*/
/************************************************************************/
void TIMER1_Init(uint16_t Initial_OCR1A){
	DDRB = (1<<PB1);					//Pin PB1 será la salida que se actualiza según COM1A1 y COM1A0
	TCCR1A = (1<<COM1A0);				//Compare Out Mode COM1A = Toggle
	TCCR1B = 1<<WGM12;					//Modo CTC
	OCR1A = Initial_OCR1A;				//Seteo valor de comparación para obtener frecuencia de salida por defecto
}

/************************************************************************/
/* Parámetro indica el nuevo valor para el registro de comparación
OCR1A, representando una nueva frecuencia de actualización para OC1A    */
/************************************************************************/
void TIMER1_ChangeTOP(uint16_t New_OCR1A){
	OCR1A = New_OCR1A;
}

/************************************************************************/
/* Selecciona la fuente de reloj y el preescalador utilizado. 
Al finalizar esta función el Timer ya está funcionando					*/
/************************************************************************/
void TIMER1_ON(){
	TCCR1B |= 1<<CS11;					//Habilito reloj de CPU con preescalador por 8 (N=8)
}

/************************************************************************/
/* No se selecciona ninguna fuente de reloj por lo que el Timer se apaga*/
/************************************************************************/
void TIMER1_OFF(){
	TCCR1B &= ~(1<<CS11);				//Deshabilito reloj de CPU
}