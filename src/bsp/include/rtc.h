#ifndef __SRC_BSP_RTC_H__
#define __SRC_BSP_RTC_H__

#include "common.h"

bool rtcInit(void);

uint32_t  rtcBackupRegRead(uint32_t idx);
void      rtcBackupRegWrite(uint32_t idx, uint32_t data);

#endif
