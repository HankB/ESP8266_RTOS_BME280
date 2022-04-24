#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <bmp280.h>
#include <string.h>

#include "my_bmp280.h"

#define I2C_MASTER_SCL 5
#define I2C_MASTER_SDA 4

bmp280_t dev;
bool bme280p;

void read_bme280(float *pressure, float *temperature, float *humidity)
{
    if (bmp280_read_float(&dev, temperature, pressure, humidity) != ESP_OK)
    {
        printf("Temperature/pressure reading failed\n");
        *pressure = *temperature = *humidity = 0.0;
        return;
    }

    if (!bme280p)
        *humidity = 0.0;

    *pressure /=100; // convert from Pa to hPa
    *temperature = *temperature/5.0*9.0 + 32.0; // °C to °F
}

void init_bmp280(void)
{
    bmp280_params_t params;
    float p, t, h;

    ESP_ERROR_CHECK(i2cdev_init());
    bmp280_init_default_params(&params);
    memset(&dev, 0, sizeof(bmp280_t));

    ESP_ERROR_CHECK(bmp280_init_desc(&dev, BMP280_I2C_ADDRESS_0, 0,
            I2C_MASTER_SDA, I2C_MASTER_SCL));
    ESP_ERROR_CHECK(bmp280_init(&dev, &params));

    bme280p = dev.id == BME280_CHIP_ID;
    printf("BMP280: found %s\n", bme280p ? "BME280" : "BMP280");
    read_bme280(&p, &t, &h); // read and discard
}

