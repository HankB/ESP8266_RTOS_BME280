/* copided from Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <time.h>

#include "my_info.h"
#include "my_gpio.h"
#include "my_wifi.h"
#include "my_mqtt.h"
#include "my_sntp.h"
#include "my_bme280.h"
#include "local.h"

static const char *TAG = "user_main";

void app_main()
{
    #define publish_buf_len 100
    static char publish_buf[publish_buf_len];
    time_t  boot_timestamp = 0;
    int  loop_count = 0;
    time_t now;
    time_t uptime;
    static int loop_delay_sec = 10;

    init_wifi();
    mqtt_start();
    init_sntp();
    print_my_info();
    init_gpio();
    init_bme280();

    ESP_LOGI(TAG, "[APP] Free memory: %d bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());
    
    while( true) {
        now = time(0);
        if(boot_timestamp == 0)
        {
            if( now > 1650502924)
            {
                boot_timestamp = now + loop_count*loop_delay_sec;
                uptime = 0;
            }
            else
            {
                loop_count++;
                uptime = now;
            }
        }
        else
        {
            uptime = now - boot_timestamp;
        }

        float   temp=0;
        float   press=0;
        float   humid=0;
        int len = 10;
        char temp_buf[len], press_buf[len], humid_buf[len];

        read_bme280(&temp, &press, &humid);
        snprintf(publish_buf, publish_buf_len, "heap:%d, t:%ld, uptime:%ld, "
                    "temp %s, press %s, humid %s",
                    esp_get_free_heap_size(), now, uptime, 
                    my_float_print(temp_buf, len, temp/5*9+32, 1),
                    my_float_print(press_buf, len, press*10, 1),
                    my_float_print(humid_buf, len, humid, 1));
        mqtt_publish(NULL, publish_buf);
        vTaskDelay(1000*loop_delay_sec / portTICK_PERIOD_MS); // publish every loop_delay_sec s.
    }

    esp_restart();
}
