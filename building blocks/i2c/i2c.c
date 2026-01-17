/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_types.h"

#define SDA_GPIO 26
#define SCL_GPIO 25
#define LM75A_ADDRESS 0X48

void app_main()
{
    i2c_config_t i2c_config = {             //i2c config
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_GPIO,
        .scl_io_num = SCL_GPIO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,        //sda requires a pullup resistor
        .scl_pullup_en = GPIO_PULLUP_ENABLE,        //scl requires a pullup resistor
        .master.clk_speed = 100000};
    i2c_param_config(I2C_NUM_0, &i2c_config);       //1. which i2c wee want to use 
    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

    uint8_t raw[2]; //this sensor reading need 2 registers
    i2c_cmd_handle_t cmd_handle = i2c_cmd_link_create();        //i2c handler
    i2c_master_start(cmd_handle);
    i2c_master_write_byte(cmd_handle, (LM75A_ADDRESS << 1) | I2C_MASTER_READ, true);    //2. target address 
                                                                                        //3. read command
                                                                                        //4. device aknowledge

       //read registers 
    i2c_master_read(cmd_handle, (uint8_t *)&raw, 2, I2C_MASTER_ACK);       //2. address casted as a pointer
                                                                            //3. byte to fill
                                                                            //4. goive aknowledgement
                                                                            
                                                                            
    i2c_master_stop(cmd_handle);

    //execute functions we gave to the command handle in the previous steps
    i2c_master_cmd_begin(I2C_NUM_0, cmd_handle, 1000 / portTICK_PERIOD_MS);     //3. timeout if 
                                                                                //there's no response
                                                                                //in selected time

    //free up memory after using the i2c commands                                                                            
    i2c_cmd_link_delete(cmd_handle);





    int16_t data = (raw[0] << 8 | raw[1]) >> 5;         // right shift raw[0] by 8 places (<< 8)
                                                        //if we use "=" raw[0] would be placed
                                                        //as the LSB of data

                                                        //we glue raw[1] to raw[0] ( | raw[1])
                                                        //since this sensor doesn't use the last 5 bits
                                                        //we discard them (>> 5)

    
    if (data & (1 << 10)) {          //1 << 10 porta 1 al 10 bit e se anche il 10bit di data è 1 allora 
                                     //la temp è negativa (D10 = 1)

    data |= 0xF800;                  //0xF800 fa diventare 1 tutti i bit non usati (dopo D10)
                                     //uguali a 1 e con l'OR si estende il dato per avere 16bit
}                                                    

    float temperature = (data * 0.125);
    printf("temperature %f\n", temperature);
}

*/