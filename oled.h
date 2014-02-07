#ifndef OLED_H
#define	OLED_H

#include <stdint.h>

#define OLED_128_64

#if defined OLED_128_64
  #define OLED_WIDTH                  (128U)
  #define OLED_HEIGHT                 (64U)
#endif
#if defined OLED_128_32
  #define OLED_WIDTH                  (128U)
  #define OLED_HEIGHT                 (32U)
#endif

#define OLED_BUFFSIZE       (OLED_WIDTH * OLED_HEIGHT / 8U)
#define OLED_NPAGES         (OLED_HEIGHT / 8U)
#define OLED_LAST_PAGE      (OLED_NPAGES - 1U)
#define OLED_LAST_COL       (OLED_WIDTH - 1U)


void oled_init(void);
void oled_reset(void);
void oled_render(void);
void oled_clearDisplay(void);

void oled_printc(char c, uint8_t col, uint8_t line);
void oled_prints(const char* s, uint8_t col, uint8_t line);
void oled_printf(const char* format, ...);

void oled_drawPixel(uint8_t x, uint8_t y);

#endif	/* OLED_H */

