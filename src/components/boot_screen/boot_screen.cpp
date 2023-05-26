#include "boot_screen.h"
#include "../../common/str_stor/stor.h"


bool boot_screen() {

  tft_clean();
  delay(1000);

  print(STR_BOARD_NAME, COL(0), ROW(0));
  print(STR_BOARD_VERSION,COL(0),ROW(1));

  print(STR_BOARD_BOOTING,COL(4.5),ROW(5));
  tft_drawrect(14, ROW(7), 100, 16);

  delay(1000);

  // for(int i=0;i<=100;i++)
  // {
  //   tft_fillrect(14, ROW(7), i, 16);
  //   delay(100);
  // }

  bool fm=flash_mount();
  if(!fm)
  {
    bool ff=flash_format();
    fm=flash_mount();

    if(!fm) return false;
  }

  flash_usb_mount();

  return true;
}
