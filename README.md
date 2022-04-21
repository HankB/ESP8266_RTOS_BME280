# ESP8266_RTOS_Start

Copied from `hello_world` example at `ESP8266_RTOS_SDK/examples/get-started/hello_world` and built/flashed/monitored on an ESP01 plugged into a USB adapter configured with pushbutton to short the required pins to flash the device.

From the original README

>Starts a FreeRTOS task to print "Hello World"

## Purpose

Build out to provide a starting point for projects that will use WiFi, MQTT, NTP, and GPIO.

## Build

"Getting Started" guide at <https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html>

Assumes that the SDK is intalled in `~/esp` but can be set elsewhere using environment variables.

```text
export ESP_BASE_DIR=~/esp
export IDF_PATH=${ESP_BASE_DIR}/ESP8266_RTOS_SDK
. ${IDF_PATH}/export.sh
make
make flash # ESP-01 - need to plug in ESP01 while holding button
make monitor # need to unplug/replug ESP01 to get it to run.
```

## Status

* Cloned code from `hello_world` example builds and runs.
* GPIO output
* Associates with AP. (info output and GPIO commented out.) Works on NodeMCU but not ESP-01.
* SNTP working.

## TODO

* Add WiFi - partial, reconnect not tested
* Add MQTT - working, reconnect tested
* Add SNTP - working, usage in main a bit buggy

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
