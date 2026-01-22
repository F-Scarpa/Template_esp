#include <stdio.h>
#include "wifi_connect.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_http_server.h"    //allow to create new server
#include "mdns.h"
#include "toggle_led.h"
#include "cJSON.h"


//npm run build
//>dist > assets //this is our website
//fatfs_create_rawflash_image(storage dir_to_copy_path FLASH_IN_PROJECT) line on main>CMakeLists.txt
      //to allow to write directory on the chip on the flash memory

      
static const char *TAG = "SERVER";

static esp_err_t on_toggle_led_url(httpd_req_t *req)
{
  char buffer[100];                                                   //space for payload as string
                                                                      // (in this case is small) {is_on:true}

  memset(&buffer,0, sizeof(buffer));                                  //clean buffer
  httpd_req_recv(req,buffer,req->content_len);                        //fill the buffer

  cJSON *payload = cJSON_Parse(buffer);                               //create a json object from buffer 
                                                                      //(string to JSON)
  cJSON *is_on_json = cJSON_GetObjectItem(payload,"is_on");           //extract json key value 

  bool is_on = cJSON_IsTrue(is_on_json);    //check if value is true
  cJSON_Delete(payload);                    //free memory
  toggle_led(is_on);                        //call function url

  httpd_resp_set_status(req,"204 NO CONTENT");      //set http status
  httpd_resp_send(req,NULL,0);                      //send http status
  return ESP_OK;
}


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

  httpd_uri_t toggle_led_url = {
      .uri = "/api/toggle-led",         //dount use underscores in uri
      .method = HTTP_POST,
      .handler = on_toggle_led_url
    };
  httpd_register_uri_handler(server, &toggle_led_url);

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
  init_led();
  wifi_connect_init();
  ESP_ERROR_CHECK(wifi_connect_sta("ssid", "passs", 10000));

  start_mdns_service();
  init_server();
}