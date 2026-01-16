/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"                 //import library for random generation
#include "math.h"                       //for math functions like abs()
#include <string.h>
#include "stdint.h"
#include "stdlib.h"
#include "freertos/semphr.h"       
#include "freertos/event_groups.h"  //library to use event groups


//event group = multiple events => listen for both ble and http, only after i got both a tast can run
EventGroupHandle_t evtGrp;        //event group handler

    const int gotHTTP = (1 << 0);           //check if triggered
    const int gotBLE = (1 << 0);

void task_ListenForHTTP(void *params)                   
{

    while(true)
    {
        xEventGroupSetBits(evtGrp, gotHTTP);        // set gotHTTP event bit to notify listener task

        printf("Received http data\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void task_listenForBluetooth(void *params)
{
    while(true)
    {   
        xEventGroupSetBits(evtGrp, gotBLE); 
        printf("got bluetooth\n");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

void task_receivedBLEAndHTTP(void *param)
{
    while(true)
    {
        xEventGroupWaitBits(evtGrp, gotHTTP | gotBLE, true, true, portMAX_DELAY);
        printf("received http and BLE\n");
    }
}





void app_main(void)
{

    evtGrp = xEventGroupCreate();            //create event group for handler           
    xTaskCreate(&task_ListenForHTTP,"get http",2048, NULL, 1, NULL);
    xTaskCreate(&task_listenForBluetooth,"do something with http",2048, NULL, 1, NULL);
    xTaskCreate(&task_receivedBLEAndHTTP, "get ble and http",2048, NULL, 1 ,NULL);
            
}

*/