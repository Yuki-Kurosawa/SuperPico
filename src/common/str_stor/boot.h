#include "../global/constants.h"

#ifndef BOOT_STOR_H
#define BOOT_STOR_H

CCS* STR_BOARD_NAME PROGMEM = "SUPERPICO HX";
CCS* STR_BOARD_VERSION PROGMEM = "Ver 1.00";
CCS* STR_PREPARE_BOOT PROGMEM = "STEP 1\nPrepare to boot";
CCS* STR_MOUNT PROGMEM = "STEP 2\nMounting Filesystem";
CCS* STR_FORMAT_NEW PROGMEM = "STEP 3\nCreating New Filesystem";
CCS* STR_MOUNT_NEW PROGMEM = "STEP 4\nMounting New Filesystem";
CCS* STR_PREPARE_FINISH PROGMEM = "STEP 5\nStarting Program";

#endif