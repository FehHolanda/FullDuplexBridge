//biblioteca de ativamento dos System Clock Gating Control(SCGC) e MUX

#include "derivative.h" /* include peripheral declarations */
#define SET_BIT(reg, idx)	reg = (reg | (1 << idx))		// Macro que seta o bit idx do registrador reg

/*
 Resumo de portas ativas: 
 SCGC4->10(UART0)  ---->UART0 
 SCGC5->09(Porta A)---->NMI,IRQ,UART0
 SCGC5->10(Porta B)---->TPM
 SCGC5->11(Porta C)---->LCD
 SCGC6->25(TPM0  0)---->TPM1  
  
 Resumo Mux  
 
 PORTA 1 (010)---->UART0_RX
 PORTA 2 (010)---->UART0_TX
 PORTA 4 (111)---->NMI
 PORTA 5 (001)---->I/O(IRQ)
 PORTA 12(001)---->I/O(IRQ)
 
 PORTB 1 (011)---->TPM
 
 PORTC 0 (001)---->I/O
 PORTC 1 (001)---->I/O
 PORTC 2 (001)---->I/O
 PORTC 3 (001)---->I/O
 PORTC 4 (001)---->I/O
 PORTC 5 (001)---->I/O
 PORTC 6 (001)---->I/O
 PORTC 7 (001)---->I/O  
   
  */

//Habilita portas para o LCD
void init_GPIO_LCD(void){
	
	SET_BIT(SIM_SCGC5, 11);		   			
	PORTC_PCR0 = PORTC_PCR0 & 0xFFFFF8FF;	
	PORTC_PCR1 = PORTC_PCR1 & 0xFFFFF8FF;	
	PORTC_PCR2 = PORTC_PCR2 & 0xFFFFF8FF;	
	PORTC_PCR3 = PORTC_PCR3 & 0xFFFFF8FF;	
	PORTC_PCR4 = PORTC_PCR4 & 0xFFFFF8FF;	
	PORTC_PCR5 = PORTC_PCR5 & 0xFFFFF8FF;	
	PORTC_PCR6 = PORTC_PCR6 & 0xFFFFF8FF;	
	PORTC_PCR7 = PORTC_PCR7 & 0xFFFFF8FF;	
	PORTC_PCR8 = PORTC_PCR8 & 0xFFFFF8FF;	
	PORTC_PCR9 = PORTC_PCR9 & 0xFFFFF8FF;	
		
		
	
	SET_BIT(PORTC_PCR0, 8);				// Seta bit 0 do MUX, assim os bits de MUX serao 001
	SET_BIT(PORTC_PCR1, 8);
	SET_BIT(PORTC_PCR2, 8);
	SET_BIT(PORTC_PCR3, 8);
	SET_BIT(PORTC_PCR4, 8);
	SET_BIT(PORTC_PCR5, 8);
	SET_BIT(PORTC_PCR6, 8);
	SET_BIT(PORTC_PCR7, 8);
	SET_BIT(PORTC_PCR8, 8);
	SET_BIT(PORTC_PCR9, 8);
		
	
	GPIOC_PDDR = 1023;				// Seta os pino 0 a 9 do PORTC como saida 
	GPIOC_PDOR = 0;					//zera os pinos da porta C
	
	return;	
}

//Ativa NMI no pino4 Porta A
void init_GPIO_NMI(void){
	
	//SET_BIT(SIM_SCGC5, 9);
	
	PORTA_PCR4 = PORTA_PCR4 & 0xFFFFF8FF;		//Zerar Mux
		
		
	SET_BIT(PORTA_PCR4, 8);						// Seta bit 0,1,2 do MUX, assim os bits de MUX serao 111
	SET_BIT(PORTA_PCR4, 9);
	SET_BIT(PORTA_PCR4,10);
		
	return;	
}

//Ativa IRQ no pino12 e pino5 Porta A
void init_GPIO_IRQ(void){
	
	//SET_BIT(SIM_SCGC5, 9);
		
	PORTA_PCR12 = PORTA_PCR12 & 0xFFFFF8FF;		//Zerar Mux			
	SET_BIT(PORTA_PCR12, 8);						// Seta bit 0 do MUX, assim os bits de MUX serao 001
	PORTA_PCR5 = PORTA_PCR5 & 0xFFFFF8FF;		//Zerar Mux			
	SET_BIT(PORTA_PCR5,8);						// Seta bit 0 do MUX, assim os bits de MUX serao 001
	
	return;
}

//habilita portas para o TPM
void init_GPIO_TPM(void){
	SET_BIT(SIM_SCGC5,10);
	SET_BIT(SIM_SCGC6,25);		
				
	PORTB_PCR1 = PORTB_PCR1 & 0xFFFFF8FF;	//MUX =000		
	SET_BIT(PORTB_PCR1, 8);					///MUX=011
	SET_BIT(PORTB_PCR1, 9);	
	return;
}

void init_GPIO_UART0(void){
	SET_BIT(SIM_SCGC4,10);
	SET_BIT(SIM_SCGC5,9);		
	
	PORTA_PCR1 = PORTA_PCR1 & 0xFFFFF8FF;	
	PORTA_PCR2 = PORTA_PCR2 & 0xFFFFF8FF;		
		
	SET_BIT(PORTA_PCR1, 9);					
	SET_BIT(PORTA_PCR2, 9);
	
	return;
}

void init_GPIO_UART2(void){
	SET_BIT(SIM_SCGC4,12);
	SET_BIT(SIM_SCGC5,13);		
	
	PORTE_PCR22 = PORTE_PCR22 & 0xFFFFF8FF;	
	PORTE_PCR23 = PORTE_PCR23 & 0xFFFFF8FF;		
		
	SET_BIT(PORTE_PCR22, 10);					
	SET_BIT(PORTE_PCR23, 10);
	
	return;
}
