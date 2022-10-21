/*
 * uart.c
 *
 *  Created on: Sep 6, 2018
 *      Author: ea871
 */

#include "../Project_Headers/derivative.h" /* include peripheral declarations */
#include "../Project_Headers/buffer.h"
#include "../Project_Headers/ports.h"
#include "../Project_Headers/uart.h"


void init_UART0(void){
	init_GPIO_UART0();			
		
	SET_BIT(SIM_SOPT2,26);
		
	UART0_BDL = 0x20;
	UART0_BDH =0x02;
	
	UART0_C2 = 0x2C;
	
	return;	
	
}

void init_UART2(void){
	init_GPIO_UART2();			
		
		
	UART2_BDL = 0x45;
	UART2_BDH =0x00;
	
	UART2_C2 = 0x2C;
	
	return;	
}


void getchar_terminal(unsigned char c,Buffer *buffer_in){
	
	putchar_serial(c,buffer_in);										

	return;
}

int getchar_serial(unsigned char c, Buffer *buffer_in){
	
	while(buffer_in->full);										//se n�o estiver cheio
	buffer_in->Buff[buffer_in->index_end]=c; 						// envia caracter para o buffer		
	buffer_add(buffer_in);										//atualiza buffer ;
	UART0_C2 = 0xAC;
	return 0;
}

void putchar_terminal(unsigned char c, Buffer *buffer_in){
	while(buffer_in->full);										//se n�o estiver cheio		
	buffer_in->Buff[buffer_in->index_end]=c; 						// envia caracter para o buffer		
	buffer_add(buffer_in);										//atualiza buffer ;
	UART0_C2 = 0xAC;											//ativa transmissao na UART0	
	return;
}
void puts_terminal(unsigned char *s, Buffer *buffer_out){
	int i=0;
	while(s[i]!='\0'){
		putchar_terminal(s[i],buffer_out);
		i++;
	}
	return;
}

void putchar_serial(unsigned char c, Buffer *buffer_out){	
	while(buffer_out->full);										//se n�o estiver cheio	
	buffer_out->Buff[buffer_out->index_end]= c; 					// envia caracter para o buffer		
	buffer_add(buffer_out);
	UART2_C2 = 0xAC;											//ativa transmissao
	return;
}
void puts_serial(unsigned char *s, Buffer *buffer_out){
	int i=0;
	while(s[i]!='\0'){
		putchar_serial(s[i],buffer_out);
		i++;
	}
	return;
}

