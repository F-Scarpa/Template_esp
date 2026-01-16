/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"                 //import library for random generation
#include "math.h"                       //for math functions like abs()
#include <string.h>
#include "stdint.h"
#include "stdlib.h"


static TaskHandle_t receiverHandler = NULL;     //variable to handle a task
void task_sender(void *params){
    while(1)
    {
        xTaskNotify(receiverHandler, (1 << 0), eSetBits);              //trigger the receiver, acts as a switch machine sending uint data
                                                                                     // which will be received by ulTaskNotifyWait
                                            //params:
                                                //handler
                                                //value to pass
                                                //eSetValue = you can F12 on the param and F12 on the typedef for more info


        //vTaskDelay(1000 / portTICK_PERIOD_MS);  
        xTaskNotify(receiverHandler, (1 << 1), eSetBits); 
        vTaskDelay(3000 / portTICK_PERIOD_MS);                  //DELAYS allow receiver to receive
        xTaskNotify(receiverHandler, (1 << 2), eSetBits); 
        //vTaskDelay(1000 / portTICK_PERIOD_MS);  
        xTaskNotify(receiverHandler, (1 << 3), eSetBits); 
        vTaskDelay(5000 / portTICK_PERIOD_MS);  
    }

}

void task_receiver(void *params){

    uint32_t state;  //variable to store data from sender, which is uint32_t DT
    while(1)
    {
        xTaskNotifyWait(0, 0xffffffff, &state, portMAX_DELAY);        // enables the receiver to be triggered by given notification (wont go next line until triggered)
                                                //params:
                                                    //clearbit entry HEX = used with no overwriting notify value to clear value every call
                                                    //clearbit exit HEX
                                                    //notification state
                                                    //timeout


       printf("Received state: %" PRIu32 "\n", state);      //PRIu32 enable printf to read uint32 DT
    }

}




void app_main(void){
    
    xTaskCreate(&task_receiver,"receiver",2048, NULL, 2, &receiverHandler);
    xTaskCreate(&task_sender,"sender",2048, NULL, 2, NULL);
    
            
}


*/