#ifndef PICO_PORTS_H

  #define PICO_PORTS_H
  #define PICO_LCD_144
  #define PICO_UPS_B
  #define PICO_RTC_DS2321

  #ifdef PICO_LCD_144
    #define PICO_LCD_DC 8
    #define PICO_LCD_CS 9
    #define PICO_LCD_CLK 10
    #define PICO_LCD_SCLK PICO_LCD_CLK
    #define PICO_LCD_DIN 11
    #define PICO_LCD_MOSI PICO_LCD_DIN
    #define PICO_LCD_RST 12
    #define PICO_LCD_BL 13
    #define PICO_LCD_KEY0 15
    #define PICO_LCD_KEY1 17
    #define PICO_LCD_KEY2 2
    #define PICO_LCD_KEY3 3
  #endif

  #ifdef PICO_UPS_B
    #define PICO_UPS_SDA 6
    #define PICO_UPS_SCL 7
  #endif

  #ifdef PICO_RTC_DS2321
    #define PICO_RTC_SDA 20
    #define PICO_RTC_SCL 21
  #endif


#endif