#include "boot_screen.h"
#include "../../common/str_stor/stor.h"


bool boot_screen() {

  tft_clean();
  delay(1000);

  print(STR_BOARD_NAME, COL(0), ROW(0));
  print(STR_BOARD_VERSION,COL(0),ROW(1));

  print(STR_PREPARE_BOOT,COL(0),ROW(4));
  delay(1000);

  tft_clean(COL(0),ROW(3),128,64);
  print(STR_MOUNT,COL(0),ROW(4));
  bool fm=flash_mount();
  delay(1000);

  if(!fm)
  {
    tft_clean(COL(0),ROW(3),FONT_WIDTH*16,FONT_HEIGHT*4);
    print(STR_FORMAT_NEW,COL(0),ROW(4));
    delay(1000);
    bool ff=flash_format();
    delay(1000);
    
    tft_clean(COL(0),ROW(3),FONT_WIDTH*16,FONT_HEIGHT*4);
    print(STR_MOUNT_NEW,COL(0),ROW(4));
    fm=flash_mount();
    delay(1000);

    if(!fm) return false;
    
  }

  tft_clean(COL(0),ROW(3),FONT_WIDTH*16,FONT_HEIGHT*4);
  print(STR_PREPARE_FINISH,COL(0),ROW(4));
  delay(1000);

  //flash_usb_mount();

  return true;
}
