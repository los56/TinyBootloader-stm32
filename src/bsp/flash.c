#include "flash.h"

#define FLASH_PAGE_MAX    64

typedef struct {
  uint32_t addr;
  uint32_t length;
} Flash_TableTypeDef;

static Flash_TableTypeDef flash_table[FLASH_PAGE_MAX];
static bool flashPageInRange(uint32_t page_num, uint32_t addr, uint32_t length);

bool flashInit(void) {
  uint32_t i;

  for (i = 0;i < FLASH_PAGE_MAX;i++) {
    flash_table[i].addr = 0x08000000 + (i * 1024);
    flash_table[i].length = 1024;
  }

  return true;
}

bool flashErase(uint32_t addr, uint32_t length) {
  bool ret = false;

  FLASH_EraseInitTypeDef eraseInit;
  HAL_StatusTypeDef status;

  int32_t start_page_num = -1;
  uint32_t i, page_count, page_error;

  page_count = 0;
  for (i = 0;i < FLASH_PAGE_MAX;i++) {
    if (flashPageInRange(i, addr, length)) {
      if (start_page_num < 0) {
        start_page_num = i;
      }
      page_count++;
    }
  }

  if(page_count > 0) {
    eraseInit.TypeErase = FLASH_TYPEERASE_PAGES;
    eraseInit.Banks = FLASH_BANK_1;
    eraseInit.PageAddress = flash_table[start_page_num].addr;
    eraseInit.NbPages = page_count;

    HAL_FLASH_Unlock();

    status = HAL_FLASHEx_Erase(&eraseInit, &page_error);
    if(status == HAL_OK) {
      ret = true;
    }

    HAL_FLASH_Lock();
  }
  return ret;
}

bool flashWrite(uint32_t addr, uint8_t *p_data, uint32_t length) {
  bool ret = true;
  HAL_StatusTypeDef status;
  uint16_t data;
  uint32_t i;

  HAL_FLASH_Unlock();

  for (i = 0;i < length;i += 2) {
    data = p_data[i];
    data |= p_data[i+1] << 8;

    status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, addr + i, (uint64_t) data);
    
    if (status != HAL_OK) {
      ret = false;
      break;
    }
  }

  HAL_FLASH_Lock();

  return ret;
}

bool flashRead(uint32_t addr, uint8_t *p_data, uint32_t length) {
  bool ret = true;
  uint8_t *p_byte = (uint8_t *)addr;
  uint32_t i;

  for (i = 0;i < length;i++) {
    p_data[i] = p_byte[i];
  }

  return ret;
}

bool flashPageInRange(uint32_t page_num, uint32_t addr, uint32_t length) {
  bool ret = false;
  uint32_t page_start, page_end, flash_start, flash_end;

  if(addr % 2 != 0) {
    return false;
  }

  page_start  = flash_table[page_num].addr;
  page_end    = page_start + flash_table[page_num].length - 1;
  flash_start = addr;
  flash_end   = flash_start + addr - 1;

  if (page_start >= flash_start && page_start <= flash_end) {
    ret = true;
  }

  if (page_end >= flash_start && page_end <= flash_end) {
    ret = true;
  }

  if (flash_start >= page_start && flash_start <= page_end) {
    ret = true;
  }

  if (flash_end >= page_start && flash_end <= page_end) {
    ret = true;
  }

  return ret;
}
