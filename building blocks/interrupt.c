#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define PIN_SWITCH 15



QueueHandle_t interruptQueue;

static void IRAM_ATTR gpio_isr_handler(void *args)                  //callback function for interrupt
{
    int pinNumber = (int)args;
    xQueueSendFromISR(interruptQueue, &pinNumber, NULL);            //we use queue because we pass parameter else we could use semaphore 
}

void buttonPushedTask(void *params)                                 //function wakes up after button press which activates gpio_isr_handler
{
    int pinNumber, count = 0;
    while (true)
    {
        if (xQueueReceive(interruptQueue, &pinNumber, portMAX_DELAY))
        {
            printf("GPIO %d was pressed %d times. The state is %d\n", pinNumber, count++, gpio_get_level(PIN_SWITCH));
        }
    }
}

void app_main()
{
   
    gpio_set_direction(PIN_SWITCH, GPIO_MODE_INPUT);
    gpio_pulldown_en(PIN_SWITCH);
    gpio_pullup_dis(PIN_SWITCH);
    gpio_set_intr_type(PIN_SWITCH, GPIO_INTR_POSEDGE);                  //interrupt trigger type
                                                                    //1. interrupt caller pin
                                                                    //2. interrupt type (positive, negative)

    interruptQueue = xQueueCreate(10, sizeof(int));                 //create a queue with 10 int I can use for the interrupt
    xTaskCreate(buttonPushedTask, "buttonPushedTask", 2048, NULL, 1, NULL);         //task that handle buttonPusehdTask

    gpio_install_isr_service(0);
    gpio_isr_handler_add(PIN_SWITCH, gpio_isr_handler, (void *)PIN_SWITCH);             //When intrrupt fires on PIN_SWITCH
                                                                                        //call gpio_isr_handler
                                                                                        //passing as argument args = (void *)PIN_SWITCH
    gpio_isr_handler_add(14, gpio_isr_handler,(void *) 14); 
    gpio_isr_handler_add(5, gpio_isr_handler,(void *) 5);                   //we can use multiple interrupt for different pins
}