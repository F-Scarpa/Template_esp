/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/dac_oneshot.h"

void app_main(void)
{
    dac_oneshot_handle_t dac_handle;

    dac_oneshot_config_t dac_cfg = {
        .chan_id = DAC_CHAN_0   // DAC_CHAN_0 = GPIO25, DAC_CHAN_1 = GPIO26
    };

    ESP_ERROR_CHECK(dac_oneshot_new_channel(&dac_cfg, &dac_handle));

    ESP_ERROR_CHECK(dac_oneshot_output_voltage(dac_handle, 150));               // 0–255 the value select the voltage, if too low ,
                                                                                //leds may not go high because of the voltage drop
    printf("OK\n");
}

*/