/*
 * lcd.c
 *
 *  Created on: Sep 5, 2018
 *      Author: ea871
 */
/* Felipe de Holanda Carvalho 	Ra:171004*/

#include "derivative.h" /* include peripheral declarations */
#include "delay.h"
#include "ports.h"
#define SET_BIT(reg, idx)	reg = (reg | (1 << idx))		// Macro que seta o bit idx do registrador reg

//inicia e configura as portas do microcontrolador
void init_GPIO(void){	
	init_GPIO_LCD();	
	return;
	
}
//Configura o LCD
void init_LCD(void){
	
	putcmd_LCD(0x0000003c,40); 			//configura para o  LCD 2 linhas
	
	putcmd_LCD(0x0000000f,40);			//configura o cursor	
	
	clear_LCD();
	
	putcmd_LCD(0x00000006,40);
		
	return;
}

//Função que executa o pulos de ENABLE
void Enable(void){
	SET_BIT(GPIOC_PSOR, 9);		//enable on
	SET_BIT(GPIOC_PCOR, 9);		//enable off
	return;
}

// envia um comando para o LCD
void putcmd_LCD(unsigned char byte, unsigned int t){
	
	SET_BIT(GPIOC_PCOR,8);		//RS off				
	GPIOC_PDOR = byte;
	Enable();
	delay(t);
	return;
}

//Envia um char para o LCD
void putchar_LCD(unsigned char text){
	
	SET_BIT(GPIOC_PSOR, 8);		//RS on				
	GPIOC_PDOR = (GPIOC_PDOR & 0xffffff00) | text;
	Enable();
	delay(40);
	return;	
}

//Limpa o Dysplay
void clear_LCD(void){
	
	putcmd_LCD(1,1800);
	return;
}

//Seleciona uma posicao no display
void setpos_LCD(unsigned int linha, unsigned int pos){
	
	unsigned int x;
	unsigned int y;
	
	if (linha==1)		x=0b0010000000;
	else if (linha==2)	x=0b0011000000;
	
	y = x+(pos-1); 
	
	putcmd_LCD(y,40);
}

//escreve uma string no display
void puts_LCD(unsigned char *word){
	
	int p=17;			
	int i=0;
	
	//setpos_LCD(1,1);
	while(word[i] != '\0'){
		
		//prencher primeira linha		
		if(i<16){
			putchar_LCD(word[i]);
		}
				
		//prenche a segunda linha
		if(i>=16 && i<32){
			setpos_LCD(2,i-15);
			putchar_LCD(word[i]);
		}		
		
		//rotina para Strings maiores que o total de posicoes do display
		if(i>=32){			
			setpos_LCD(1,p);					//seleciona a posição fantasma(17) do diplay
			putchar_LCD(word[p-1]);				//Salva na posição fantasma	o primeiro caracter da linha 2
			putcmd_LCD(0b0000011000,40);		//Shift no display
			setpos_LCD(2,p);					//seleciona a ultima posição da segunda linha	
			putchar_LCD(word[i]);				//escreve na ultima posicao
			p++;								// implementa a variavel auxiliar
		}		
	
	i++;
	}	
	return;
	
	
}
