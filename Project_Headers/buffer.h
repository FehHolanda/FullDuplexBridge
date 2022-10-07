/*
 * buffer.h
 *
 *  Created on: Oct 10, 2018
 *      Author: ea871
 */

#ifndef BUFFER_H_
#define BUFFER_H_
#include "structs.h"

void init_buffer(Buffer *buf);
void buffer_remove(Buffer *buf);
void buffer_add(Buffer *buf);
void set_buffer(Buffer *buf);

#endif /* BUFFER_H_ */
