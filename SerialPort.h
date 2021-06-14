/*
 * SerialPort.h
 *
 * Created: 7/6/2021 17:01:27
 *  Author: Lucas
 */ 


#ifndef SERIALPORT_H_
#define SERIALPORT_H_
	#include <avr/io.h>
	
	// Interrupciones del Microcontrolador
	#include <avr/interrupt.h>
	
	
	#define BUFFER_LENGTH 6			//Tamaño del buffer para 5 caracteres + '\0'
	
	// -------- Prototipos de funciones Publicas ---------------
	
	// Inicializacion de Puerto Serie
	void SerialPort_Init(uint8_t);					//recibe un boud rate

	// Inicializacion de Transmisor
	void SerialPort_TX_Enable(void);
	void SerialPort_TX_Interrupt_Enable(void);
	void SerialPort_TX_Interrupt_Disable(void);
	
	// Inicializacion de Receptor
	void SerialPort_RX_Enable(void);
	void SerialPort_RX_Interrupt_Enable(void);
	void SerialPort_RX_Interrupt_Disable(void);
	


	//SACAR LAS QUE NO VAN
	void SerialPort_Wait_For_TX_Buffer_Free(void);	// Pooling - Bloqueante hasta que termine de transmitir. Espera UDR vacio (UDRE)
	void SerialPort_Send_Data(char);				// Escribe un char en UDR
	void SerialPort_Send_String(char *);			// Transmision bloqueante (tiene un while)
	void SerialPort_Send_uint8_t(uint8_t);			// Escribe valor entero sin signo en UDR
	void SerialPort_send_int16_t(int val,unsigned int field_length); //This function writes a integer type value to UART





#endif /* SERIALPORT_H_ */