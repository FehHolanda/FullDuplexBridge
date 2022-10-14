/*Projeto
//Felipe de Holanda Carvalho 		R.A:171004 

DescrissÒo:
O projeto tem como finalidade a transmissÒo entre dois microcontroladores... para isso usamos a Uart0 para comunicaþ§a com o terminal e a Uart2 para comunicaþÒo
com o micontrolador.
A comunicaþÒo se dß por um protocolo onde monto uma struct header, ela contem flag e dado , envio esses dois dados seguidos pela Uart2, por sua vez o outro
microcontrolador recebe esses dados e pelo item flag determina se o dado Ú de fato um dado ou um comando., e manda uma confirmaþÒo de recebimento para o microcontrolador
que enviou.
*/

#include "derivative.h" /* include peripheral declarations */
#include "delay.h"
#include "lcd.h"
#include "uart.h"
#include "intrpt.h"
#include "buffer.h"
#include "structs.h"
#include "interruptions.h"

#define SET_BIT(reg, idx)	reg = (reg | (1 << idx))		// Macro que seta o bit idx do registrador reg.

//declararacao das funþoes.
void test_comand(unsigned char cmd);
void Clear_ALL(void);
void Clear_terminal(void);
void UART0_IRQHandler();
void test_twh(void);
void confirm_cmd(void);

/*-----------------------------------------------------------------------------------------------------------------------*/

/*Variaveis globais*/
int conect=0,try_conect=0,d=0,rec_confirmed=0,acept=0,request =0,control=0,confirm_erase=0,cont_rec=0,cont_rec_last=0;
int i=1,j=1,p=0,type=0,sis=2;
int id_receptor=0,n=0;

//Buffers
Buffer buffer_in;
Buffer buffer_out;

//strings 
unsigned char text0[] = "Bem vindo \n\r";
unsigned char text1[] = "\n\rPara iniciar uma conexao pressione s \n\r";
unsigned char text2[] = "\n\rErro na tentativa de conexao\n\r";
unsigned char text3[] = "\n\rConexao Habilitada\n\r";
unsigned char text4[] = "\n\rConexao Solicitada, aceitar? s \n\r";


/*--------------------------------------------------------------------------------------------------------------------------*/

int main(void) {
	init_buffer(&buffer_in);
	init_buffer(&buffer_out);

	
	//inicializacao dos modulos.
	init_GPIO();		//Ativa a GPIO para o LCD
	init_LCD();			//Congigura LCD
	init_UART0();		//Configura UART0
	init_UART2();		//Configura UART2
	init_NMI();			//Ativa NMI 
	init_IRQA();		//Ativa IRQ das portas A
	nvic_config();		//Ativa as interrupþoess e configura as prioridades
	
	//ativar as condicoes iniciais.
	Clear_ALL();
	puts_UART0(text0);
	//puts_UART0(text1);
	
	conect=1;
	//esperando habilitar conexao
	while(!conect){
		if(try_conect && !request && j) {
			putchar_UART2('0');			//envia pedido de conexao
			try_conect=0;
			j=0;
		}
		
		else if(try_conect && request && i) {
			puts_UART0(text4);	
			try_conect=0;
			i=0;
		}
		
		if(acept){
			putchar_UART2('0');			//envia confirmaþÒo de conexao
			puts_UART0(text3);
			conect=1;
		}
	}
		

while(1){			
}
	
	
	//Finaliza.	
	//Clear_ALL();
	
	return 0;
}

//---------------------------------------------------------------------------------------------------------------------

/*--------------------------------------------------------recepcao UART0*-------------------------------------------------------------------------*/
void UART0_IRQHandler(){
	unsigned char f;
	
	if (UART0_S1 & UART0_S1_RDRF_MASK){
		f =	UART0_D;		
		putchar_UART0(f);										//ecoa no terminal
		
		if(!conect)test_comand(f);								//testa se Ú um comando 		
		else getchar_UART0(f); 									//caso esteja conectado
	}
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/	
	
	
/*--------------------------------------------------------transmissao UART0*-------------------------------------------------------------------------*/		
	
	else if((UART0_S1 & UART0_S1_TDRE_MASK)){
		if(buffer_in.empty){									//Se o buffer estiver vazio desabilita transmissao
			UART0_C2 = 0x2c;
		}
		else{
			UART0_D = buffer_in.Buff[buffer_in.index_start]; 	// envia caracter DO BUFFER a ser transmitido		
			buffer_remove(&buffer_in);							//atualiza buffer
		}
	}
	return;
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/	

void UART2_IRQHandler(){
	int z;
	unsigned char f;
	
		
/*--------------------------------------------------------recepcao UART2*-------------------------------------------------------------------------*/

	
	if (UART2_S1 & UART_S1_RDRF_MASK){					
		f =	UART2_D;	



	}

/*-----------------------------------------------------------------------------------------------------------------------------------------------*/	
	
	
	
	
/*--------------------------------------------------------transmissao UART2*-------------------------------------------------------------------------*/	
	else if((UART2_S1 & UART_S1_TDRE_MASK)){			
		if(buffer_out.empty){											//Se o buffer estiver vazio desabilita transmissao
				UART2_C2 = 0x2c;
			}
		else{
				

								
		}
	}
	
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/	

void NMI_Handler(){
	d=1;
	return;
}

void PORTA_IRQHandler(){	
	
	return;
}

void SysTick_Handler(){
	n++;
	if(n==10){
		SYST_CSR = 0x00000006;
		n=0;
	
		event_type Timeout = timeout;
	}

	else;
	
	return;
}

//testa o comando enviado pelo terminal.
void test_comand(unsigned char cmd){
		if(cmd == 's' && !request)	try_conect=1;
		else if((cmd == 's') && request)acept=1;
		
	return ;
}

//funcao que limpa terminal e LCD.
void Clear_ALL(void){
	clear_LCD();											//Limpa LCD.
	putchar_UART0(27);										//Limpa terminal.
	puts_UART0("[2J");
	putchar_UART0(27);										//Carriage return.
	puts_UART0("[H");
	return;
}

//funþao que limpa apenas o terminal
void Clear_terminal(void){
	putchar_UART0(27);										//Limpa terminal.
	puts_UART0("[2J");
	putchar_UART0(27);										//Carriage return.
	puts_UART0("[H");
	return;
}
