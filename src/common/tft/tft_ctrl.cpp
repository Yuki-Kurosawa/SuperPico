#include "tft_ctrl.h"

#ifdef GFX_LIB_U8G2
  Adafruit_ST7735 tft=Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
  U8G2_FOR_ADAFRUIT_GFX u8g2;
#endif

#ifdef GFX_LIB_ESPI
  TFT_eSPI tft = TFT_eSPI();  
#endif

uint16_t bg = ST7735_BLACK;

void tft_init()
{
  #ifdef GFX_LIB_U8G2
    tft.initR(INITR_GREENTAB);
    tft.setRotation(2);
    tft.fillScreen(bg);

    u8g2.begin(tft);
    u8g2.setFontMode(0);
    u8g2.setFontDirection(0);
  #endif 

  #ifdef GFX_LIB_ESPI
    tft.begin();
    tft.fillScreen(bg);
    tft.setRotation(UP_SIDE);
    
  #endif

}

void tft_clean_all()
{
  tft.fillScreen(bg);
}

void tft_clean(int16_t x,int16_t y,int16_t w,int16_t h)
{
  if(!h && !w)
  {
    tft_clean_all();
  }
  else
  {
    tft.fillRect(x,y,w,h,bg);
  }
}

void tft_init_font(const uint8_t* font,uint16_t color)
{
  tft.loadFont(font);
  tft.setTextSize(1);
  tft.setTextColor(color);
}

void tft_print(const char* str,int16_t x,int16_t y,const uint8_t* font,uint16_t color)
{
  tft_init_font(font,color);  
  tft.setCursor(x,y);
  tft.println(str);
  tft.unloadFont();
}

void tft_print(int num,int16_t x,int16_t y,const uint8_t* font,uint16_t color)
{
  tft_init_font(font,color);  
  tft.setCursor(x,y);
  tft.println(num,DEC);
  tft.unloadFont();
}

void tft_clean_print(const char* str,int16_t x,int16_t y,const uint8_t* font,uint16_t color)
{
  tft_clean();
  tft_print(str,x,y,font,color);
}

void tft_drawrect(int16_t x,int16_t y,int16_t w,int16_t h,uint32_t color)
{
  tft.drawRect(x, y, w, h, color);
}

void tft_fillrect(int16_t x,int16_t y,int16_t w,int16_t h,uint32_t color)
{
  tft.fillRect(x, y, w, h, color);
}

