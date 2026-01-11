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


//queue is like a semaphore but we can send data into it
QueueHandle_t queue;    //declare a new queue handler




void task_ListenForHTTP(void *params)                   
{
    int counter = 0;        
    while(true)
    {
        counter++;
        printf("Received http data\n");
        long ok = xQueueSend( queue, &counter, 1000/portTICK_PERIOD_MS);      //return true if data is pushed in the queue
                                                                    //params:
                                                                    //queue handler
                                                                    //&var
                                                                    //time to wait
        if(ok)
        {
            printf("Added message to queue\n");
        }
        else
        {
            printf("Fail to add message to queue\n");                 // if queue is full we need to free it
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


void task_HTTPWork(void *params)
{
    while(true)
    {           
        int rxint;
        if(xQueueReceive(queue, &rxint, 5000/portTICK_PERIOD_MS))
        {
            printf("Read data from queue %d\n", rxint);
        }
        printf("Working with http data\n");
    }
}





void app_main(void)
{
    queue = xQueueCreate(3, sizeof(int));         //create a queue inside queue handler and push x item of size y (3 ints)
                                        //params:
                                        //how long is the queue
                                        //size of queue items
                
    xTaskCreate(&task_ListenForHTTP,"get http",2048, NULL, 1, NULL);
    xTaskCreate(&task_HTTPWork,"do something with http",2048, NULL, 1, NULL);
            
}

*/