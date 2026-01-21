/*

#include <stdio.h>
#include "wifi_connect.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_http_server.h"    //allow to create new server
#include "mdns.h"

static const char *TAG = "SERVER";


static esp_err_t on_default_url(httpd_req_t *req)     //static = like private member in classes
{
    ESP_LOGI(TAG,"URL: %s",req->uri);
    httpd_resp_sendstr(req,"hello world");
    return ESP_OK;
}

static void init_server()
{
  httpd_handle_t server = NULL;   //server handle
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();   //working configuration of our server

  ESP_ERROR_CHECK(httpd_start(&server, &config));   //start the server
// we need to listen to something now

  
  httpd_uri_t default_url = {   //url = browser address
    .uri ="/",                  //uri = 
    .method = HTTP_GET,
    .handler = on_default_url   //function which will be caleld when someone visits the url
  };
  httpd_register_uri_handler(server,&default_url);    //register the http

}

void start_mdns_service()
{
  mdns_init();
  mdns_hostname_set("my-esp32");    //create our name for server, set the host  type hostname.local
  mdns_instance_name_set("LEARN esp32 thing");
}

void app_main(void)
{
  ESP_ERROR_CHECK(nvs_flash_init());
  wifi_connect_init();
  ESP_ERROR_CHECK(wifi_connect_sta("g!g g TM", "e", 10000));

  start_mdns_service();
  init_server();
}



*/