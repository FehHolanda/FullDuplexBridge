/*
 * uart.h
 *
 *  Created on: Sep 6, 2018
 *      Author: ea871
 */

#ifndef UART_H_
#define UART_H_

void init_UART0(void);
void putchar_UART0(unsigned char c);
void getchar_UART0(unsigned char c);
void puts_UART0(unsigned char *s);
void init_UART2(void);
void putchar_UART2(unsigned char c,int type);
int getchar_UART2(int type ,unsigned char c);
void puts_UART2(unsigned char *s);


#endif /* UART_H_ */
