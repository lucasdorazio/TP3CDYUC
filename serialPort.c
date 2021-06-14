/*
 * serialPort.c
 *
 * Created: 7/6/2021 17:01:12
 *  Author: Lucas
 */ 
#include "SerialPort.h"
/************************************************************************/
/* LAS FUNCIONES DE ESTE ARCHIVO POSEEN DEPENDENCIAS CON EL HARDWARE	*/
/************************************************************************/

extern volatile int fin_comando, comando_invalido;
extern char RX_Buffer[6];
extern int TX_Buffer[117];


/************************************************************************/
/* FUNCION DE INICIALIZACION DE LA UART.CONFIGURA EL BIT DE ESTADO U2X=0.
 CONFIGURA EL TAMAÑO DE DATOS EN 8 BITS, SIN PARIDAD Y 1 BIT DE PARADA. 
 ESTABLECE EL BAUDRATE RECIBIDO.										*/
/************************************************************************/
void SerialPort_Init(uint8_t baudrate){		
	UCSR0A = 0;								
	UCSR0B = 0;								
	UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);		
	UBRR0L = (unsigned char)baudrate;		//baudrate=103 (9600bps@16MHz)		
}


/************************************************************************/
/* FUNCIONES DE HABILITACIONES DE TRANSMISION Y RECEPCIÓN               */                                            
/************************************************************************/
void SerialPort_TX_Enable(void){
	UCSR0B |= (1<<TXEN0);
}

void SerialPort_RX_Enable(void){
	UCSR0B |= (1<<RXEN0);
}

/************************************************************************/
/* FUNCIONES PARA HABILITAR Y DESHABILITAR INTERRUPCIONES POR
TRANSMISION Y RECEPCION													*/
/************************************************************************/

void SerialPort_TX_Interrupt_Enable(void){
	UCSR0B |= (1<<UDRIE0);
}

void SerialPort_RX_Interrupt_Enable(void){
	UCSR0B |= (1<<RXCIE0);
}

void SerialPort_TX_Interrupt_Disable(void)
{
	UCSR0B &=~(1<<UDRIE0);
}

void SerialPort_RX_Interrupt_Disable(void)
{
	UCSR0B &=~(1<<RXCIE0);
}



/************************************************************************/
/* TAREA DE FOREGROUND. FUNCION PRODUCTORA DE LA RECEPCION. NO BLOQUEANTE
LEE UN DATO DEL REGISTRO UDR Y LO ALMACENA EN EL BUFFER RX_BUFFER.
AL INGRESAR <ENTER>, SE DETERMINA SI EL COMANDO PUEDE SER VALIDO O NO. 
SI PUEDE SERLO ACTIVA EL FLAG fin_comando, DE LO CONTRARIO ACTIVA comando_invalido*/
/************************************************************************/
ISR(USART_RX_vect){
	static int RX_index=0, overflow_buffer=0;
	unsigned char dato = UDR0;				//Leer el UDR borra el flag RXC(condición de interrupción)
	
	if (dato == '\r') {
		if (overflow_buffer){				//El comando es invalido por tener más caracteres que los debidos
			comando_invalido=1;				 
			overflow_buffer=0;
		}
		else{
			RX_Buffer[RX_index]='\0';		//Inserta fin de cadena al final.
			fin_comando = 1;
		}
		RX_index=0;
		} else {
		if (RX_index<BUFFER_LENGTH){		
			RX_Buffer[RX_index++] =  dato;
		}
		else{								
			overflow_buffer = 1;
		}
	}
}

/************************************************************************/
/* TAREA DE FOREGROUND. FUNCION CONSUMIDORA DE LA TRANSMISION. NO BLOQUEANTE
ESCRIBE EN EL REGISTRO UDR LOS CARACTERES ALMACENADOS EN EL BUFFER. AL
ENCONTRAR EL FIN DE CADENA, DESHABILITA LA INTERRUPCIÓN*/
/************************************************************************/
ISR(USART_UDRE_vect){
	static int TX_index=0;
	UDR0 = TX_Buffer[TX_index];
	if (TX_Buffer[TX_index++]=='\0'){
		SerialPort_TX_Interrupt_Disable();
		TX_index=0;
	}	
}