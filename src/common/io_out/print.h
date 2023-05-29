#include "../tft/tft_ctrl.h"

#ifndef PRINT_H
  #define PRINT_H
  void init();
  void print(const char* str,int16_t x,int16_t y,const uint8_t* font=unifont_en,uint16_t color=ST7735_WHITE);
  void print(int num,int16_t x,int16_t y,const uint8_t* font=unifont_en,uint16_t color=ST7735_WHITE);
#endif