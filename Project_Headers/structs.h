/*
 * structs.h
 *
 *  Created on: Oct 10, 2018
 *      Author: ea871
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_
#define MAX_PKT 1024

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


typedef unsigned int seq_nr;
typedef struct {unsigned char data[MAX_PKT];} packet; 
typedef enum {data, ack, nak} frame_kind; 
typedef enum {timeout} event_type;


typedef struct { 		/* frames are transported in this layer */
frame_kind kind; 		/* what kind of frame is it? */
seq_nr seq;				/* sequence number */
seq_nr ack; 			/* acknowledgement number */
packet info; 			/* the network layer packet */
} frame;


#endif /* STRUCTS_H_ */
