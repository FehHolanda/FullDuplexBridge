/*
 * uart.h
 *
 *  Created on: Sep 6, 2018
 *      Author: ea871
 */

#ifndef UART_H_
#define UART_H_

#include "structs.h"

void init_UART0(void);
void putchar_terminal(unsigned char c, Buffer *buffer_out);
void getchar_terminal(unsigned char c, Buffer *buffer_in);
void puts_terminal(unsigned char *s, Buffer *buffer_out);
void init_UART2(void);
void putchar_serial(unsigned char c, Buffer *buffer_out);
int getchar_serial(unsigned char c, Buffer *buffer_in);
void puts_serial(unsigned char *s, Buffer *buffer_out);

#endif /* UART_H_ */
