/* 
 * File:   SSD1306.h
 * Author: jesus
 *
 * Created on January 28, 2014, 7:48 PM
 */

#ifndef SSD1306_H
#define	SSD1306_H

#include <stdint.h>

/* Fundamental ****************************************************************/
// Entire Display ON
#define RESUME_TO_RAM       0
#define ENTIRE_DISPLAY_ON   1
// Set normal/inverse display
#define DISPLAY_NORMAL      0
#define DISPLAY_INVERSE     1
// Set Display ON/OFF
#define DISPLAY_OFF         0
#define DISPLAY_ON          1

/* Scrolling ******************************************************************/
// Continuous horizontal scrolling
#define SCROLL_RIGHT        0
#define SCROLL_LEFT         1
// Continuous vertical and horizontal scrolling
#define SCROLL_DIAG_RIGHT   0x01
#define SCROLL_DIAG_LEFT    0x02

/* Addressing *****************************************************************/
// Set memory addressing mode
#define MODE_HORIZONTAL     0x00
#define MODE_VERTICAL       0x01
#define MODE_PAGE           0x02

/* Hardware configuration *****************************************************/
// Set segment remap
#define ADDR_0              0
#define ADDR_127            1
// Set COM output scan direction
#define COM_NORMAL          0
#define COM_REMAPPED        0x08
// Set COM pins hardware configuration
#define COM_SEQUENTIAL_DISABLE_COM_REMAP    0x02
#define COM_SEQUENTIAL_ENABLE_COM_REMAP     0x12
#define COM_ALTERNATIVE__DISABLE_COM_REMAP  0x22
#define COM_ALTERNATIVE__ENABLE_COM_REMAP   0x32
// Set V_comh Deselect
#define LEVEL_0_65V         0x00
#define LEVEL_0_77V         0x20
#define LEVEL_0_83V         0x30

/* Charge Pump ****************************************************************/
#define CHARGE_DISABLE      0x10
#define CHARGE_ENABLE        0x14


void ssd1306cmd_contrast(uint8_t contrast);
void ssd1306cmd_entireDisplayOn(uint8_t resume_on);
void ssd1306cmd_displayNormalInverse(uint8_t norm_inv);
void ssd1306cmd_displayOnOff(uint8_t on_off);

void ssd1306cmd_scrollHorizontal(uint8_t dir, uint8_t start, uint8_t time, uint8_t end);
void ssd1306cmd_scrollVerticalAndHorizontal(uint8_t dir, uint8_t start, uint8_t time, uint8_t end, uint8_t offset);
void ssd1306cmd_scrollOn(void);
void ssd1306cmd_scrollOff(void);
void ssd1306cmd_scrollVerticalarea(uint8_t fixed, uint8_t scroll);

void ssd1306cmd_addrLowerColumn(uint8_t lowerNibble);
void ssd1306cmd_addrHigherColumn(uint8_t higherNibble);
void ssd1306cmd_addrMemoryAddressingMode(uint8_t mode);
void ssd1306cmd_addrColumnAddress(uint8_t startAddress, uint8_t endAddress);
void ssd1306cmd_addrPageAddress(uint8_t startAddress, uint8_t endAddress);
void ssd1306cmd_addrPageStartAddress(uint8_t startAddress);

void ssd1306cmd_displayStartLine(uint8_t startLineReg);
void ssd1306cmd_displaySegmentRemap(uint8_t addr);
void ssd1306cmd_displayMultiplexRatio(uint8_t ratio);
void ssd1306cmd_displayComDirection(uint8_t dir);
void ssd1306cmd_displayOffset(uint8_t offset);
void ssd1306cmd_displayComPins(uint8_t config);

void ssd1306cmd_setClock(uint8_t ratio, uint8_t freq);
void ssd1306cmd_setPrechargePeriod(uint8_t phase);
void ssd1306cmd_setVDeselect(uint8_t level);
void ssd1306cmd_nop(void);

void ssd1306cmd_chargePump(uint8_t arg);

void ssd1306_config();
void ssd1306_send(uint8_t* data, uint16_t dataSize);

#endif	/* SSD1306_H */

