/*
 * intrpt.c
 *
 *  Created on: Sep 27, 2018
 *      Author: ea871
 */

#include "derivative.h" /* include peripheral declarations */
#include "ports.h"
#define SET_BIT(reg, idx)	reg = (reg | (1 << idx))		// Macro que seta o bit idx do registrador reg

//Ativa o Systick
void Start_systick(void){	
	SYST_CSR = 0x00000007;
	SYST_RVR = 0x33333;
	//SYST_RVR = 0x99999;
	return;
}

//Configura e Ativa  Prioridades 
void nvic_config(void){
	
	NVIC_IPR3 = NVIC_IPR3 & 0xFF3FFF3F;
	NVIC_IPR7 = NVIC_IPR7 & 0xFF7FFFFF;

	
	SET_BIT(NVIC_ISER,12);
	SET_BIT(NVIC_ISER,14);
	SET_BIT(NVIC_ISER,30);
	
	return;
}

//Ativa IRQ no pino12 e pino5 Porta A
void init_IRQA(void){
	init_GPIO_IRQ();
		
	PORTA_PCR12 = PORTA_PCR12 & 0xFFF0FFFF;		//Zerar IRQA	
	SET_BIT(PORTA_PCR12, 19);					// Seta bit 3,1, do IRQA, assim os bits serao 1001(borda de subida)
	SET_BIT(PORTA_PCR12, 16);
	
	PORTA_PCR5 = PORTA_PCR5 & 0xFFF0FFFF;		//Zerar IRQA	
	SET_BIT(PORTA_PCR5, 19);					// Seta bit 3,1, do IRQA, assim os bits serao 1001(borda de subida)
	SET_BIT(PORTA_PCR5, 16);
		
	return;
}
void init_NMI(void){
	init_GPIO_NMI();
	return;
}


