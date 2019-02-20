/*
 * NHD-24-240320.c
 *
 *  Created on: Jan 24, 2019
 *      Author: Alex
 */

#include "NHD-24-240320.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_dma.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdlib.h"

void TFT_Config_Pins()
{
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

	// Config CS
	LL_GPIO_SetPinMode(LCD_PORT_CS, LCD_PIN_CS, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_CS, LCD_PIN_CS, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_CS, LCD_PIN_CS, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_CS, LCD_PIN_CS, LL_GPIO_PULL_UP);

	// Config DC
	LL_GPIO_SetPinMode(LCD_PORT_DC, LCD_PIN_DC, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_DC, LCD_PIN_DC, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_DC, LCD_PIN_DC, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_DC, LCD_PIN_DC, LL_GPIO_PULL_UP);

	// Config WR
	LL_GPIO_SetPinMode(LCD_PORT_WR, LCD_PIN_WR, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_WR, LCD_PIN_WR, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_WR, LCD_PIN_WR, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_WR, LCD_PIN_WR, LL_GPIO_PULL_UP);

	// Config RD
	LL_GPIO_SetPinMode(LCD_PORT_RD, LCD_PIN_RD, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_RD, LCD_PIN_RD, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_RD, LCD_PIN_RD, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_RD, LCD_PIN_RD, LL_GPIO_PULL_UP);

	// Config RES
	LL_GPIO_SetPinMode(LCD_PORT_RES, LCD_PIN_RES, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_RES, LCD_PIN_RES, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_RES, LCD_PIN_RES, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_RES, LCD_PIN_RES, LL_GPIO_PULL_UP);

	// Config Data pins
	LL_GPIO_SetPinMode(LCD_PORT_DATA, LCD_PIN_DB8, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_DATA, LCD_PIN_DB8, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_DATA, LCD_PIN_DB8, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_DATA, LCD_PIN_DB8, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(LCD_PORT_DATA, LCD_PIN_DB9, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_DATA, LCD_PIN_DB9, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_DATA, LCD_PIN_DB9, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_DATA, LCD_PIN_DB9, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(LCD_PORT_DATA, LCD_PIN_DB10, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_DATA, LCD_PIN_DB10, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_DATA, LCD_PIN_DB10, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_DATA, LCD_PIN_DB10, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(LCD_PORT_DATA, LCD_PIN_DB11, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_DATA, LCD_PIN_DB11, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_DATA, LCD_PIN_DB11, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_DATA, LCD_PIN_DB11, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(LCD_PORT_DATA, LCD_PIN_DB12, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_DATA, LCD_PIN_DB12, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_DATA, LCD_PIN_DB12, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_DATA, LCD_PIN_DB12, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(LCD_PORT_DATA, LCD_PIN_DB13, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_DATA, LCD_PIN_DB13, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_DATA, LCD_PIN_DB13, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_DATA, LCD_PIN_DB13, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(LCD_PORT_DATA, LCD_PIN_DB14, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_DATA, LCD_PIN_DB14, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_DATA, LCD_PIN_DB14, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_DATA, LCD_PIN_DB14, LL_GPIO_PULL_UP);

	LL_GPIO_SetPinMode(LCD_PORT_DATA, LCD_PIN_DB15, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinSpeed(LCD_PORT_DATA, LCD_PIN_DB15, LL_GPIO_SPEED_FREQ_HIGH);
	LL_GPIO_SetPinOutputType(LCD_PORT_DATA, LCD_PIN_DB15, LL_GPIO_OUTPUT_PUSHPULL);
	LL_GPIO_SetPinPull(LCD_PORT_DATA, LCD_PIN_DB15, LL_GPIO_PULL_UP);
}

void TFT_24_7789_Write_Cmd(uint8_t command)
{
	LL_GPIO_ResetOutputPin(LCD_PORT_CS, LCD_PIN_CS);
	LL_GPIO_ResetOutputPin(LCD_PORT_DC, LCD_PIN_DC);
	LL_GPIO_SetOutputPin(LCD_PORT_RD, LCD_PIN_RD);
	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

	uint32_t n = LL_GPIO_ReadOutputPort(LCD_PORT_DATA);
	n &= 0x000000FF;
	n |= (command << 8);
	LL_GPIO_WriteOutputPort(LCD_PORT_DATA, n);
	LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	//vTaskDelay(1);
}

void TFT_24_7789_Write_Data(uint8_t data)
{
	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

	uint32_t n = LL_GPIO_ReadOutputPort(LCD_PORT_DATA);
	n &= 0x000000FF;
	n |= (data << 8);
	LL_GPIO_WriteOutputPort(LCD_PORT_DATA, n);

	LL_GPIO_SetOutputPin(LCD_PORT_DC, LCD_PIN_DC);
	LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	//vTaskDelay(1);
}

void TFT_Init(void)
{
	LL_GPIO_ResetOutputPin(LCD_PORT_CS, LCD_PIN_CS);
	LL_GPIO_SetOutputPin(LCD_PORT_RD, LCD_PIN_RD);
	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	LL_GPIO_ResetOutputPin(LCD_PORT_RES, LCD_PIN_RES);
	vTaskDelay(10);
	LL_GPIO_SetOutputPin(LCD_PORT_RES, LCD_PIN_RES);
	vTaskDelay(10);

	TFT_24_7789_Write_Cmd(SWRESET);
	vTaskDelay(10);
	TFT_24_7789_Write_Cmd(SLPOUT);	// Exit SLEEP mode
	//TFT_24_7789_Write_Cmd(MADCTL);
	//TFT_24_7789_Write_Data(0x08);	// MADCTL: memory data access control
	TFT_24_7789_Write_Cmd(COLMOD);
	TFT_24_7789_Write_Data(0x05);	// COLMOD: Interface Pixel format


	/*TFT_24_7789_Write_Cmd(0x53);
	TFT_24_7789_Write_Data(0x24);
	TFT_24_7789_Write_Cmd(0x51);
		TFT_24_7789_Write_Data(0xFF);*/

	/*TFT_24_7789_Write_Cmd(0xB2);
	TFT_24_7789_Write_Data(0x0C);
	TFT_24_7789_Write_Data(0x0C);
	TFT_24_7789_Write_Data(0x00);
	TFT_24_7789_Write_Data(0x33);
	TFT_24_7789_Write_Data(0x33);	// PORCTRK: Porch setting
	TFT_24_7789_Write_Cmd(0xB7);
	TFT_24_7789_Write_Data(0x35);	// GCTRL: Gate Control
	TFT_24_7789_Write_Cmd(0xBB);
	TFT_24_7789_Write_Data(0x2B);	// VCOMS: VCOM setting
	TFT_24_7789_Write_Cmd(0xC0);
	TFT_24_7789_Write_Data(0x2D);	// LCMCTRL: LCM Control
	TFT_24_7789_Write_Cmd(0xC2);
	TFT_24_7789_Write_Data(0x01);
	TFT_24_7789_Write_Data(0xFF);	// VDVVRHEN: VDV and VRH Command Enable
	TFT_24_7789_Write_Cmd(0xC3);
	TFT_24_7789_Write_Data(0x11);	// VRHS: VRH Set
	TFT_24_7789_Write_Cmd(0xC4);
	TFT_24_7789_Write_Data(0x20);	// VDVS: VDV Set

	TFT_24_7789_Write_Cmd(0xC6);
	TFT_24_7789_Write_Data(0x0F);	// FRCTRL2: Frame Rate control in normal

	TFT_24_7789_Write_Cmd(0xA1);
	TFT_24_7789_Write_Data(0xA4);
	TFT_24_7789_Write_Data(0xA1);*/	// PWCTRL1: Power Control 1

	vTaskDelay(10);
	//TFT_24_7789_Write_Cmd(0x13);
	TFT_24_7789_Write_Cmd(0x29);

	vTaskDelay(10);

	TFT_Clear(WHITE);
}

void TFT_SetOrientation(uint8_t degrees)
{
    uint8_t arg;
    switch (degrees)
    {
        case ORIENTATION_0: arg = 0x00; break;
        case ORIENTATION_90: arg = 0x60; break;
        case ORIENTATION_180: arg = 0xC0; break;
        case ORIENTATION_270: arg = 0xA0; break;
        case ORIENTATION_MY: arg = 0x80; break;	// BMP mirror Y-axis
        case ORIENTATION_MX: arg = 0x20; break;	// BMP mirror Y-axis
        default: arg = 0x00; break;
    }
    TFT_24_7789_Write_Cmd(MADCTL);
    TFT_24_7789_Write_Data(arg);
}

void TFT_SetAddrWindow(const uint16_t x0, const uint16_t y0, const uint16_t x1, const uint16_t y1)
{
	TFT_24_7789_Write_Cmd(CASET);
	TFT_24_7789_Write_Data((uint8_t)(x0 >> 8));
	TFT_24_7789_Write_Data((uint8_t)x0);
	TFT_24_7789_Write_Data((uint8_t)(x1 >> 8));
	TFT_24_7789_Write_Data((uint8_t)x1);	// X address set

	TFT_24_7789_Write_Cmd(RASET);
	TFT_24_7789_Write_Data((uint8_t)(y0 >> 8));
	TFT_24_7789_Write_Data((uint8_t)y0);
	TFT_24_7789_Write_Data((uint8_t)(y1 >> 8));
	TFT_24_7789_Write_Data((uint8_t)y1);	// Y address set

	TFT_24_7789_Write_Cmd(RAMWR);
}

void TFT_Clear(uint16_t color)
{
	taskENTER_CRITICAL();

	TFT_SetAddrWindow(0, 0, LCDMAXWIDTH, LCDMAXHEIGHT);

	LL_GPIO_SetOutputPin(LCD_PORT_DC, LCD_PIN_DC);
	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	vTaskDelay(10);

	// Only reads the GPIO once. Could be a problem in RTOS
	uint32_t n = LL_GPIO_ReadOutputPort(LCD_PORT_DATA);
	n &= 0xFFFF00FF;

	uint32_t color2 = ((color & 0x000000FF) << 8) | n;
	uint32_t color1 = (color & 0x0000FF00) | n;

	for (int i = 0; i < LCDWIDTH*LCDHEIGHT; ++i) {
		LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
		LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color1);
		LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

		// Required for optimization to work
		__ASM volatile ("nop");

		LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
		LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color2);
		LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	}
	taskEXIT_CRITICAL();
}

void TFT_DrawPixel(uint16_t x, uint16_t y, uint16_t color)
{
	TFT_SetAddrWindow(x, y, x, y);

	LL_GPIO_SetOutputPin(LCD_PORT_DC, LCD_PIN_DC);
	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	//vTaskDelay(1);

	uint32_t n = LL_GPIO_ReadOutputPort(LCD_PORT_DATA);
	n &= 0xFFFF00FF;
	uint32_t color2 = ((color & 0x000000FF) << 8) | n;
	uint32_t color1 = (color & 0x0000FF00) | n;

	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color1);
	LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

	// Required for optimization to work
	__ASM volatile ("nop");

	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color2);
	LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
}

void TFT_FillRect(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    uint16_t width = x1-x0+1;
    uint16_t height = y1-y0+1;
	TFT_SetAddrWindow(x0, y0, x1, y1);

	LL_GPIO_SetOutputPin(LCD_PORT_DC, LCD_PIN_DC);
	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

	uint32_t n = LL_GPIO_ReadOutputPort(LCD_PORT_DATA);
	n &= 0xFFFF00FF;

	uint32_t color2 = ((color & 0x000000FF) << 8) | n;
	uint32_t color1 = (color & 0x0000FF00) | n;

	for (int i = 0; i < width*height; ++i) {
		LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
		LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color1);
		LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

		// Required for optimization to work
		__ASM volatile ("nop");

		LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
		LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color2);
		LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	}
}

void TFT_DrawHLine(uint16_t x0, uint16_t x1, uint16_t y, uint16_t color)
{
	uint16_t width = x1-x0+1;
	TFT_SetAddrWindow(x0, y, x1, y);

	LL_GPIO_SetOutputPin(LCD_PORT_DC, LCD_PIN_DC);
	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

	uint32_t n = LL_GPIO_ReadOutputPort(LCD_PORT_DATA);
	n &= 0xFFFF00FF;

	uint32_t color2 = ((color & 0x000000FF) << 8) | n;
	uint32_t color1 = (color & 0x0000FF00) | n;

	for (int i = 0; i < width; ++i) {
		LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
		LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color1);
		LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

		// Required for optimization to work
		__ASM volatile ("nop");

		LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
		LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color2);
		LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	}
}

