/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"                 //import library for random generation
#include "math.h"                       //for math functions like abs()
#include <string.h>
#include "stdint.h"
#include "stdlib.h"
#include "freertos/semphr.h"            //for semaphore


SemaphoreHandle_t binSemaphore; 

void task_ListenForHTTP(void *params)                   //Do something after receiving data
{
    while(true)
    {
        printf("Received http data\n");
        xSemaphoreGive(binSemaphore);
        printf("Processed http data\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void task_HTTPWork(void *params)
{
    while(true)
    {
        
        xSemaphoreTake(binSemaphore, portMAX_DELAY);            //portMAX_DELAY makes the function wait until the semaphore is free
        printf("Working with http data\n");
    }
}





void app_main(void)
{

    binSemaphore = xSemaphoreCreateBinary();            //create binary semaphore inside binSemaphore handler
    xTaskCreate(&task_ListenForHTTP,"httpReq",2048, NULL, 1, NULL);
    xTaskCreate(&task_HTTPWork,"httpwork",2048, NULL, 1, NULL);
            
}

*/