#include "print.h"

void init() {
  tft_init();
  if (SERIAL_ENABLED) {
    Serial.begin(115200);
    while (!Serial) {
      //WAIT SERIAL
    }
  }
}

void print(const char* str, int16_t x, int16_t y, const uint8_t* font, uint16_t color) {
  tft_print(str, x, y, font, color);
  if (SERIAL_ENABLED) {
    Serial.println(str);
  }
}