/*


//set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/protocol_examples_common)
//we add that line in out Cmakelist file in the root


#include <stdio.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "protocol_examples_common.h"
#include "esp_http_client.h"

esp_err_t client_event(esp_http_client_event_t *evt)        //called when something happens
{
    if (evt->event_id == HTTP_EVENT_ON_DATA)            //http_event is a enum there are different type of event(F12)
    {
        printf("%.*s\n", evt->data_len, (char *)evt->data);     //print received data
    }
    return ESP_OK;
}

void app_main(void)
{
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();

    example_connect();

    esp_http_client_config_t esp_http_client_config = {     //client config
        .url = "https://google.com",
        .event_handler = client_event};         //callback


    esp_http_client_handle_t client = esp_http_client_init(&esp_http_client_config);        //create client
    esp_http_client_perform(client);            //send a get http request to .url calling .event_handler callback
    esp_http_client_cleanup(client);            //free memory
}

*/