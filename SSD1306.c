#include "SSD1306.h"
#include "spi/spi.h"
#include <stdint.h>         // fixed size types

/* Command talbe, page 28 of SSD1306 datasheet ********************************/
// Fundamental
#define SSD1306_SET_CONTRAST            0x81
#define SSD1306_ENTIRE_DISPLAYALL_ON    0xA4
#define SSD1306_NORM_INV_DISPLAY        0xA6
#define SSD1306_DISPLAY_ON_OFF          0xAE

// Scrolling
#define SSD1306_HORIZONTAL_SCROLL           0x26
#define SSD1306_VERTICAL_HORIZONTAL_SCROLL  0x29
#define SSD1306_DEACTIVATE_SCROLL           0x2E
#define SSD1306_ACTIVATE_SCROLL             0x2F
#define SSD1306_SET_VERTICAL_SCROLL_AREA    0xA3

// Address setting
#define SSD1306_SET_LOW_COLUMN          0x00
#define SSD1306_SET_HIGH_COLUMN         0x10
#define SSD1306_SET_MEMORY_MODE         0x20
#define SSD1306_SET_COLUMN_ADDR         0x21
#define SSD1306_SET_PAGE_ADDR           0x22
#define SSD1306_SET_PAGE_START_ADDR     0xB0

// Hardware configuration (Panel resolution and layout
#define SSD1306_SET_START_LINE          0x40
#define SSD1306_SET_SEGMENT_REMAP       0xA0
#define SSD1306_SET_MULTIPLEX           0xA8
#define SSD1306_COM_SCAN                0xC0
#define SSD1306_SET_DISPLAY_OFFSET      0xD3
#define SSD1306_SET_COM_PINS            0xDA

// Timing and driving scheme
#define SSD1306_SET_DISPLAY_CLOCK_DIV   0xD5
#define SSD1306_SET_PRECHARGE           0xD9
#define SSD1306_SET_VCOM_DESELECT       0xDB
#define SSD1306_NOP                     0xE3

// Charge Pump: page 62
#define SSD1306_CHARGE_PUMP             0x8D

/* Static functions ***********************************************************/
static void ssd1306_sendCMD(uint8_t* cmd, uint8_t cmdSize);

static void ssd1306_sendCMD(uint8_t* cmd, uint8_t cmdSize)
{
    uint8_t i;

    OLED_DC = 0;
    OLED_CS = 0;

    for (i = 0; i < cmdSize; i++, cmd++)
    {
        spiWrite(*cmd);
    }

    Nop();
    Nop();
    OLED_CS = 1;
}

void ssd1306_send(uint8_t* data, uint16_t dataSize)
{
    uint16_t i;

    OLED_DC = 1;
    OLED_CS = 0;

    for (i = 0; i < dataSize; i++, data++)
    {
        spiWrite(*data);
    }

    Nop();
    Nop();
    OLED_CS = 1;
}

/* Command functions **********************************************************/
void ssd1306cmd_contrast(uint8_t contrast)
{
    uint8_t cmd[] = {SSD1306_SET_CONTRAST, contrast};
    ssd1306_sendCMD(cmd, 2);
}

void ssd1306cmd_entireDisplayOn(uint8_t resume_on)
{
    uint8_t cmd[] = {SSD1306_ENTIRE_DISPLAYALL_ON | resume_on};
    ssd1306_sendCMD(cmd, 1);
}

void ssd1306cmd_displayNormalInverse(uint8_t norm_inv)
{
    uint8_t cmd[] = {SSD1306_NORM_INV_DISPLAY | norm_inv};
    ssd1306_sendCMD(cmd, 1);
}

void ssd1306cmd_displayOnOff(uint8_t on_off)
{
    uint8_t cmd[] = {SSD1306_DISPLAY_ON_OFF | on_off};
    ssd1306_sendCMD(cmd, 1);
}

void ssd1306cmd_scrollHorizontal(uint8_t dir, uint8_t start, uint8_t time, uint8_t end)
{
    uint8_t cmd[] = {(SSD1306_HORIZONTAL_SCROLL | dir), 0x00, start, time, end, 0x00, 0xFF};
    ssd1306_sendCMD(cmd, 7);
}
void ssd1306cmd_scrollVerticalAndHorizontal(uint8_t dir, uint8_t start, uint8_t time, uint8_t end, uint8_t offset)
{
    uint8_t cmd[] = {(SSD1306_VERTICAL_HORIZONTAL_SCROLL | dir), 0x00, start, time, end, offset};
    ssd1306_sendCMD(cmd, 7);
}
void ssd1306cmd_scrollOn(void)
{
    uint8_t cmd[] = {SSD1306_ACTIVATE_SCROLL};
    ssd1306_sendCMD(cmd, 1);
}
void ssd1306cmd_scrollOff(void)
{
    uint8_t cmd[] = {SSD1306_DEACTIVATE_SCROLL};
    ssd1306_sendCMD(cmd, 1);
}
void ssd1306cmd_scrollVerticalarea(uint8_t rowsFixed, uint8_t rowsScroll)
{
    uint8_t cmd[] = {SSD1306_SET_VERTICAL_SCROLL_AREA, rowsFixed, rowsScroll};
    ssd1306_sendCMD(cmd, 3);
}

