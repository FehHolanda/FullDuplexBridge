/*
 * intrpt.h
 *
 *  Created on: Sep 27, 2018
 *      Author: ea871
 */

#ifndef INTRPT_H_
#define INTRPT_H_

void Start_Timer(void);
void init_IRQA(void);
void nvic_config(void);
void init_NMI(void);

#endif /* INTRPT_H_ */
