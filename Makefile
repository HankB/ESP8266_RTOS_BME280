#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := ESP8266_RTOS_BME280

EXTRA_COMPONENT_DIRS := /home/hbarta/esp/esp-idf-lib/components
EXCLUDE_COMPONENTS := max7219 mcp23x17 led_strip max31865 ls7366r

include $(IDF_PATH)/make/project.mk

