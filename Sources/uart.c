/*
 * uart.c
 *
 *  Created on: Sep 6, 2018
 *      Author: ea871
 */

#include "derivative.h" /* include peripheral declarations */
#include "buffer.h"
#include"structs.h"
#include "ports.h"
#define SET_BIT(reg, idx)	reg = (reg | (1 << idx))		// Macro que seta o bit idx do registrador reg

extern struct Buffer buffer_in;
extern struct Buffer buffer_out;


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


void getchar_UART0(unsigned char c){
	
	putchar_UART2(c);										

	return;
}

int getchar_UART2(unsigned char c){
	
	while(buffer_in.full);										//se n�o estiver cheio
	buffer_in.Buff[buffer_in.index_end]=c; 						// envia caracter para o buffer		
	buffer_add(&buffer_in);										//atualiza buffer ;
	UART0_C2 = 0xAC;
	return 0;
}

void putchar_UART0(unsigned char c){
	while(buffer_in.full);										//se n�o estiver cheio		
	buffer_in.Buff[buffer_in.index_end]=c; 						// envia caracter para o buffer		
	buffer_add(&buffer_in);										//atualiza buffer ;
	UART0_C2 = 0xAC;											//ativa transmissao na UART0	
	return;
}
void puts_UART0(unsigned char *s){
	int i=0;
	while(s[i]!='\0'){
		putchar_UART0(s[i]);
		i++;
	}
	return;
}

void putchar_UART2(unsigned char c){
	
	while(buffer_out.full);										//se n�o estiver cheio	
	buffer_out.Buff[buffer_out.index_end]= c; 					// envia caracter para o buffer		
	buffer_add(&buffer_out);									//atualiza buffer	
	UART2_C2 = 0xAC;											//ativa transmissao
	
	return;
}
void puts_UART2(unsigned char *s){
	int i=0;
	while(s[i]!='\0'){
		putchar_UART2(s[i]);
		i++;
	}
	return;
}
