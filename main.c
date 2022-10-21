/*Projeto
//Felipe de Holanda Carvalho 		R.A:171004 

DescrissÒo:
O projeto tem como finalidade a transmissÒo entre dois microcontroladores... para isso usamos a Uart0 para comunicaþ§a com o terminal e a Uart2 para comunicaþÒo
com o micontrolador.
A comunicaþÒo se dß por um protocolo onde monto uma struct header, ela contem flag e dado , envio esses dois dados seguidos pela Uart2, por sua vez o outro
microcontrolador recebe esses dados e pelo item flag determina se o dado Ú de fato um dado ou um comando., e manda uma confirmaþÒo de recebimento para o microcontrolador
que enviou.
*/

#include "Project_Headers/derivative.h" /* include peripheral declarations */
#include "Project_Headers/delay.h"
#include "Project_Headers/lcd.h"
#include "Project_Headers/uart.h"
#include "Project_Headers/intrpt.h"
#include "Project_Headers/buffer.h"
#include "Project_Headers/structs.h"
#include "Project_Headers/unibridge.h"


//declararacao das funþoes.
void Clear_ALL(void);
void Clear_terminal(void);

/*-----------------------------------------------------------------------------------------------------------------------*/

/*Variaveis globais*/
int count=0;

//Buffers
extern Buffer buffer_in_terminal;
extern Buffer buffer_out_terminal;
extern Buffer buffer_in_Serial;
extern Buffer buffer_out_Serial;

//strings 
unsigned char text0[] = "Bem vindo \n\r";
unsigned char text1[] = "\n\rPara iniciar uma conexao pressione s \n\r";
unsigned char text2[] = "\n\rErro na tentativa de conexao\n\r";
unsigned char text3[] = "\n\rConexao Habilitada\n\r";
unsigned char text4[] = "\n\rConexao Solicitada, aceitar? s \n\r";

/*--------------------------------------------------------------------------------------------------------------------------*/

int main(void) {


	init_buffer(&buffer_in_terminal);
	init_buffer(&buffer_out_terminal);
	init_buffer(&buffer_in_Serial);
	init_buffer(&buffer_out_Serial);

	
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
	puts_terminal(text0,&buffer_out_terminal);
	//puts_UART0(text1);
	
		


	//Finaliza.	
	//Clear_ALL();
	
	return 0;
}


//funcao que limpa terminal e LCD.
void Clear_ALL(void){
	clear_LCD();											//Limpa LCD.
	putchar_terminal(27,&buffer_out_terminal);										//Limpa terminal.
	puts_terminal("[2J",&buffer_out_terminal);
	putchar_terminal(27,&buffer_out_terminal);										//Carriage return.
	puts_terminal("[H",&buffer_out_terminal);
	return;
}

//funþao que limpa apenas o terminal
void Clear_terminal(void){
	putchar_terminal(27,&buffer_out_terminal);										//Limpa terminal.
	puts_terminal("[2J",&buffer_out_terminal);
	putchar_terminal(27,&buffer_out_terminal);										//Carriage return.
	puts_terminal("[H",&buffer_out_terminal);
	return;
}
