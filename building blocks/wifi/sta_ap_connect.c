/*

#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "wifi_connect.h"       //created this component (new folder) and created a new CMakeLists.txt  //wifi init
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"





void app_main(void)
{
    //wifi init start
    nvs_flash_init();
    wifi_connect_init();
    //wifi init end
    wifi_connect_sta("FRITZ!Box 7530 TM", "BVXZH9GCX4V",10000);     //3. stop after failing for parameter time (milliseconds)
    vTaskDelay(pdMS_TO_TICKS(10000));
    wifi_disconnect();
    wifi_connect_ap("myESP32AP", "password"); //esp as access point, default = password 8 char long atleast
    vTaskDelay(pdMS_TO_TICKS(20000));
    wifi_disconnect();




}

*/