void ssd1306cmd_addrLowerColumn(uint8_t lowerNibble)
{
    uint8_t cmd[] = { SSD1306_SET_LOW_COLUMN | (lowerNibble & 0x0F) };
    ssd1306_sendCMD(cmd, 1);
}
void ssd1306cmd_addrHigherColumn(uint8_t higherNibble)
{
    uint8_t cmd[] = { SSD1306_SET_HIGH_COLUMN | (higherNibble & 0x0F) };
    ssd1306_sendCMD(cmd, 1);
}
void ssd1306cmd_addrMemoryAddressingMode(uint8_t mode)
{
    uint8_t cmd[] = {SSD1306_SET_MEMORY_MODE, (mode & 0x02)};
    ssd1306_sendCMD(cmd, 2);
}
void ssd1306cmd_addrColumnAddress(uint8_t startAddress, uint8_t endAddress)
{
    uint8_t cmd[] = {SSD1306_SET_COLUMN_ADDR, (startAddress & 0x7F), (endAddress & 0x7F)};
    ssd1306_sendCMD(cmd, 3);
}
void ssd1306cmd_addrPageAddress(uint8_t startAddress, uint8_t endAddress)
{
    uint8_t cmd[] = {SSD1306_SET_PAGE_ADDR, (startAddress & 0x07), (endAddress & 0x07)};
    ssd1306_sendCMD(cmd, 3);
}
void ssd1306cmd_addrPageStartAddress(uint8_t startAddress)
{
    uint8_t cmd[] = {SSD1306_SET_PAGE_START_ADDR | startAddress};
    ssd1306_sendCMD(cmd, 1);
}

void ssd1306cmd_displayStartLine(uint8_t startLineReg)
{
    uint8_t cmd[] = {SSD1306_SET_START_LINE | startLineReg};
    ssd1306_sendCMD(cmd, 1);
}
void ssd1306cmd_displaySegmentRemap(uint8_t addr)
{
    uint8_t cmd[] = {SSD1306_SET_SEGMENT_REMAP | addr};
    ssd1306_sendCMD(cmd, 1);
}
void ssd1306cmd_displayMultiplexRatio(uint8_t ratio)
{
    uint8_t cmd[] = {SSD1306_SET_MULTIPLEX, (ratio & 0x3F)};
    ssd1306_sendCMD(cmd, 2);
}
void ssd1306cmd_displayComDirection(uint8_t dir)
{
    uint8_t cmd[] = {SSD1306_COM_SCAN | dir};
    ssd1306_sendCMD(cmd, 1);
}
void ssd1306cmd_displayOffset(uint8_t offset)
{
    uint8_t cmd[] = {SSD1306_SET_DISPLAY_OFFSET, (offset & 0x3F)};
    ssd1306_sendCMD(cmd, 2);
}
void ssd1306cmd_displayComPins(uint8_t config)
{
    uint8_t cmd[] = {SSD1306_SET_COM_PINS, config};
    ssd1306_sendCMD(cmd, 2);
}

void ssd1306cmd_setClock(uint8_t ratio, uint8_t freq)
{
    uint8_t cmd[] = {SSD1306_SET_DISPLAY_CLOCK_DIV, ((ratio << 4) | freq)};
    ssd1306_sendCMD(cmd, 2);
}
void ssd1306cmd_setPrechargePeriod(uint8_t phase)
{
    uint8_t cmd[] = {SSD1306_SET_PRECHARGE, phase};
    ssd1306_sendCMD(cmd, 2);
}
void ssd1306cmd_setVDeselect(uint8_t level)
{
    uint8_t cmd[] = {SSD1306_SET_VCOM_DESELECT, level};
    ssd1306_sendCMD(cmd, 2);
}
void ssd1306cmd_nop(void)
{
    uint8_t cmd[] = {SSD1306_NOP};
    ssd1306_sendCMD(cmd, 1);
}

void ssd1306cmd_chargePump(uint8_t arg)
{
    uint8_t cmd[] = {SSD1306_CHARGE_PUMP ,arg};
    ssd1306_sendCMD(cmd, 2);
}

void ssd1306_config()
{
    spiConfigPins();
    spiConfig();
}