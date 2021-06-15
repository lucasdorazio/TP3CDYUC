/*
 * SerialPort.h
 *
 * Created: 7/6/2021 17:01:27
 *  Author: Lucas
 */ 


#ifndef SERIALPORT_H_
#define SERIALPORT_H_
	#include <avr/io.h>
	
	//Inclusi�n de librerias publicas
	#include <avr/interrupt.h>
	
	//Definici�n de constantes 
	#define RX_BUFFER_LENGTH 6						//Tama�o del buffer para 5 caracteres + '\0'
	#define TX_BUFFER_LENGTH 117					//Tama�o de la cadena m�s larga a transmitir
	
	
	// -------- Prototipos de funciones Publicas ---------------
	
	// Inicializacion de Puerto Serie
	void SerialPort_Init(uint8_t);					//recibe un baudrate

	// Congifuraci�n de Transmisor
	void SerialPort_TX_Enable(void);
	void SerialPort_TX_Interrupt_Enable(void);
	void SerialPort_TX_Interrupt_Disable(void);
	
	// Configuraci�n de Receptor
	void SerialPort_RX_Enable(void);
	void SerialPort_RX_Interrupt_Enable(void);
	

#endif /* SERIALPORT_H_ */