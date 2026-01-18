#include <stdio.h>
#include "esp_wifi.h"
#include "nvs_flash.h"

#define MAX_APs 20          //esp32 max Access points

char *getAuthModeName(wifi_auth_mode_t wifi_auth_mode)      //return the connection auth mode
{
    switch (wifi_auth_mode)
    {
    case WIFI_AUTH_OPEN:
        return "WIFI_AUTH_OPEN";
    case WIFI_AUTH_WEP:
        return "WIFI_AUTH_WEP";
    case WIFI_AUTH_WPA_PSK:
        return "WIFI_AUTH_WPA_PSK";
    case WIFI_AUTH_WPA2_PSK:
        return "WIFI_AUTH_WPA2_PSK";
    case WIFI_AUTH_WPA_WPA2_PSK:
        return "WIFI_AUTH_WPA_WPA2_PSK";
    case WIFI_AUTH_WPA2_ENTERPRISE:
        return "WIFI_AUTH_WPA2_ENTERPRISE";
    case WIFI_AUTH_WPA3_PSK:
        return "WIFI_AUTH_WPA3_PSK";
    case WIFI_AUTH_WPA2_WPA3_PSK:
        return "WIFI_AUTH_WPA2_WPA3_PSK";
    case WIFI_AUTH_WAPI_PSK:
        return "WIFI_AUTH_WAPI_PSK";
    case WIFI_AUTH_OWE:
        return "WIFI_AUTH_OWE";
    case WIFI_AUTH_MAX:
        return "WIFI_AUTH_MAX";
    case WIFI_AUTH_WPA3_EXT_PSK_MIXED_MODE:
        return "WIFI_AUTH_WPA3_EXT_PSK_MIXED_MODE";
    case WIFI_AUTH_DPP:
        return "WIFI_AUTH_DPP";
    case WIFI_AUTH_WPA3_ENTERPRISE:
        return "IFI_AUTH_WPA3_ENTERPRISE";
    case WIFI_AUTH_WPA2_WPA3_ENTERPRISE:
        return "WIFI_AUTH_WPA2_WPA3_ENTERPRISE";
    case WIFI_AUTH_WPA_ENTERPRISE:
        return "WIFI_AUTH_WPA_ENTERPRISE";
    case WIFI_AUTH_WPA3_ENT_192:
        return "WIFI_AUTH_WPA3_ENT_192";
    case WIFI_AUTH_WPA3_EXT_PSK:
        return "WIFI_AUTH_WPA3_EXT_PSK";

    }
    return "UNKNOWN";
}

void app_main(void)
{
    nvs_flash_init();

    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();       //struct to configure wifi
                                                                            //wifi_config_default is helper function to fill the structure
    esp_wifi_init(&wifi_init_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    esp_wifi_start();

    wifi_scan_config_t wifi_scan_config = {     //struct for scan
        .show_hidden = true,
        //.channel = 13       //look at a particular channel
    };
    esp_wifi_scan_start(&wifi_scan_config, true);       //start scan 2. stop code until wifi scan is completed

    wifi_ap_record_t wifi_records[MAX_APs];             //struct to hold the Access Points
    uint16_t max_record = MAX_APs;

    esp_wifi_scan_get_ap_records(&max_record, wifi_records);        //
    
    //print found APs
    printf("Found %d access points:\n", max_record);
    printf("\n");
    printf("               SSID              | Channel | RSSI |   Auth Mode \n");
    printf("----------------------------------------------------------------\n");
    for (int i = 0; i < max_record; i++)
    {
        printf("%32s | %7d | %4d | %12s\n", (char *)wifi_records[i].ssid,
               wifi_records[i].primary, wifi_records[i].rssi,
               getAuthModeName(wifi_records[i].authmode));
    }
    printf("----------------------------------------------------------------\n");
}