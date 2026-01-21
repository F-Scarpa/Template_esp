/*


#include <stdio.h>
#include <string.h>
#include "wifi_connect.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "nvs_flash.h"

static const char *TAG = "REST";
extern const uint8_t cert[] asm("_binary_AMAZON_crt_start");        //store certificate inside array ("_binary_certName_start")
                                                                    //every special character becomes a "_"

typedef struct chunk_payload_t          //struct to store incoming data
{
    uint8_t *buffer;
    int buffer_index;
} chunk_payload_t;

esp_err_t on_client_data(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
    {
        // ESP_LOGI(TAG, "Length=%d", evt->data_len);
        // printf("%.*s\n", evt->data_len, (char *)evt->data);
        chunk_payload_t *chunk_payload = evt->user_data;            //get user data

        //realloc change the amount of space the payload is using
        //1. existing size
        //2. what size do we want
        chunk_payload->buffer = realloc(chunk_payload->buffer, chunk_payload->buffer_index + evt->data_len + 1);

        //copy data inside payload
        //1. target index
        //2. data
        //3. how many bytes to copy
        memcpy(&chunk_payload->buffer[chunk_payload->buffer_index],(uint8_t *) evt->data, evt->data_len );      
        chunk_payload->buffer_index = chunk_payload->buffer_index + evt->data_len;      //move buffer index forward
        chunk_payload->buffer[chunk_payload->buffer_index] = 0;

        //printf("buffer******** %s\n",chunk_payload->buffer);

    }
    break;

    default:
        break;
    }
    return ESP_OK;
}

void fetch_quote()
{
    chunk_payload_t chunk_payload = {0};        //istance of payload, set the whole struct to 0

    esp_http_client_config_t esp_http_client_config = {
        //to use https certificate we need to copy url and paste in web searchbar 
        //> right click on the icon left of the bar
        //> click secure conenction
        //> click cert is valid
        //> go to details
        //> export to folder inside our project
        //> on CMakeLists include relative path of certificate 
        .url = "https://weather-api167.p.rapidapi.com/api/weather/forecast?place=Sassari",
        .method = HTTP_METHOD_GET,
        .event_handler = on_client_data,
        .user_data = &chunk_payload ,        //store incoming data
        .cert_pem = (char*)cert
    };
    esp_http_client_handle_t client = esp_http_client_init(&esp_http_client_config);
    esp_http_client_set_header(client, "Contnet-Type", "application/json");
    esp_http_client_set_header(client, "x-rapidapi-key", "a5088f2f2fmshfa72a41b2368229p14010djsn7c4aec708c38");
    esp_http_client_set_header(client, "x-rapidapi-host", "weather-api167.p.rapidapi.com");
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK)
    {
        ESP_LOGI(TAG, "HTTP GET status = %d, result = %s\n",
                 esp_http_client_get_status_code(client),  chunk_payload.buffer);       //chunk_payload.buffer = http
                                                                                        //get data, this print a giant JSON
    }
    else
    {
        ESP_LOGE(TAG, "HTTP GET request failed: %s", esp_err_to_name(err));
    }
    if(chunk_payload.buffer != NULL){           //free memory we created
       free(chunk_payload.buffer); 
    }
    esp_http_client_cleanup(client);
    wifi_disconnect();
}

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_connect_init();
    ESP_ERROR_CHECK(wifi_connect_sta("OPPO", "PASSWORD", 10000));
    fetch_quote();
}

*/