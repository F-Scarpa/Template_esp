#include <stdio.h>
#include "esp_log.h"
#include "string.h"
#include "esp_wifi.h"
#include "esp_netif.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

static char* TAG = "WIFI CONNECT: ";

static esp_netif_t *esp_netif;  //wifi_connect_sta return value to avoid errors 

static EventGroupHandle_t wifi_events;      //event group allows to have multiple states, semaphore only 1
static int CONNECTED = BIT0;
static int DISCONNECTED = BIT1;


//wifi init - 1
void event_handler(void *event_handler_arg, esp_event_base_t event_base,        //this function is called when WIFI CONNECTS                                                                        
                   int32_t event_id, void *event_data)
{
    switch(event_id)
    {
        case WIFI_EVENT_STA_START :
            ESP_LOGI(TAG, "WIFI_EVENT_STA_START");
            esp_wifi_connect();
            break;
        case WIFI_EVENT_STA_CONNECTED :
            ESP_LOGI(TAG, "WIFI_EVENT_STA_CONNECTED");
            break;
        case WIFI_EVENT_STA_DISCONNECTED :
            ESP_LOGI(TAG, "WIFI_EVENT_STA_DISCONNECTED");
            xEventGroupSetBits(wifi_events, DISCONNECTED);
            break;
        case IP_EVENT_STA_GOT_IP :
            ESP_LOGI(TAG, "IP_EVENT_STA_GOT_IP");       //this happens when we connect correctly
            xEventGroupSetBits(wifi_events, CONNECTED);
            break;
        default:
            break;
}
}


void wifi_connect_init(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());       //enable event loop 
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, event_handler, NULL));     //1. event category we are interested in
                                                                                                        //2. subscribed events
                                                                                                        //3. event handler
                                                                                                        //4 parameter to pass to handler
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, event_handler, NULL));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));        //store wifi data
};

//wifi station - 2


esp_err_t wifi_connect_sta(char* ssid, char* pass, int timeout)
{   
    wifi_events = xEventGroupCreate();
    esp_netif = esp_netif_create_default_wifi_sta(); //create interface for station
    esp_wifi_set_mode(WIFI_MODE_STA);
    wifi_config_t wifi_config = {};
    strncpy((char*)wifi_config.sta.ssid,ssid,sizeof(wifi_config.sta.ssid)-1);
    strncpy((char*)wifi_config.sta.password,pass,sizeof(wifi_config.sta.password)-1);
    esp_wifi_set_config(WIFI_IF_STA, &wifi_config);
    esp_wifi_start();
    
    EventBits_t result = xEventGroupWaitBits(wifi_events, CONNECTED | DISCONNECTED, true, false, pdMS_TO_TICKS(timeout));//block this function until wifi connect or timeout
                                    //2. bits to listen
                                    //3 want to clear memory on exit?
                                    //4 want to wait to block until all bits are received?
                                    //5 wait time until timeout
    if(result == CONNECTED)
    {
        return ESP_OK;
    }
    else
    {
        return ESP_FAIL;
    }

}