 #ifndef USB_MSC_H
  #define USB_MSC_H
  // USB MSC INCLUDES
  #include <Arduino.h>
  #include <SPI.h>
  #include <SdFat.h>
  #include <Adafruit_SPIFlash.h>
  #include <Adafruit_TinyUSB.h>
  #include "../../filesystem/flash_config.h"
  // END USB MSC
  
  

  extern Adafruit_SPIFlash flash;
  extern FatVolume fatfs;
  extern Adafruit_USBD_MSC usb_msc;


#endif