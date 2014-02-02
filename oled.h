/* 
 * File:   oled.h
 * Author: jesus
 *
 * Created on January 30, 2014, 7:02 PM
 */

#ifndef OLED_H
#define	OLED_H

#include <stdint.h>
#include "../pinconfig.h"

/* User must define OLED_CS, OLED_RST and OLED_DC here or in a "pinconfig.h" file
 * Example:
 *  #define OLED_CS         LATAbits.LATA0      // Chip select
 *  #define OLED_CS_TRS     TRISAbits.TRISA0    // Chip select TRIS
 *  #define OLED_RST        LATBbits.LATB6      // Reset
 *  #define OLED_RST_TRS    TRISBbits.TRISB6    // Reset TRIS
 *  #define OLED_DC         LATBbits.LATB7      // Data/command
 *  #define OLED_DC_TRS     TRISBbits.TRISB7    // Data/command TRIS
 */

#if !defined(OLED_CS) || !defined (OLED_RST) || !defined(OLED_DC) || \
    !defined(OLED_CS_TRS) || !defined (OLED_RST_TRS) || !defined(OLED_DC_TRS)
#error("Must define OLED_CS, OLED_RST and OLED_DC ")
#endif

#define OLED_128_64

#if defined OLED_128_64
  #define OLED_WIDTH                  128
  #define OLED_HEIGHT                 64
#endif
#if defined OLED_128_32
  #define OLED_WIDTH                  128
  #define OLED_HEIGHT                 32
#endif

#define OLED_BUFFSIZE       (OLED_WIDTH * OLED_HEIGHT / 8)
#define OLED_NPAGES         (OLED_HEIGHT / 8)
#define OLED_LAST_PAGE      (OLED_NPAGES - 1)
#define OLED_LAST_COL       (OLED_WIDTH - 1)


void oled_begin(void);
void oled_reset(void);
void oled_render(void);
void oled_clearDisplay(void);

void oled_printc(char c, uint8_t col, uint8_t line);
void oled_prints(char* s, uint8_t col, uint8_t line);

void oled_drawPixel(uint8_t x, uint8_t y);

#endif	/* OLED_H */

