/* 
 * File:   oled_print.h
 * Author: jesus
 *
 * Created on January 31, 2014, 7:26 PM
 */

#ifndef OLED_PRINT_H
#define	OLED_PRINT_H

#include <stdint.h>


#define CHAR_WIDTH  5

void oled_putc(uint8_t* buffer, char c, uint8_t col, uint8_t line);
void oled_puts(uint8_t* buffer, const char* s, uint8_t col, uint8_t line, uint8_t sLen);

#endif	/* OLED_PRINT_H */

