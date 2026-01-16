#include <stdio.h>
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"

#define TXD_PIN 4
#define RXD_PIN 5

#define RX_BUF_SIZE 1024

void app_main(void)
{
  uart_config_t uart_config = {                                     //configure serial port
                                                                    //keys:
                                                                    
    .baud_rate = 9600,                                              //baud rate
    .data_bits = UART_DATA_8_BITS,                                  //send 8 bits at a time
    .parity = UART_PARITY_DISABLE,                                  //
    .stop_bits = UART_STOP_BITS_1,                                  //
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE                           //
  };
  uart_param_config(UART_NUM_1 ,&uart_config);          //esp have 3 uart 0 is for serial communication so we use 1

  uart_set_pin(UART_NUM_1,TXD_PIN,RXD_PIN,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);   //set pins
  uart_driver_install(UART_NUM_1,RX_BUF_SIZE,0,0,NULL,0);                           //install uart driver
                                                                                        //1.uart we are using
                                                                                        //2. buffer size receiver
                                                                                        //3. buffer size sender 
                                                                                        //4. queue size (not used in this example)
                                                                                        //5. uart queue (NULL here)
                                                                                        //6. interrupt flag 

  char message[] = "ping";
  printf("sending: %s\n", message);
  uart_write_bytes(UART_NUM_1,message, sizeof(message));                //send message through serial port 

  //set up message tobe received
  char incoming_message[RX_BUF_SIZE];                       
  memset(incoming_message, 0 , sizeof(incoming_message));       //set all bytes pointed by incoming_message to 0 (clean the buffer)
  uart_read_bytes(UART_NUM_1,(uint8_t *) incoming_message,RX_BUF_SIZE,pdMS_TO_TICKS(500));
  printf("received: %s\n",incoming_message);
  

}