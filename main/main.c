#include <stdio.h>
#include "nvs_flash.h"
#include "wifi_connect.h"
#include "mqtt_client.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "secrets.h"

static char *TAG = "MQTT";
static void mqtt_event_handler(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data);
static void test_send_messages(void *param);
static esp_mqtt_client_handle_t client;

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    wifi_connect_init();
    ESP_ERROR_CHECK(wifi_connect_sta(WIFI_SSID, WIFI_PASSWORD, 10000));
    esp_mqtt_client_config_t esp_mqtt_client_config = {                         //configure mqtt client
        .broker.address.uri = "mqtt://test.mosquitto.org:1883"};           
    client = esp_mqtt_client_init(&esp_mqtt_client_config);         
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);         //1.client 2.type of events to listen to 
                                                                                                // 3.callback 4.args for handler
    esp_mqtt_client_start(client);
}

static void mqtt_event_handler(void *event_handler_arg, esp_event_base_t event_base,
                               int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;

    switch ((esp_mqtt_event_id_t)event_id)          //event id is uint 32 so we cast it t oesp mqtt event
    {
    case MQTT_EVENT_CONNECTED:      //check all events of mqtt
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        esp_mqtt_client_subscribe(client,"animal/mammal/cat/felix",1);          //2 what do we want to listen   3. quality of system
        esp_mqtt_client_subscribe(client,"animal/reptiles/+/slither",1);  
        esp_mqtt_client_subscribe(client,"animal/fish/#",1);        //any fish
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED");
        break;
    case MQTT_EVENT_UNSUBSCRIBED:
        ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED");
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED");
        break;
    case MQTT_EVENT_DATA:                               //event coming in
        printf("topic: %.*s\n",event->topic_len, event->topic);                          //print not terminated string but i know the length
        printf("message: %.*s\n",event->data_len, event->data); 
        ESP_LOGI(TAG, "MQTT_EVENT_DATA");
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGE(TAG, "ERROR %s", strerror(event->error_handle->esp_transport_sock_errno));
        break;
    default:
        break;
    }
}