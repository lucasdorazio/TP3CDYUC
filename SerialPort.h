/*
 * SerialPort.h
 *
 * Created: 7/6/2021 17:01:27
 *  Author: Lucas
 */ 


#ifndef SERIALPORT_H_
#define SERIALPORT_H_
	#include <avr/io.h>
	
	//Inclusión de librerias publicas
	#include <avr/interrupt.h>
	
	//Definición de constantes 
	#define RX_BUFFER_LENGTH 6						//Tamaño del buffer para 5 caracteres + '\0'
	#define TX_BUFFER_LENGTH 117					//Tamaño de la cadena más larga a transmitir
	
	
	// -------- Prototipos de funciones Publicas ---------------
	
	// Inicializacion de Puerto Serie
	void SerialPort_Init(uint8_t);					//recibe un baudrate

	// Congifuración de Transmisor
	void SerialPort_TX_Enable(void);
	void SerialPort_TX_Interrupt_Enable(void);
	void SerialPort_TX_Interrupt_Disable(void);
	
	// Configuración de Receptor
	void SerialPort_RX_Enable(void);
	void SerialPort_RX_Interrupt_Enable(void);
	

#endif /* SERIALPORT_H_ */