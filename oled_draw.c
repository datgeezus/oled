#include "oled/oled_draw.h"
#include "oled/oled.h"

void oled_putPixel(uint8_t* buffer, uint8_t x, uint8_t y)
{
//    buffer[x + ((y / 8) * OLED_WIDTH)] = (1 << (y % 8));
    buffer[x + ((y >> 3) * OLED_WIDTH)] |= (1 << (y & 7));
}
