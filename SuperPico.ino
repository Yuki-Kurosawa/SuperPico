#include "src/common/global/pico-ports.h"
#include "src/common/global/constants.h"
#include "src/common/tft/tft_ctrl.h"
#include "src/common/oc/overclock.h"
#include "src/common/io_out/print.h"
#include "src/components/boot_screen/boot_screen.h"

void setup() {  
  
  OverClockSPI();

  //float cpu=clock_get_hz(clk_sys)/1.0/MHZ;
  //float spi=clock_get_hz(clk_peri)/2.0/MHZ;

  init();
  boot_screen();

  
  
}

void loop() {
  
  //HERE

}


