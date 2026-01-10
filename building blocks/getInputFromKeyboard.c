/*
#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_random.h"                 //import library for random generation
#include "math.h"                       //for math functions like abs()
#include "driver/gpio.h"                //enable use of digital inputs/oututs
#include <string.h>                     //import file for memset and strlen



void app_main(void)

{   
    char c = 0;
    char str[100];      //array
    memset(str,0,sizeof(str));                //clean rubbish from array can also do || char str[100] = {0};

    while(c!='\n')          //check if variable c is not empty
    {
        c = getchar();      //get character from keyboard if not character is found then returns 0xff
        if(c != 0xff)       //check if character is pressed (because c now is not 0xff, so the if blocks activates)
        {
            str[strlen(str)] = c;
            printf("%c",c);

        }
        
        vTaskDelay(100 / portTICK_PERIOD_MS);      //to avoid watchdog timer errors we need a delay because we are in a blocking loop
    }
    printf("Your input: %s\n", str);                
}

*/