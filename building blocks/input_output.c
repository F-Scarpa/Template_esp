/*

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
              
#include "math.h"                       //for math functions like abs()
#include "driver/gpio.h"                //enable use of digital inputs/oututs


#define builtInLED 2
#define buttonPin 15



void app_main(void)

{   

    gpio_set_direction(builtInLED, GPIO_MODE_OUTPUT );               //set direction of pins (input or output)
    gpio_set_direction(buttonPin,GPIO_MODE_INPUT);
    gpio_pulldown_en(buttonPin);                                     //set internal pulldown resistor of pin
    //gpio_pullup_en(******);                                        //set internal pullup resistor of pin
                                                                            //wotuhout pullup or pulldown resistor enabled we need to 
                                                                            //use an external one to avoid float state
    //gpio_pullup_dis(******);                                       //disable pullups for pin
    uint32_t ledOnFlag = 0; 


    while(true)
    {
        int ledState = gpio_get_level(buttonPin);                   //get voltage level on pin
        gpio_set_level(builtInLED,ledState);                        //set voltage level on pin
        vTaskDelay(1);                                               //we need to add a delay to avoid watchdog timer trigger
        // in this state the CPU works even while there is no reason to, noone might press the button for a long time
        //may need an interrupt to avoid battery consumption
        
        
    }








}


*/