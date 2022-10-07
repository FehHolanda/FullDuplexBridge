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