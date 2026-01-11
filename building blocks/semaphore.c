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


//mutex semaphore allow tasks to not interferwe with each other, task_2 must wait task_1 to complete before running
//only one thing at a particular time (mutex)
//semaphore allowa only a block of code to enter at once

//create semaphore handler
SemaphoreHandle_t mutexBus; //no one can talk while mutexBus is occupied, here we define the semaphore, it's a special variable

void WriteToBus(char* message)
{
    printf("%s",message);
    
}

void task_1(void *params)
{
    while(true)
    {  
        printf("Reading temperature...\n");
        if(xSemaphoreTake(mutexBus, 1000 / portTICK_PERIOD_MS)) 
        {                                                               //block the semaphore
                                                                        //params:
                                                                        //semaphore handler
                                                                        //max waiting time to take the semaphore if occupied
        printf("Temperature : ");
        WriteToBus("25 C\n");
        xSemaphoreGive(mutexBus);       //allow to free the semaphore once the operation is finished
        }
        else
        {
            printf("Temp read time out\n");
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }
}

void task_2(void *params)
{
    while(true)
    {   
        printf("Reading humidity...\n");
        if(xSemaphoreTake(mutexBus,1000/portTICK_PERIOD_MS))
        {
            printf("Humidity : ");
            WriteToBus("40\n");
            xSemaphoreGive(mutexBus);       //allow to free the semaphore once the operation is finished
        }
        else
        {
            printf("Humidity read time out\n");
        }
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}





void app_main(void)
{
    mutexBus = xSemaphoreCreateMutex(); //we create a semaphore and store in the variable mutexBus
    xTaskCreate(&task_1,"temp",2048, NULL, 2, NULL);

    xTaskCreate(&task_2,"Humidity",2048, NULL, 2, NULL);
   
            
}

*/