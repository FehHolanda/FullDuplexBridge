/*
 * structs.h
 *
 *  Created on: Oct 10, 2018
 *      Author: ea871
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

//definição de uma variavel boleana
typedef enum {false, true} boolean;
#define SET_BIT(reg, idx)	reg = (reg | (1 << idx))		// Macro que seta o bit idx do registrador reg


//definiзгo da estrutura do buffer
typedef struct Buffer{
	unsigned char Buff[50];
	int size;
	boolean full;					//full = true ------> buffer cheio
	boolean empty;					//empty = true ------> buffer vazio
	int index_start;
	int index_end;
	int count;
}Buffer;

#endif /* STRUCTS_H_ */
