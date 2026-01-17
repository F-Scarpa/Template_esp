/*

//set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/protocol_examples_common)
//we add that line in out Cmakelist file in the root


#include <stdio.h>
#include "nvs_flash.h"          //flash memory storage. persistent memory
#include "esp_wifi.h"           //wifi library
#include "esp_event.h"          //third essential library for connecting to wifi
#include "protocol_examples_common.h"

void app_main(void)
{
    nvs_flash_init();       //initialize nvs flash 
    esp_netif_init();       //initialize network interface
    esp_event_loop_create_default();    //create event loop
    //all of the above is always needed to connect to wifi

    example_connect();          //SSID and password are to be 
                                //written in menuconfig 
}

*/