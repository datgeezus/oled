#include <stdint.h>
#include "configbits.h"
#include "sysconfig.h"
#include <libpic30.h>
#include "oled/oled.h"

void move(uint8_t* x, uint8_t* y, uint8_t* dx, uint8_t* dy);
void bounce(uint8_t* x, uint8_t* y, uint8_t* dx, uint8_t* dy);

int main(void)
{
    sys_init();
    oled_init();

    // Initial parameters
    uint8_t x = OLED_WIDTH / 2;     // x initial position
    uint8_t y = OLED_HEIGHT / 2;    // y initial position
    uint8_t dx = 1;                 // x speed
    uint8_t dy = 1;                 // y speed

    //
    oled_clearDisplay();
    oled_drawPixel(x,y);
    oled_render();
    __delay_ms(2000);

    while(1)
    {
        LED ^= 1;
        oled_clearDisplay();
        move(&x, &y, &dx, &dy);
        oled_render();
        __delay_ms(16);
    }
    return (0);
}

void move(uint8_t* x, uint8_t* y, uint8_t* dx, uint8_t* dy)
{
    *x += *dx;
    *y += *dy;

    // Bounce off edges
    bounce(x, y, dx, dy);

    // Update pixel position
    oled_drawPixel(*x, *y);
}
void bounce(uint8_t* x, uint8_t* y, uint8_t* dx, uint8_t* dy)
{
    if ( (*x >= OLED_WIDTH) || *x <= 1)         // bounce horizontally
        *dx *= -1;
    else if ((*y >= OLED_HEIGHT) || *y <= 1)    // bounce vertically
        *dy *= -1;
}
