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
extern struct header hdr;
extern struct tw_hand twh_t;
extern struct tw_hand twh_r;

extern int id_receptor;

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
	
	putchar_UART2(c,4);										

	return;
}

int getchar_UART2(int type ,unsigned char c){
	int r=0;
	
	if(!type){
		hdr.flags=c;
		get_header(&hdr,&twh_r);
	}
	
	else if(type!=0){
		id_receptor =( id_receptor + 1)%16;
		hdr.dado=c;		
		if(twh_r.id == id_receptor ){
			if(type==2){
				while(buffer_in.full);										//se não estiver cheio
				buffer_in.Buff[buffer_in.index_end]=hdr.dado; 				// envia caracter para o buffer		
				buffer_add(&buffer_in);										//atualiza buffer ;
				UART0_C2 = 0xAC;
				r=1;
				}			
			}
		else 			id_receptor =( id_receptor -1)%16;

	}
	
	return r;
}

void putchar_UART0(unsigned char c){
	while(buffer_in.full);										//se não estiver cheio		
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

void putchar_UART2(unsigned char c,int type){
	twh_t.id++;
	hdr.dado=c;
	
	switch(type){		
	
		//enviar ack
		case 0:
			twh_t.ack = 1;
			twh_t.wa  = 0;
			twh_t.syn = 0;				
			twh_t.fin = 0;			
			break;
			
		//Enviar syn	
		case 1: 		
			twh_t.ack = 0;
			twh_t.wa  = 0;
			twh_t.syn = 1;				
			twh_t.fin = 0;
			break;
	
	//Enviar syn e ack
		case 2: 
			twh_t.ack = 1;
			twh_t.wa  = 0;
			twh_t.syn = 1;				
			twh_t.fin = 0;
			break;
			
		
		case 4:
			twh_t.ack = 1;
			twh_t.wa  = 1;
			twh_t.syn = 0;				
			twh_t.fin = 0;			
			break;
	}
	
	
	create_header(&hdr,&twh_t);
	
	while(buffer_out.full);										//se não estiver cheio	
	buffer_out.Buff[buffer_out.index_end]= hdr.flags; 			// envia caracter para o buffer		
	buffer_add(&buffer_out);									//atualiza buffer	
	
	while(buffer_out.full);										//se não estiver cheio	
	buffer_out.Buff[buffer_out.index_end]= hdr.dado; 			// envia caracter para o buffer		
	buffer_add(&buffer_out);									//atualiza buffer	
	
	UART2_C2 = 0xAC;											//ativa transmissao
	
	return;
}
void puts_UART2(unsigned char *s){
	int i=0;
	while(s[i]!='\0'){
		putchar_UART2(s[i],4);
		i++;
	}
	return;
}