void TFT_DrawVLine(uint16_t x, uint16_t y0, uint16_t y1, uint16_t color)
{
    uint16_t height = y1-y0+1;
	TFT_SetAddrWindow(x, y0, x, y1);

	LL_GPIO_SetOutputPin(LCD_PORT_DC, LCD_PIN_DC);
	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

	uint32_t n = LL_GPIO_ReadOutputPort(LCD_PORT_DATA);
	n &= 0xFFFF00FF;

	uint32_t color2 = ((color & 0x000000FF) << 8) | n;
	uint32_t color1 = (color & 0x0000FF00) | n;

	for (int i = 0; i < height; ++i) {
		LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
		LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color1);
		LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

		// Required for optimization to work
		__ASM volatile ("nop");

		LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
		LL_GPIO_WriteOutputPort(LCD_PORT_DATA, color2);
		LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
	}
}

void TFT_DrawLine(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    for(;;) {
        TFT_DrawPixel(x0, y0, color);
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void TFT_LCD_putCh(char ch, uint16_t x, uint16_t y, uint16_t color, uint16_t bgcolor)
{
    // Write a character is 6x7

    uint8_t row, col, bit, data, mask = 0x01;
    TFT_SetAddrWindow(x, y, x+4, y+6);

	LL_GPIO_SetOutputPin(LCD_PORT_DC, LCD_PIN_DC);
	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

    uint32_t n = LL_GPIO_ReadOutputPort(LCD_PORT_DATA);
	n &= 0xFFFF00FF;
    uint32_t fcolor2 = ((color & 0x000000FF) << 8) | n;
	uint32_t fcolor1 = (color & 0x0000FF00) | n;
	uint32_t bcolor2 = ((bgcolor & 0x000000FF) << 8) | n;
	uint32_t bcolor1 = (bgcolor & 0x0000FF00) | n;

    for (row = 0; row < 7; ++row)
    {
        for (col = 0; col < 5; ++col)
        {
            data = (FONT_CHARS[ch-32][col]);
            bit = data & mask;
            if (bit == 0) {
            	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
				LL_GPIO_WriteOutputPort(LCD_PORT_DATA, bcolor1);
				LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

				// Required for optimization to work
				__ASM volatile ("nop");

				LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
				LL_GPIO_WriteOutputPort(LCD_PORT_DATA, bcolor2);
				LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
            }
            else {
            	LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
				LL_GPIO_WriteOutputPort(LCD_PORT_DATA, fcolor1);
				LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);

				// Required for optimization to work
				__ASM volatile ("nop");

				LL_GPIO_ResetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
				LL_GPIO_WriteOutputPort(LCD_PORT_DATA, fcolor2);
				LL_GPIO_SetOutputPin(LCD_PORT_WR, LCD_PIN_WR);
            }
        }
        mask <<= 1;
    }
}

void TFT_DrawString(const char *str, uint16_t x, uint16_t y, uint16_t color)
{
    uint16_t xt = x;
    uint8_t strindex = 0;
    while(str[strindex] != '\0') {
        TFT_LCD_putCh(str[strindex], xt, y, color, WHITE);
        xt += 6;
        ++strindex;
    }
}

void TFT_DrawInt(uint16_t num, uint8_t numdigits, uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t xt = x + 18;
    char ch;
    while(numdigits-- > 0) {
        ch = num % 10;
        TFT_LCD_putCh(ch + 48, xt, y, color, WHITE);
        xt -= 6;
        num /= 10;
    }
}

void TFT_DrawFloat(double f, uint16_t x, uint16_t y, uint16_t color)
{
    uint8_t i;
    uint16_t temp = 100;
    uint16_t xt = x;
    if (f < 0) {
        TFT_LCD_putCh('-', xt, y, color, WHITE);
        xt += 6;
        f *= -1;
    } else {
        TFT_LCD_putCh(' ', xt, y, color, WHITE);
        xt += 6;
    }
    for (i = 0; i < 3; ++i) {
    	TFT_LCD_putCh(((int)(f / temp) % 10) + 48, xt, y, color, WHITE);
        xt += 6;
        temp /= 10;
    }
    TFT_LCD_putCh('.', xt, y, color, WHITE);
    xt += 6;
    temp = 10;
    for (i = 0; i < 4; ++i) {
    	TFT_LCD_putCh(((uint32_t)(f * temp) % 10) + 48, xt, y, color, WHITE);
        xt += 6;
        temp *= 10;
    }
}

uint16_t TFT_RGBto16Bit(uint8_t r, uint8_t g, uint8_t b)
{
	// R <= 32 (5bit), G <= 64 (6bit), B <= 32 (5bit)
	return( (r << 11) | (g << 5) | (b));
}
