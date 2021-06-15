/*
 * Comunicacion.h
 *
 * Created: 14/6/2021 14:09:01
 *  Author: Lucas
 */ 


#ifndef COMUNICACION_H_
#define COMUNICACION_H_

//Inclusi�n de librerias publicas
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "SignalGenerator.h"
#include "SerialPort.h"

//Definici�n de constantes 
#define F_MIN 100				//M�nima frecuencia admitida
#define F_MAX 10000				//M�xima frecuencia admitida

// -------- Prototipos de funciones Publicas ---------------

//Inicializaci�n del modulo de comunicaci�n
void Comunicacion_Inicializar(uint8_t baudrate);
//Envio de mensaje
void Comunicacion_Enviar_mensaje(char * msg);
//Recepci�n y procesamiento de comando
void Comunicacion_Recibir_comando(void);

#endif /* COMUNICACION_H_ */