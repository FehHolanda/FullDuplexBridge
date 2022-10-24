
/*



*/

#include "../Project_Headers/derivative.h" /* include peripheral declarations */
#include "../Project_Headers/uart.h"
#include "../Project_Headers/structs.h"
#include "../Project_Headers/buffer.h"
#include "../Project_Headers/protocol.h"


Buffer buffer_in_terminal;
Buffer buffer_out_terminal;
Buffer buffer_in_Serial;
Buffer buffer_out_Serial;

boolean event_ready;
boolean stoped_timer;
boolean chat_ready;

event_type event_save;

int countimer;
int cont=0;
int frame_test[MAX_PKT+1];
int checksum = 0;



//---------------------------------------------------------------------------------------------------------------------
// UART0 - TERMINAL
/*--------------------------------------------------------recepcao UART0*  -------------------------------------------------------------------------*/
void UART0_IRQHandler(){
	unsigned char f;
	
	if (UART0_S1 & UART0_S1_RDRF_MASK){
		f =	UART0_D;		
		putchar_terminal(f,&buffer_in_terminal);									//ecoa no terminal
		}
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/	
	
	
/*--------------------------------------------------------transmissao UART0*-------------------------------------------------------------------------*/		
	
	else if((UART0_S1 & UART0_S1_TDRE_MASK)){
		if(buffer_out_terminal.empty){									//Se o buffer estiver vazio desabilita transmissao
			UART0_C2 = 0x2c;
		}
		else{
			UART0_D = buffer_out_terminal.Buff[buffer_out_terminal.index_start]; 	// envia caracter DO BUFFER a ser transmitido		
			buffer_remove(&buffer_out_terminal);							//atualiza buffer
		}
	}
	return;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/	

/*  REDE DE COMUNICAÇÂO  */
void UART2_IRQHandler(){
	unsigned char f;
	int aux[MAX_PKT];		
		
/*--------------------------------------------------------recepcao UART2*-------------------------------------------------------------------------*/
	if (UART2_S1 & UART_S1_RDRF_MASK){	
		f =	UART2_D;			
	
		 /*CHECK SUM*/
		
		if(cont<MAX_PKT+1) {
			aux[cont] = f;
			if(cont>1) checksum += f;
			cont++;
		}

		else{
				if(checksum == f) {
					event_save = frame_arrival;
					for(int i =0;i<MAX_PKT+1;i++) putchar_serial(aux[i],&buffer_in_Serial);
					putchar_serial(checksum,&buffer_in_Serial);
				}
			
				else event_save = cksum_err; 
			
			cont=0;
			checksum = 0;
			event_ready = true;
			
		}
	}
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/	
	
/*--------------------------------------------------------transmissao UART2*-------------------------------------------------------------------------*/	
	else if((UART2_S1 & UART_S1_TDRE_MASK)){			
		if(buffer_out_Serial.empty){											//Se o buffer estiver vazio desabilita transmissao
				UART2_C2 = 0x2c;
			}
		else{
				
			UART2_D = buffer_out_Serial.Buff[buffer_out_Serial.index_start]; 			//envia caracter DO BUFFER a ser transmitido	
			buffer_remove(&buffer_out_Serial);								
		}
	}		
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/	

void NMI_Handler(){
	return;
}

void PORTA_IRQHandler(){	
		
	return;
}

void SysTick_Handler(){
	countimer++;
	if(countimer==10){
		//SYST_CSR = 0x00000006;
		countimer=0;
		if(!stoped_timer){
			event_save = timeout;
			event_ready = true;
		}
		
		
	}
	else;
	
	return;
}