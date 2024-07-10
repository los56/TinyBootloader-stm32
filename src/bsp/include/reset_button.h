#ifndef __SRC_BSP_RESET_BUTTON_H__
#define __SRC_BSP_RESET_BUTTON_H__

#include "common.h"

#define RESET_BUTTON_BACKUP_REG_INDEX   1

bool     resetButtonInit(void);
uint32_t resetButtonCount(void);

#endif
