/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
              
#include "math.h"                       //for math functions like abs()
#include "driver/gpio.h"                //enable use of digital inputs/oututs

#define builtInLED 2

void app_main(void)

{   
    gpio_set_direction(builtInLED, GPIO_MODE_OUTPUT );               //set direction of pins (input or output)
    uint32_t ledOnFlag = 0; 


    while(1)
    {
       ledOnFlag = !ledOnFlag;
       gpio_set_level(builtInLED,ledOnFlag);                         //set pin level (high or low);
       vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}

*/