#include <stdio.h>
#include <string.h>
#include "parse_weather.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "cJSON.h"                      //library to parse JSON data


static const char* TAG = "PARSE WEATHER";


esp_err_t parse_weather(char *weatherStr)
{
    cJSON *root = cJSON_Parse(weatherStr);

    //if error on root
    if (!root) {
        ESP_LOGE(TAG, "JSON parse error");      //info error message
        return ESP_FAIL;                        //return
    }

    cJSON *list = cJSON_GetObjectItem(root, "list");

    //if error
    if (!cJSON_IsArray(list)) {
        ESP_LOGE(TAG, "'list' not found or not array");
        cJSON_Delete(root);     //free memory destroying root
        return ESP_FAIL;
    }

    int items = cJSON_GetArraySize(list);           //get items from list as array length
    ESP_LOGI(TAG, "Forecast entries: %d", items);

    // take first element
    cJSON *item = cJSON_GetArrayItem(list, 0);      //1. array_name 2. item index

    //if error
    if (!item) {
        cJSON_Delete(root);
        return ESP_FAIL;
    }

    cJSON *main = cJSON_GetObjectItem(item, "main");        //get main from item and save in the pointer variable main

    //if error
    if (!main) {
        ESP_LOGE(TAG, "'main' not found");
        cJSON_Delete(root);
        return ESP_FAIL;
    }

    cJSON *temp = cJSON_GetObjectItem(main, "temp");
    if (cJSON_IsNumber(temp)) {
        ESP_LOGI(TAG, "Temperature: %.2f", temp->valuedouble);
    }

    cJSON_Delete(root);
    return ESP_OK;
}
