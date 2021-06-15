/*
 * TP3_GENERADOR_DE_SEÑALES.c
 *
 * Created: 7/6/2021 16:58:41
 * Author : Lucas
 */ 

#include "Main.h"
//Flags para comunicación entre Background y Foreground
volatile uint8_t fin_comando, comando_invalido;	
//Mensajes 
char msgBienvenida[] = "Bienvenido al Generador de Senales\n\rIngrese una frecuencia entre 100 y 10000\n\rON: Encender\n\rApagar\n\rRST:Reiniciar\n\r";
char msgComandoInvalido[] = "COMANDO INVALIDO\n\r";

int main(void)
{	
	//INICIALIZACIÓNES
	SIGNALGENERATOR_Init();
	Comunicacion_Inicializar(BR9600);	
	//BIENVENIDA (UNICA VEZ)
	Comunicacion_Enviar_mensaje(msgBienvenida);
	//SUPER-LOOP
	while (1) 
    {	
		//TAREAS DE BACKGROUND
		if (fin_comando == 1){
			Comunicacion_Recibir_comando();
			fin_comando=0;
		}
		if (comando_invalido == 1){
			Comunicacion_Enviar_mensaje(msgComandoInvalido);	
			comando_invalido=0;
		}
    }
	return 0;
	
}

//TAREAS DE FOREGROUND ISR(TX) Y ISR(RX) EN serialPort.c (INTERACTUAN CON HARDWARE)