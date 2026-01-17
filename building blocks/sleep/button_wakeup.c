/*

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/rom/uart.h"
#include "driver/rtc_io.h"      //rtc_io enables pins even when sleep

#include "esp_timer.h"

#define INPUT_PIN 0       //0 is the boot button on the esp32 board

void app_main()
{
  
    rtc_gpio_set_direction(INPUT_PIN, GPIO_MODE_INPUT);
    rtc_gpio_wakeup_enable(INPUT_PIN, GPIO_INTR_LOW_LEVEL);       //wakeup interrupt command
                                                              //enabler to let defined pin to be used to wake up
                                                              //when is at low value

    esp_sleep_enable_gpio_wakeup();     //enable the gpio for wakeup
    esp_sleep_enable_timer_wakeup(5000000);

    while (true)
    {
        if (rtc_gpio_get_level(INPUT_PIN) == 0)     //this command read pin even if controller is sleeping
        {
            printf("please release button\n");
            do
            {
                vTaskDelay(pdMS_TO_TICKS(10));
            } while (rtc_gpio_get_level(INPUT_PIN) == 0);
        }

        printf("going for a nap\n");
        uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);
        int64_t before = esp_timer_get_time();
        esp_light_sleep_start();
        int64_t after = esp_timer_get_time();

        esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();     //return enum state to detect
                                                                            //what woke up the esp32
        printf("napped for %lld, reason was %s\n", (after - before) / 1000,
               reason == ESP_SLEEP_WAKEUP_TIMER ? "timer" : "button");
    }
}

*/