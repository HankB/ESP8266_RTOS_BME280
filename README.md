# ESP8266_RTOS_Start

Copied from my private "start" project that included GPIO, WiFi, SNTP and MQTT in a sort of example project. That began life as the example "hello_world" project and grew like topsy.



## Purpose

Add BME280 support to the starting point. Target is a ESP8266 NodeMCU 12E (or similar.)

## Other libraries

[ESP-IDF Components library](https://github.com/UncleRus/esp-idf-lib)

```text
cd ~/exp
git clone https://github.com/UncleRus/esp-idf-lib.git
cd ~/Programming/ESP8266/ESP8266_RTOS_BME280
```

```text
hbarta@olive:~/Programming/ESP8266/ESP8266_RTOS_Start$ cat Makefile
#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := ESP8266_RTOS_Start

EXTRA_COMPONENT_DIRS := /home/hbarta/esp/esp-idf-lib/components
EXCLUDE_COMPONENTS := max7219 mcp23x17 led_strip max31865 ls7366r

include $(IDF_PATH)/make/project.mk

hbarta@olive:~/Programming/ESP8266/ESP8266_RTOS_Start$ 
```

## Build

"Getting Started" guide at <https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html>

Assumes that the SDK is intalled in `~/esp` but can be set elsewhere using environment variables.

```text
export ESP_BASE_DIR=~/esp
export IDF_PATH=${ESP_BASE_DIR}/ESP8266_RTOS_SDK
. ${IDF_PATH}/export.sh
make
make flash 
make monitor 
```

## Status

* Copied code from starting point, builds and runs.
* Added [ESP-IDF Components library](https://github.com/UncleRus/esp-idf-lib), compile errors.

## TODO

* Identify compatible BME280 library.
    * [ESP-IDF Components library](https://github.com/UncleRus/esp-idf-lib)
    * [ESP8266 driver for the BME280 sensor](https://github.com/Phosphenius/esp8266_bme280) GPL
    * [BMP280-library](https://github.com/farmerkeith/BMP280-library)

## Convenient host commands

```text
mosquitto_sub -v -t esp8266.1/pub/\#
systemctl status mqtt
sudo systemctl stop mosquitto
sudo tail -f /var/log/mosquitto/mosquitto.log
make menuconfig # to change build/config settings
```

## Errata

* `make monitor` will restart the device.
* `minicom` will not work at the default baud rate of 74880. But it will capture some boot messages put out at 115200 using the -C option. Used `make menuconfig` to set baudrate to 115200. (Still some output at ???)
* Setting GPIO_LED to 1 (to work on the ESP01) doesn't work on the NodeMCU board and causes serial monitor to no longer work.
* It's really a challenge to change the name of the project.
    * Edit `CMakeLists.txt` `Makefile`
    * `make clean`\
    * `cd build; cmake ..`
    * `make`
    * Still there!
* [Link to FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos.html) (for ESP32, but probably close for ESP8266.)
