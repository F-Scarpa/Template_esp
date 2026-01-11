#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"                 //import library for random generation
#include "math.h"                       //for math functions like abs()
#include <string.h>


void everySec(void *params){        //task always accept a void pointer as parameter, we need to cast them as needed
    
    while(true)
    {
        printf("Hello %s\n",(char*)params);             //params is casted to array of chars, which automatically point
        vTaskDelay(1000 / portTICK_PERIOD_MS);          //to memory
    }
}


void app_main(void){
    static char fastPrinter[20] = "Hello";

    xTaskCreate(&everySec,"printFast",2048, fastPrinter, 2, NULL);
            
}
