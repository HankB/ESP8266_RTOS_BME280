
/* Following copied from the example at https://github.com/Phosphenius/esp8266_bme280

 * esp8266_bme280  - a bme280 driver for the esp8266
 * Copyright (C) 2020 Luca Kredel
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "bme280.h"
#include "my_bme280.h"

static struct bme280_dev dev = {
      .addr = 0x76,
      .i2c_port = I2C_NUM_0,
      .i2c_sda_io = 4,
      .i2c_scl_io = 5
      };

void init_bme280(void)
{
  ESP_ERROR_CHECK(bme280_init(&dev));
}


void read_bme280(float *temp, float *press, float *humid)
{
    bme280_read(&dev, temp, press, humid);
}