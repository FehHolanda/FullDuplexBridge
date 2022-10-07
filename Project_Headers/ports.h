/*
 * ports.h
 *
 *  Created on: Oct 15, 2018
 *      Author: ea871
 */

#ifndef PORTS_H_
#define PORTS_H_

void init_GPIO_LCD(void);
void init_GPIO_UART0(void);
void init_GPIO_UART2(void);
void init_GPIO_NMI(void);
void init_GPIO_IRQ(void);
void init_GPIO_TPM(void);

#endif /* PORTS_H_ */
