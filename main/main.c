#include <stdio.h>
#include <time.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define SDA_PIN 4
#define SCL_PIN 5
#define I2C_PORT I2C_NUM_0
#define PCF8563_ADDR 0x51

static const char *TAG = "PCF8563";

// Convert BCD to int
int bcd_to_int(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

void app_main(void) {
    // Ritardo iniziale
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    // Configurazione I2C
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = SDA_PIN,
        .scl_io_num = SCL_PIN,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 100000
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_PORT, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, 0, 0, 0));

    uint8_t buf[7];

    // Creazione comando I2C
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (PCF8563_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x02, true);  // Puntatore al registro secondi
    i2c_master_start(cmd);  // repeated start
    i2c_master_write_byte(cmd, (PCF8563_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, buf, 6, I2C_MASTER_ACK);  // secondi, minuti, ore, giorno, wday, mese
    i2c_master_read_byte(cmd, buf + 6, I2C_MASTER_NACK); // anno
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(I2C_PORT, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Errore lettura RTC: %s", esp_err_to_name(ret));
        return;
    }

    // Conversione BCD → struct tm
    struct tm dt = {
        .tm_sec  = bcd_to_int(buf[0] & 0x7F),
        .tm_min  = bcd_to_int(buf[1] & 0x7F),
        .tm_hour = bcd_to_int(buf[2] & 0x3F),
        .tm_mday = bcd_to_int(buf[4] & 0x3F),
        .tm_wday = buf[3] & 0x07,
        .tm_mon  = bcd_to_int(buf[5] & 0x1F) - 1,
        .tm_year = bcd_to_int(buf[6]) + 100  // 2000-based
    };

    char timestr[64];
    strftime(timestr, sizeof(timestr), "%c", &dt);
    ESP_LOGI(TAG, "Ora attuale: %s", timestr);
}
