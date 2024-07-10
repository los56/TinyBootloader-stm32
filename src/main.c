#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_rcc.h"
#include "usb_device.h"

void init(void) {
  bspInit();
  rtcInit();

  resetButtonInit();
  gpioInit();
  MX_USB_DEVICE_Init();
  flashInit();
}

void jumpToFirmware(void) {
  void (**jump_target)(void) = (void (**)(void))(0x08005000 + 4);
  
  if((uint32_t)(*jump_target) != 0xFFFFFFFF) {
    uint32_t i;

    HAL_RCC_DeInit();
    HAL_DeInit();
    
    for (i = 0;i < 8;i++) {
      NVIC->ICER[i] = 0xFFFFFFFF;
      __DSB();
      __ISB();
    }
    SysTick->CTRL = 0;

    (*(jump_target))();
  }
}

int main(void) {
  uint32_t delay_ms = 250;
  init();

  if (resetButtonCount() != 2) {
    jumpToFirmware();
    delay_ms = 100;
  }

  for(;;) {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_12);
    HAL_Delay(delay_ms);
  }

  return 0;
}
