#include "../global/constants.h"
#include <hardware/clocks.h>
#include "overclock.h"


void OverClockSPI()
{
  if(OVERCLOCK_SPI)
  {
    uint32_t freq=clock_get_hz(clk_sys);
    clock_configure(clk_peri, 0, CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLK_SYS, freq, freq);
  }
}