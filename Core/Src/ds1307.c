#include "ds1307.h"

static uint8_t dec2bcd(uint8_t val) {
    return ((val / 10) << 4) | (val % 10);
}

static uint8_t bcd2dec(uint8_t val) {
    return ((val >> 4) * 10) + (val & 0x0F);
}

void DS1307_SetTime(I2C_HandleTypeDef *hi2c, DS1307_Time *t) {
    uint8_t data[8];
    data[0] = 0x00;
    data[1] = dec2bcd(t->seconds) & 0x7F;
    data[2] = dec2bcd(t->minutes);
    data[3] = dec2bcd(t->hours);
    data[4] = 0x01;
    data[5] = dec2bcd(t->date);
    data[6] = dec2bcd(t->month);
    data[7] = dec2bcd(t->year);
    HAL_I2C_Master_Transmit(hi2c, DS1307_ADDR, data, 8, HAL_MAX_DELAY);
}

void DS1307_GetTime(I2C_HandleTypeDef *hi2c, DS1307_Time *t) {
    uint8_t data[7];
    uint8_t reg = 0x00;
    HAL_I2C_Master_Transmit(hi2c, DS1307_ADDR, &reg, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(hi2c, DS1307_ADDR, data, 7, HAL_MAX_DELAY);
    t->seconds = bcd2dec(data[0] & 0x7F);
    t->minutes = bcd2dec(data[1]);
    t->hours   = bcd2dec(data[2] & 0x3F);
    t->date    = bcd2dec(data[4]);
    t->month   = bcd2dec(data[5]);
    t->year    = bcd2dec(data[6]);
}
