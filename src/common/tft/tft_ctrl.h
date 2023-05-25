#include "../global/constants.h"
#include "../global/libs.h"
#include "../global/pico-ports.h"


#ifndef TFT_CTRL_H
  #define TFT_CTRL_H

  #ifdef GFX_LIB_U8G2

    #define TFT_CS         PICO_LCD_CS
    #define TFT_RST        PICO_LCD_RST
    #define TFT_DC       PICO_LCD_DC
    #define TFT_MOSI      PICO_LCD_MOSI
    #define TFT_SCLK       PICO_LCD_SCLK

    extern Adafruit_ST7735 tft;
    extern U8G2_FOR_ADAFRUIT_GFX u8g2;
  #endif

  #ifdef GFX_LIB_ESPI
    extern TFT_eSPI tft;
  #endif

  void tft_init();
  void tft_clean_all();
  void tft_clean(int16_t x=0,int16_t y=0,int16_t w=0,int16_t h=0);
  void tft_print(const char* str,int16_t x,int16_t y,const uint8_t* font=unifont_en,uint16_t color=ST7735_WHITE);
  void tft_drawrect(int16_t x,int16_t y,int16_t w,int16_t h,uint32_t color=ST7735_YELLOW);
  void tft_fillrect(int16_t x,int16_t y,int16_t w,int16_t h,uint32_t color=ST7735_YELLOW);
#endif