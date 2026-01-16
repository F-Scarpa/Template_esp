/*

#include <stdio.h>
#include "esp_timer.h"      //used for timer
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void timer_callback(void *args)             //timer callback implementation, always return void and take void *args as param
                                            //will be called after timer trigger
{
    static bool on;
    on = !on;
    gpio_set_level(GPIO_NUM_4, on);
    //printf("CALLED\n");
}

void app_main(void)
{

    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_OUTPUT);

    const esp_timer_create_args_t esp_timer_create_args = {             //create a struct for timer
                                                                            //keys:
                                                                            //1. timer callback
                                                                            //2. timer name
        .callback = timer_callback,
        .name = "My timer"
    };

    esp_timer_handle_t esp_timer_handle;                                //create timer handler, it enables the timer to
                                                                        //understand which tmer we want to use


    esp_timer_create(&esp_timer_create_args, &esp_timer_handle);        //create timer with previous struct and handler

    //2 function to start timers
    //esp_timer_start_once(esp_timer_handle,20);                  //fire once after 2nd arg microseconds (min 20 us)
    esp_timer_start_periodic(esp_timer_handle, ((1000*1000)*3));             //fire periodically (min 50 us)

    int x = 0;
    while (true)
    {
        esp_timer_dump(stdout);         //prints some info about timer
        vTaskDelay(pdMS_TO_TICKS(1000));
        if (x++ == 5)
        {
            esp_timer_stop(esp_timer_handle);           //stop the timer at specified handler
            esp_timer_delete(esp_timer_handle);         //clean data about timer at specified handler
        }
    }
}


*/