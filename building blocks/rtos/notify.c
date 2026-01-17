/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"                 //import library for random generation
#include "math.h"                       //for math functions like abs()
#include <string.h>


static TaskHandle_t receiverHandler = NULL;     //variable to handle a task
void sender(void *params){
    while(1)
    {
        xTaskNotifyGive(receiverHandler);       //trigger the receiver
        xTaskNotifyGive(receiverHandler); 
        xTaskNotifyGive(receiverHandler); 
        xTaskNotifyGive(receiverHandler); 
        vTaskDelay(5000 / portTICK_PERIOD_MS);  
    }

}

void receiver(void *params){
    while(1)
    {
       ulTaskNotifyTake(pdTRUE, portMAX_DELAY);        // enables the receiver to be triggered by given notification (wont go next line until triggered)
                                                    //params:
                                                    //boolean :
                                                    //pdFALSE = one call for every notification given 
                                                    //pdTRUE = one call only 
                                                    //timer
       printf("Received notification\n");
    }

}



void app_main(void){
    
    xTaskCreate(&receiver,"receiver",2048, NULL, 2, &receiverHandler);
    xTaskCreate(&sender,"sender",2048, NULL, 2, NULL);
    
            
}



*/