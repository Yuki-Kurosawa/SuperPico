#ifndef LIBS_H
 #define LIBS_H
  #ifdef GFX_LIB_U8G2
    #include <Adafruit_GFX.h> 
    #include <Adafruit_ST7735.h> 
    #include <U8g2_for_Adafruit_GFX.h>
  #endif

  #ifdef GFX_LIB_ESPI
    #include "../../fonts/unifont_jp.h"
    #include "../../fonts/unifont_cn.h"
    #include "../../fonts/unifont_en.h"
    #include <TFT_eSPI.h>
  #endif

  #include <TinyMenu.h>
 
#endif