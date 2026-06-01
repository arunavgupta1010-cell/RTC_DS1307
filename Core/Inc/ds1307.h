#ifndef DS1307_H
#define DS1307_H

#include "stm32g0xx_hal.h"

// ─── Address ─────────────────────────────
#define DS1307_ADDR  (0x68 << 1)

// ─── Structure ───────────────────────────
typedef struct {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t date;
    uint8_t month;
    uint8_t year;
} DS1307_Time;

// ─── Function Declarations ───────────────
void DS1307_SetTime(I2C_HandleTypeDef *hi2c,
                    DS1307_Time *t);
void DS1307_GetTime(I2C_HandleTypeDef *hi2c,
                    DS1307_Time *t);

#endif /* DS1307_H */
