/*
 * lcd.h
 *
 *  Created on: Sep 5, 2018
 *      Author: ea871
 */

#ifndef LCD_H_
#define LCD_H_

void init_GPIO(void);
void puts_LCD(unsigned char *word);
void setpos_LCD(unsigned int linha, unsigned int pos);
void init_LCD(void);
void clear_LCD(void);
void putchar_LCD(unsigned char text);
void putcmd_LCD(unsigned char byte, unsigned int t);
void puts_LCD(unsigned char *word);

#endif /* LCD_H_ */
