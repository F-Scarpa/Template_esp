/*



#include <stdio.h>
#include <stdlib.h>
#include "wifi_connect.h"
#include "nvs_flash.h"
#include "esp_log.h"
#include "esp_http_server.h"    //allow to create new server
#include "mdns.h"
#include "toggle_led.h"
#include "cJSON.h"
#include "pushBtn.h"


#include "esp_vfs.h"
#include "esp_vfs_fat.h"



static const char *BASE_PATH = "/store";   


static const char *TAG = "SERVER";
static httpd_handle_t server = NULL;   //server handle


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

#define WS_MAX_SIZE 1024
static int client_session_id;

esp_err_t send_ws_message(char* message)
{
  if(!client_session_id)
  {
    ESP_LOGE(TAG, "no client id");
    return -1;
  }
  httpd_ws_frame_t ws_message = {
    .final = true,
    .fragmented = false,
    .len = strlen(message),
    .payload = (uint8_t *)message,
    .type = HTTPD_WS_TYPE_TEXT

  };
  httpd_ws_send_frame_async(server, client_session_id, &ws_message);
  return 1;
}


static esp_err_t on_WEB_SOCKET_url(httpd_req_t *req)
{
  client_session_id = httpd_req_to_sockfd(req);
  if(req->method == HTTP_GET) return ESP_OK;
  
  httpd_ws_frame_t ws_pkt;
  memset(&ws_pkt,0,sizeof(httpd_ws_frame_t));
  ws_pkt.type = HTTPD_WS_TYPE_TEXT;
  ws_pkt.payload = malloc(WS_MAX_SIZE);         //create our own heap memory
  httpd_ws_recv_frame(req,&ws_pkt,WS_MAX_SIZE);   //copy memory 
  printf("ws payload: %.*s\n", ws_pkt.len, ws_pkt.payload);     //1. length to print 2. start index pointer 
  free(ws_pkt.payload);

  char* response = "connected OK";
  httpd_ws_frame_t ws_response = {
    .final = true,
    .fragmented = false,
    .type = HTTPD_WS_TYPE_TEXT,
    .payload = (uint8_t *)response,
    .len = strlen(response), 
  };
  return httpd_ws_send_frame(req, &ws_response);
  
}

static esp_err_t on_default_url(httpd_req_t *req)    
{                                                     //http home url page
    ESP_LOGI(TAG,"URL: %s",req->uri);

    char path[600];
    sprintf(path, "/store%s", req->uri);      //write a string inside a variable

    FILE *file = fopen(path, "r"); 
    //if path does not exist                   
    if(file == NULL)
    {
      file = fopen("/store/index.html", "r");    //open index page
      if(file == NULL)
      {
        httpd_resp_send_404(req);   //send error 404
      }
      ESP_LOGI(TAG, "STORE/INDEX.HTML NOT FOUND");
    }
    char buffer[1024];
    int bytes_read = 0;
    while((bytes_read = fread(buffer, sizeof(char), sizeof(buffer),file)) > 0)   //read the file, end file
                                                                                 //when byres_read is 0
    {
      httpd_resp_send_chunk(req, buffer, bytes_read); //send response while buffer is filled with file data
    }
    fclose(file);   //close file
    httpd_resp_send_chunk(req, NULL, 0); //empty http data chunk

    
    return ESP_OK;
}

static void init_server()     // can be used to store paths
{
 
  httpd_config_t config = HTTPD_DEFAULT_CONFIG();   //working configuration of our server

  config.uri_match_fn = httpd_uri_match_wildcard;   //enables the use of wildcards in routes, (/*)

  ESP_ERROR_CHECK(httpd_start(&server, &config));   //start the server



  
  httpd_uri_t toggle_led_url = {
      .uri = "/api/toggle-led",         //dount use underscores in uri
      .method = HTTP_POST,
      .handler = on_toggle_led_url
    };
  httpd_register_uri_handler(server, &toggle_led_url);

  
  httpd_uri_t web_socket_url = {
      .uri = "/ws",         //dount use underscores in uri
      .method = HTTP_GET,
      .handler = on_WEB_SOCKET_url,
      .is_websocket = true
    };
  httpd_register_uri_handler(server, &web_socket_url);


  httpd_uri_t default_url = {   //url = browser address
    .uri ="/*",                  //accept everything (/*)
    .method = HTTP_GET,
    .handler = on_default_url   //function which will be called when someone visits the url
                                //with /* every url call this func, unless farther in sequence
  };
  httpd_register_uri_handler(server,&default_url);    //register the http

}

void start_mdns_service()
{
  mdns_init();
  mdns_hostname_set("my-esp32");    //create our name for server, set the host  type hostname.local
  mdns_instance_name_set("LEARN esp32 thing");
}

void mount_fs()     //setup for fat memory
{
   esp_vfs_fat_mount_config_t esp_vfs_fat_mount_config = {
        .allocation_unit_size = CONFIG_WL_SECTOR_SIZE,
        .max_files = 5,
        .format_if_mount_failed = true,
    };
    esp_vfs_fat_spiflash_mount_ro(BASE_PATH, "storage", &esp_vfs_fat_mount_config);   //base_path is /store
                                                                                      //2. partition name in 
                                                                                      //partition table
}

void app_main(void)
{
  
  ESP_ERROR_CHECK(nvs_flash_init());
  init_led();
  init_btn();

  wifi_connect_init();
  ESP_ERROR_CHECK(wifi_connect_sta("FRITZ!Box 7530 TM", "BVXZH9GCX4V", 10000));

  start_mdns_service();
  mount_fs();   
  init_server();

}









*/