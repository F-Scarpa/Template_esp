
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
              
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
    //gpio_pullup_dis(******);                                       //disable pullups for pin
    uint32_t ledOnFlag = 0; 


    while(1)
    {
        int ledState = gpio_get_level(buttonPin);                   //get voltage level on pin
        gpio_set_level(builtInLED,ledState);                        //set voltage level on pin
        
    }

}

