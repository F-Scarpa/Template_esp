#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"

void app_main(void)
{
    adc_oneshot_unit_handle_t adc_handle;

    // Config ADC1
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
        .ulp_mode = ADC_ULP_MODE_DISABLE                //ULP disabled (Ultra low power processor)
                                                        //ADC_ULP_MODE_FSM usefull for battery devices or when
                                                        //esp needs to go sleep
    };
    adc_oneshot_new_unit(&init_config, &adc_handle);

    // Channel config (ADC1_CHANNEL_6 = GPIO34)
    adc_oneshot_chan_cfg_t channel_config = {
        .bitwidth = ADC_BITWIDTH_12,      // 0–4095
        .atten = ADC_ATTEN_DB_12,           // 0 to ~3.9V
    };
    adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_6, &channel_config);

    while (1)
    {
        int val = 0;
        adc_oneshot_read(adc_handle, ADC_CHANNEL_6, &val);
        printf("ADC value: %d\n", val);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
