//set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/protocol_examples_common)
//we add that line in out Cmakelist file in the root

#include <stdio.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "protocol_examples_common.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include <time.h>
#include "esp_sntp.h"

#define TAG "NTP TIME"

SemaphoreHandle_t got_time_semaphore;

void print_time()           //primnt current time
{
    time_t now = 0;
    time(&now);             //retrieves the time in microseconds
    struct tm *time_info = localtime(&now);

    char time_buffer[50];
    strftime(time_buffer, sizeof(time_buffer), "%c", time_info);        //convert time in human readable value from a struct and push that in a string
                                                                            //3. how we want date to be printed (you can check list on internet)
    ESP_LOGI(TAG, "************ %s ***********", time_buffer);
}

void on_got_time(struct timeval *tv)            //timeval struct hold the seconds
{
    printf("on got callback %lld\n", tv->tv_sec);
    print_time();

    xSemaphoreGive(got_time_semaphore);     //allows the code to go past the semaphore take of got_time_semaphore
}

void app_main(void)
{
    got_time_semaphore = xSemaphoreCreateBinary();

    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);             //global environment variable
                                                                                        //1. var name
                                                                                        //2. opnode-time-zones and look for the desired timezone
                                                                                        //3. overwrite
    tzset();    //apply the timezone varialbe

    printf("first time print\n");
    print_time();

    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();
    example_connect();


    //init and setup the ntp
    esp_sntp_init();
    esp_sntp_set_sync_mode(SNTP_SYNC_MODE_IMMED);
    esp_sntp_setservername(0, "pool.ntp.org");
    esp_sntp_set_time_sync_notification_cb(on_got_time);

    xSemaphoreTake(got_time_semaphore, portMAX_DELAY);      //stop the code here until callback returns

    for (int i = 0; i < 5; i++)
    {
        print_time();
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    esp_restart();      //restart the chip
}