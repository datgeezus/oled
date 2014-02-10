#include "oled.h"           // main functions
#include "oled_print.h"     // print functions
#include "oled_draw.h"      // draw functions
#include "SSD1306.h"        // hardware driver functions
#include "../globals.h"   // __delay_ms() needs FCY defined
#include <libpic30.h>       // __delay_ms()
#include "string.h"         // memset()
#include "../pinconfig.h"
#include <stdio.h>


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


/* Private variables **********************************************************/
static uint8_t printBuffer[OLED_BUFFSIZE] = {0};
// Display buffer
static uint8_t buffer[OLED_BUFFSIZE] = {0};


/* Private functions **********************************************************/
static void oled_config(void);

/* Main functions *************************************************************/
void oled_config(void)
{
    OLED_CS_TRS = 0;     // CS as output
    OLED_RST_TRS = 0;    // RST as output
    OLED_DC_TRS = 0;     // CD as output

    // Configure SPI1
    ssd1306_init();
}

void oled_init(void)
{
    oled_config();      // hardware config
    oled_reset();       // display config
}

void oled_reset(void)
{
    // Reset
    OLED_RST = 1;
    __delay_ms(1);
    OLED_RST = 0;
    __delay_ms(10);
    OLED_RST = 1;

    // Init sequence for 128x64 OLED module taken from
    // page 64 of SSD1306 datasheet
    ssd1306cmd_displayOnOff(DISPLAY_OFF);               // 0xAE
    ssd1306cmd_displayMultiplexRatio(0x3F);             // 0xA8, 0x3F
    ssd1306cmd_displayOffset(0);                        // 0xD3, 0x00
    ssd1306cmd_displayStartLine(0);                     // 0x40, 0x00
    ssd1306cmd_displaySegmentRemap(ADDR_127);           // 0xA1
    ssd1306cmd_displayComDirection(COM_REMAPPED);       // 0xC8
    ssd1306cmd_displayComPins(COM_SEQUENTIAL_ENABLE_COM_REMAP);  // 0xDA, 0x02
    ssd1306cmd_contrast(0x7F);                          // 0x81, 0x7F
    ssd1306cmd_entireDisplayOn(RESUME_TO_RAM);          // 0xA4
    ssd1306cmd_displayNormalInverse(DISPLAY_NORMAL);    // 0xA6
    ssd1306cmd_setClock(0x08, 0x00);                    // 0xD5, 0x80
    ssd1306cmd_chargePump(CHARGE_ENABLE);               // 0x8D, 0x14
    ssd1306cmd_addrMemoryAddressingMode(MODE_HORIZONTAL);    // 0x20, 0x00
    ssd1306cmd_displayOnOff(DISPLAY_ON);                // 0xAF
}

void oled_render(void)
{
    ssd1306cmd_addrColumnAddress(0, OLED_LAST_COL);
    ssd1306cmd_addrPageAddress(0, OLED_LAST_PAGE);
    ssd1306_send(buffer, OLED_BUFFSIZE);
}

void oled_clearDisplay(void)
{
    memset(buffer, 0, OLED_BUFFSIZE);
}

/* Print functions ************************************************************/
void oled_printc(uint8_t col, uint8_t line, char c)
{
    // Check for a valid line [1 to 8]
    if (line < 0 || line > OLED_NPAGES)
        return;

    // to ease further computations, send values with 0 index
    oled_putc(buffer, c, --col, --line);
}

void oled_prints(uint8_t col, uint8_t line, const char* s)
{
    uint8_t sLen = strlen(s);
    if((sLen + CHAR_WIDTH) + col > OLED_WIDTH)
        return;

    oled_puts(buffer, s, --col, --line, sLen);
}

void oled_printf(uint8_t col, uint8_t line, const char* format, ...)
{
    char tempBuffer[OLED_WIDTH / CHAR_WIDTH];
    uint8_t maxCharCount = ((OLED_WIDTH / CHAR_WIDTH) - (CHAR_WIDTH * (col-1))) + 1;

    va_list  args;
    va_start(args, format);
    vsnprintf(tempBuffer, maxCharCount, format, args);    /* TODO: write custom vsprintf() */
//    sprintf(tempBuffer, format, args);

    uint8_t sLen = strlen(tempBuffer);
    oled_puts(buffer, tempBuffer, --col, --line, sLen);
    va_end(args);
}



/* Draw functions *************************************************************/
void oled_drawPixel(uint8_t x, uint8_t y)
{
    // Check for a valid position
    // x: [1 to 128]
    // y: [1 to 64]
    if(x < 1 || x > OLED_WIDTH || y < 1 || y > OLED_HEIGHT)
        return;

    // put pixel on buffer
    // to ease further computations, send values with 0 index
    oled_putPixel(buffer, --x, --y);
}
