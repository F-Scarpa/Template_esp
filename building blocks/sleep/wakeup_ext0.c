/*

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "driver/rtc_io.h"

#define BUTTON GPIO_NUM_25      //external button

RTC_DATA_ATTR int timesWokenUp = 0;
void app_main(void)
{
  rtc_gpio_deinit(BUTTON);    //allows to use button as a normal gpio input
                              //until the rtc pullup en line
  /// general gpio functions using the pin.

  rtc_gpio_pullup_en(BUTTON);
  rtc_gpio_pulldown_dis(BUTTON);

  esp_sleep_enable_ext0_wakeup(BUTTON,0);     //wakeup esp32 when button signal is 0 
  printf("going to sleep. woken up %d\n", timesWokenUp++);

  esp_deep_sleep_start();     //go to sleep until wakeup
}

*/