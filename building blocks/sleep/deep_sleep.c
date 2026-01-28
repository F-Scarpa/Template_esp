/*

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"

RTC_DATA_ATTR int timesWokenUp = 0;     //allow this variable to be recorded even during deep sleep
                                        //normal int the variable would go back to init value (0)
void app_main(void)
{
  esp_sleep_enable_timer_wakeup(5 * 1000000);
  printf("going to sleep. woken up %d\n", timesWokenUp++);

  esp_deep_sleep_start();   //go into deep sleep
                            //deep sleep dont allow the program to continue
                            //in light sleep the program continue instead
}

*/