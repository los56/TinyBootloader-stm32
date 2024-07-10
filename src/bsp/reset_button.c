#include "reset_button.h"
#include "rtc.h"

static uint32_t _reset_button_count = 0;

bool resetButtonInit(void) {
  bool ret = true;

  if (RCC->CSR & (1 << 26)) {
    rtcBackupRegWrite(RESET_BUTTON_BACKUP_REG_INDEX, rtcBackupRegRead(RESET_BUTTON_BACKUP_REG_INDEX) + 1);
    HAL_Delay(500);
    _reset_button_count = rtcBackupRegRead(RESET_BUTTON_BACKUP_REG_INDEX);
  }

  rtcBackupRegWrite(RESET_BUTTON_BACKUP_REG_INDEX, 0);

  return ret;
}

uint32_t resetButtonCount(void) {
  return _reset_button_count;
}
