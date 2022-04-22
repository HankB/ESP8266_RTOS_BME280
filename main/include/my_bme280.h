#ifndef MY_BME280_H
#define MY_BME280_H

void init_bme280(void);
void read_bme280(float *temp, float *press, float *humid);



#endif // MY_BME280_H
