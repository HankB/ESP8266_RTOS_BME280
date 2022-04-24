// @file bmp280.h

#ifndef BMP280_H
#define BMP280_H

void read_bme280(float *pressure, float *temperature, float *humidity);
void init_bmp280(void);

#endif // BMP280_H