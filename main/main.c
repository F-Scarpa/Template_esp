#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "wifi_connect.h"       //created this component (new folder) and created a new CMakeLists.txt  //wifi init






void app_main(void)
{
    //wifi init start
    nvs_flash_init();
    wifi_connect_init();
    //wifi init end
    esp_err_t err = wifi_connect_sta("FRITZ!Box 7530 TM", "BVXZH9GCX4V",10000);     //3. stop after failing for parameter time (milliseconds)



}