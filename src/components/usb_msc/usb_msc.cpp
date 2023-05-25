#include "usb_msc.h"
#include "usb_msc_func.h"
#include "../../common/str_stor/fs.h"
#include "../../common/device/device.h"

#include "../../filesystem/ff.h"
#include "../../filesystem/diskio.h"


Adafruit_SPIFlash flash(&flashTransport);
FatVolume fatfs;
Adafruit_USBD_MSC usb_msc;

#pragma region FatFS

DSTATUS disk_status ( BYTE pdrv )
{
  (void) pdrv;
	return 0;
}

DSTATUS disk_initialize ( BYTE pdrv )
{
  (void) pdrv;
	return 0;
}

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
  (void) pdrv;
	return flash.readBlocks(sector, buff, count) ? RES_OK : RES_ERROR;
}

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
  (void) pdrv;
  return flash.writeBlocks(sector, buff, count) ? RES_OK : RES_ERROR;
}

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
  (void) pdrv;

  switch ( cmd )
  {
    case CTRL_SYNC:
      flash.syncBlocks();
      return RES_OK;

    case GET_SECTOR_COUNT:
      *((DWORD*) buff) = flash.size()/512;
      return RES_OK;

    case GET_SECTOR_SIZE:
      *((WORD*) buff) = 512;
      return RES_OK;

    case GET_BLOCK_SIZE:
      *((DWORD*) buff) = 8;    // erase block size in units of sector size
      return RES_OK;

    default:
      return RES_PARERR;
  }
}

#pragma endregion

#pragma region MSC_FLASH

// Callback invoked when received READ10 command.
// Copy disk's data to buffer (up to bufsize) and 
// return number of copied bytes (must be multiple of block size) 
int32_t msc_read_cb (uint32_t lba, void* buffer, uint32_t bufsize)
{
  // Note: SPIFLash Block API: readBlocks/writeBlocks/syncBlocks
  // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
  return flash.readBlocks(lba, (uint8_t*) buffer, bufsize/512) ? bufsize : -1;
}

// Callback invoked when received WRITE10 command.
// Process data in buffer to disk's storage and 
// return number of written bytes (must be multiple of block size)
int32_t msc_write_cb (uint32_t lba, uint8_t* buffer, uint32_t bufsize)
{
  digitalWrite(LED_BUILTIN, HIGH);

  // Note: SPIFLash Block API: readBlocks/writeBlocks/syncBlocks
  // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
  return flash.writeBlocks(lba, buffer, bufsize/512) ? bufsize : -1;
}

// Callback invoked when WRITE10 command is completed (status received and accepted by host).
// used to flush any pending cache.
void msc_flush_cb (void)
{
  // sync with flash
  flash.syncBlocks();

  // clear file system's cache to force refresh
  fatfs.cacheClear();

  digitalWrite(LED_BUILTIN, LOW);
}

void flash_usb_mount()
{
  pinMode(LED_BUILTIN, OUTPUT);

  bool fl=flash.begin();

  usb_msc.setID(STR_DEV_MANUFACTOR, STR_DEV_PRODUCT, STR_DEV_VERSION);

  usb_msc.setReadWriteCallback(msc_read_cb, msc_write_cb, msc_flush_cb);

  usb_msc.setCapacity(flash.size()/512, 512);

  usb_msc.setUnitReady(true);

  bool msc=usb_msc.begin();


  bool fs_formatted = fatfs.begin(&flash);

  if(!fs_formatted)
  {
    Serial.println("NO FORMAT");
    flash_format();
    fs_formatted = fatfs.begin(&flash);
  }
  else
  {
    Serial.println("FORMAT");
  }

  Serial.begin(115200);

  Serial.println("Yuki SuperPico 1.0");
  Serial.print("JEDEC ID: 0x"); Serial.println(flash.getJEDECID(), HEX);
  Serial.print("Flash size: "); Serial.print(flash.size() / 1024); Serial.println(" KB");
}


bool format_fat12(void)
{
  // Working buffer for f_mkfs.
  #ifdef __AVR__
    uint8_t workbuf[512];
  #else
    uint8_t workbuf[4096];
  #endif

  // Elm Cham's fatfs objects
  FATFS elmchamFatfs;

  // Make filesystem.
  #if FF_MULTI_PARTITION
  const DWORD plist[]={100,0,0,0};
  FRESULT f=f_fdisk(0,plist,workbuf);
  Serial.print("FDISK = ");
  Serial.println(f);
  FRESULT r = f_mkfs("0:", FM_FAT, 0, workbuf, sizeof(workbuf));
  #else
  FRESULT r = f_mkfs("0:", FM_FAT, 0, workbuf, sizeof(workbuf));
  #endif
  Serial.print("MKFS = ");
  Serial.println(r);
  if (r != FR_OK) {
    return false;
  }

  // mount to set disk label
  r = f_mount(&elmchamFatfs, "0:", 1);
  Serial.print("MOUNT = ");
  Serial.println(r);
  if (r != FR_OK) {
    return false;
  }

  // Setting label
  r = f_setlabel(DISK_LABEL);
  Serial.print("LABEL = ");
  Serial.println(r);
  if (r != FR_OK) {    
    return false;
  }

  // unmount
  f_unmount("0:");

  // sync to make sure all data is written to flash
  flash.syncBlocks();

  return true;
}

bool check_fat12(void)
{
  // Check new filesystem
  FatVolume fatfs;
  if (!fatfs.begin(&flash)) {
    return false;
  }
  return true;
}


void flash_format()
{
  format_fat12();
  check_fat12();
}

#pragma endregion

