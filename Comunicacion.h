/*
 * Comunicacion.h
 *
 * Created: 14/6/2021 14:09:01
 *  Author: Lucas
 */ 


#ifndef COMUNICACION_H_
#define COMUNICACION_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "SignalGenerator.h"
#include "SerialPort.h"


#define F_MIN 100				//Mínima frecuencia admitida
#define F_MAX 10000				//Máxima frecuencia admitida

void Comunicacion_Inicializar(uint8_t baudrate);
void Comunicacion_Enviar_mensaje(char * msg);
void Comunicacion_Recibir_comando(void);

#endif /* COMUNICACION_H_ */