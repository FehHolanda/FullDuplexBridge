/*
 * buffer.c
 *
 *  Created on: Oct 10, 2018
 *      Author: ea871
 */

#include "derivative.h" /* include peripheral declarations */
#include "structs.h"
#define SET_BIT(reg, idx)	reg = (reg | (1 << idx))		// Macro que seta o bit idx do registrador reg

Buffer *bufr;

void init_buffer(Buffer *buf){
	bufr = buf;
	(*bufr).size=50;
	(*bufr).full= false;
	(*bufr).empty= true;
	(*bufr).index_start=0;
	(*bufr).index_end=0;
	(*bufr).count=0;
	return;
}	

//remove um item do buffer
void buffer_remove(Buffer *buf){
	bufr = buf;
	if((*bufr).full)
	    (*bufr).full=false;
	
	(*bufr).count = ((*bufr).count + (*bufr).size -1)%(*bufr).size;
	(*bufr).index_start =((*bufr).index_start + 1)%(*bufr).size;
	
	if(!(*bufr).count){				//buffer esta vazio -> atualizar flag
		(*bufr).empty=true;
	}
	return;	
}

//adiciona um item do buffer
void buffer_add(Buffer *buf){
	bufr = buf;
	if((*bufr).empty)
	    (*bufr).empty=false;	
	(*bufr).count = ((*bufr).count +1)%((*bufr).size+1);
	(*bufr).index_end =((*bufr).index_end +1)%((*bufr).size);
	
	
	if((*bufr).count == (*bufr).size){			//buffer esta cheio
		(*bufr).full= true;
	}	
	
	return;
}