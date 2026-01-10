/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"                 //import library for random generation
#include "math.h"                       //for math functions like abs()
#include <string.h>
#include "stdlib.h"        


void everySec(void *params){        //task always accept a void pointer as parameter, we need to cast them as needed
    
    while(true)
    {
        printf("Hello %s\n",(char*)params);             //params is casted to array of chars, which automatically point
        vTaskDelay(1000 / portTICK_PERIOD_MS);          //to memory
    }
}

void everyTwoSec(void *params){
    while(true)
    {
        printf("HelloSlow %d\n",*(int*)params);         //other data types need to be dereferenced from their address
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }

}

void app_main(void)
{
    static char fastPrinter[50] = "dieci";          //good practice to static data type for tasks params
    static int slowPrinter = 47;

          //create task:
                        //&functionName
                        //friendly name
                        //how much memory to utilize with this task
                        //optional parameters, always (void *params)
                        //priority 1-5 (1 is lowest 5 highest)
                        //handler

    xTaskCreate(&everySec,"printFast",2048, fastPrinter, 2, NULL);          //fastPrinter is array of char, 
                                                                            //no need to pass as a reference

    xTaskCreate(&everyTwoSec,"printslow",2048, &slowPrinter, 2, NULL);      //slowPrinter need to be passed as a 
                                                                            //reference instead


            
}


*/