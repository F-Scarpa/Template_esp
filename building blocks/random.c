/*
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"  //import library for random generation
#include "math.h"

#define TAG "dice"

void app_main(void)
{   
    while(1)
    {
        ESP_LOGI(TAG,"rolled for: %ld", ((abs(esp_random()))%6) + 1);  //esp random
        vTaskDelay(1000 / portTICK_PERIOD_MS);  //delay for x milliseconds
        
    }

}
    */
