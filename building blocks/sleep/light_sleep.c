/*

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "esp_sleep.h"
#include "esp_log.h"
#include "esp32/rom/uart.h"
#include "esp_timer.h"

void app_main()
{
    esp_sleep_enable_timer_wakeup(5000000);     //how long to sleep when sleep command is called
    printf("going for a nap\n");
    uart_tx_wait_idle(CONFIG_ESP_CONSOLE_UART_NUM);

    int64_t before = esp_timer_get_time();      //get how long the esp has been running 
    printf("%lld\n",before);
    esp_light_sleep_start();    //go to sleep

    int64_t after = esp_timer_get_time();

    printf("napped for %lld milliseconds\n", (after - before) / 1000);   // divide for 1000 to get 
                                                            //milliseconds from microseconds
}

*/