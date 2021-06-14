/*
 * comunicacion.c
 *
 * Created: 14/6/2021 14:08:27
 *  Author: Lucas
 */ 
#include "Comunicacion.h"

extern volatile int comando_invalido;
extern char RX_Buffer[6];				
extern char TX_Buffer[117];
char msgON[] = "COMANDO ON\n\r";
char msgOFF[] = "COMANDO OFF\n\r";
char msgFREC[] = "COMANDO FRECUENCIA\n\r";
char msgMENU[] = "\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\rIngrese una frecuencia entre 100 y 10000\n\rON: Encender\n\rApagar\n\rRST:Reiniciar\n\r";


/************************************************************************/
/* FUNCION PARA INICIALIZAR LA COMUNICACIÓN. INICIALIZA LA UART CON EL 
BAUDRATE, ACTIVA AL TRANSMISOR Y AL RECEPTOR DEL PUERTO SERIE. 
HABILITA INTERRUPCION POR RECEPCION E INTERRUPCIONES GLOBALES.			*/
/************************************************************************/
void Comunicacion_Inicializar(uint8_t baudrate){
	SerialPort_Init(baudrate); 			//baudrate=103 (9600bps@16MHz)	
	SerialPort_TX_Enable();				
	SerialPort_RX_Enable();				
	SerialPort_RX_Interrupt_Enable();	
	sei();								
}


/************************************************************************/
/* FUNCION PRODUCTORA PARA LA TRANSMISIÓN SERIE DE UN MENSAJE.
COPIA EN TX_BUFFER LOS CARACTERES DE LA CADENA msg. ESCRIBE HASTA EL 
CARACTER FIN DE CADENA INCLUSIVE. HABILITA LA INTERRUPCION PARA TRANSMITIR*/
/************************************************************************/
void Comunicacion_Enviar_mensaje(char * msg){
	uint8_t i = 0;
	
	do{
		TX_Buffer[i]=msg[i];
	}while(msg[i++]);					//CARACER FIN DE CADENA '\0' = 0x00		
	SerialPort_TX_Interrupt_Enable();
}


/************************************************************************/
/* FUNCION CONSUMIDORA PARA LA RECEPCION QUE PROCESA LA CADENA DE CARACTERES
 EN EL ARRAY RX_Buffer. SEGUN EL COMANDO INGRESADO, SE TRANSMITIRA EL 
 MENSAJE CORRESPONDIENTE Y REALIZARÁ LA TAREA DE GENERACION CORRESPONDIENTE. 
 SI NO ES UN COMANDO VALIDO, ACTIVA EL FLAG comando_invalido			*/                                                                 
/************************************************************************/
void Comunicacion_Recibir_comando(){
	int  decod_index,num;
	
	if (strcmp(RX_Buffer,"RST") == 0)					//INGRESÓ COMANDO RST
	{
		Comunicacion_Enviar_mensaje(msgMENU);
		SIGNALGENERATOR_RST();
	}
	else{
		if (strcmp(RX_Buffer,"ON") == 0)				//INGRESÓ COMANDO ON
		{
			Comunicacion_Enviar_mensaje(msgON);
			SIGNALGENERATOR_ON();
		}
		else{
			if (strcmp(RX_Buffer,"OFF") == 0)			//INGRESÓ COMANDO OFF
			{
				Comunicacion_Enviar_mensaje(msgOFF);
				SIGNALGENERATOR_OFF();
			}
			else{
				decod_index=0;				
				//CORROBORO QUE LOS CARACTERES SEAN TODOS DIGITOS
				while (RX_Buffer[decod_index]!='\0' && comando_invalido==0){
					if (RX_Buffer[decod_index] >= '0' && RX_Buffer[decod_index] <= '9')
					{
						decod_index++;
					}
					else{
						comando_invalido=1;
					}
				}
				if (comando_invalido==0){
					num=atoi(RX_Buffer);
					if (num>=F_MIN && num<=F_MAX){		//INGRESÓ COMANDO FRECUENCIA VALIDA
						Comunicacion_Enviar_mensaje(msgFREC);
						SIGNALGENERATOR_ChangeFrec(num);
					}
					else{
						comando_invalido=1;
					}
				}
			}
		}
	}
}