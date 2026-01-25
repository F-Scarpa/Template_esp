#include "pushBtn.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <driver/gpio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"
#include "cJSON.h"
#include "app.h"

#define btn 0 //push button on the esp32 board

static SemaphoreHandle_t btn_sem;

static void IRAM_ATTR on_btn_pushed(void *args)     //button interrupt
{
    xSemaphoreGiveFromISR(btn_sem,NULL);            //send signal to semaphore
}

static void btn_push_task(void *params)
{
    while(true)
    {
        xSemaphoreTake(btn_sem,portMAX_DELAY);      //listen for segnal
        cJSON *payload = cJSON_CreateObject();                                          //create JSON object, this is out data = {}
        cJSON_AddBoolToObject(payload,"btn_state",gpio_get_level(btn));                 //we add btn_state:gpio_get_level struct to out object
                                                                                        //now it is :

                                                                                        // {
                                                                                        //     btn_state: gpio_get_level
                                                                                        // }
        char *message = cJSON_Print(payload);       //json message
        printf("message : %s\n", message);
        send_ws_message(message);               //send message to websocket

        //free heap memory
        cJSON_Delete(payload);     
        free(message); 
    }
}

void init_btn(void)     
{   

    btn_sem = xSemaphoreCreateBinary();         //create semaphore, needed to create receiver and transmitter 
    xTaskCreate(btn_push_task,"btn_push_task",2048,NULL,5,NULL);            //create handlers before creating a task

    gpio_set_direction(btn, GPIO_MODE_INPUT);
    gpio_set_intr_type(btn,GPIO_INTR_ANYEDGE);              //button presses are async events, we dont know wehn it may happen,
                                                            // polling will consume cpu resources uselessly, so we use semaphores

    gpio_install_isr_service(0);
    gpio_isr_handler_add(btn, on_btn_pushed, NULL);         //add interrupt 1. pin 2. interrupt_name
};