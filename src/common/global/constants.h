#ifndef CONSTANTS_H

  #define CONSTANTS_H

  #define CCS const static char

  #define CHINESE_FONT u8g2_font_unifont_t_chinese3
  #define JAPANESE_FONT u8g2_font_unifont_t_japanese3
  #define ENGLISH_FONT u8g2_font_unifont_te
  #define LANG zh

  #define SERIAL_ENABLED 0

  #define OVERCLOCK_SPI 0

  /* BEGIN SELECT GFX_LIB */
  //#define GFX_LIB_U8G2 1
  #define GFX_LIB_ESPI 1
  /* END SELECT GFX_LIB */

  //#define UP_SIDE_UP 0
  #define UP_SIDE_DOWN 2

  #ifdef UP_SIDE_UP
    #define UP_SIDE UP_SIDE_UP
  #endif

  #ifdef UP_SIDE_DOWN
    #define UP_SIDE UP_SIDE_DOWN
  #endif

  #define FONT_HEIGHT 16
  #define FONT_WIDTH 8

  #ifdef GFX_LIB_U8G2
    #define REAL_X(x) (x)
    #define REAL_Y(y) (y)
    #define X_FONT(x) (x * FONT_WIDTH) //non-ASCII sympols must be calculated as 2 chars 
    #define Y_FONT(y) ((y+1) * FONT_HEIGHT)
  #endif
  #ifdef GFX_LIB_ESPI
    #define REAL_X(x) (x)
    #define REAL_Y(y) (y)
    #ifdef UP_SIDE_UP
      #define OFFSET_X 0
      #define OFFSET_Y 0
    #endif
    #ifdef UP_SIDE_DOWN
      #define OFFSET_X 0
      #define OFFSET_Y 0
    #endif
    #define X_FONT(x) (x * FONT_WIDTH) + OFFSET_X //non-ASCII sympols must be calculated as 2 chars 
    #define Y_FONT(y) (y * FONT_HEIGHT) + OFFSET_Y
  #endif


  #define COL(x) X_FONT(x)
  #define ROW(y) Y_FONT(y)

#endif