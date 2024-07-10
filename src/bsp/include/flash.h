#ifndef __SRC_BSP_FLASH_H__
#define __SRC_BSP_FLASH_H__

#include "common.h"

bool flashInit(void);
bool flashErase(uint32_t addr, uint32_t length);
bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length);
bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length);

#endif
