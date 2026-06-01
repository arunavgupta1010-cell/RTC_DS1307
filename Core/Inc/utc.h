#ifndef __UTC_H
#define __UTC_H

#include "stm32g0xx_hal.h"
#include <stdbool.h>
#include <stdint.h>

bool utc_init(void);
bool utc_update(uint32_t utc_timestamp);
uint32_t utc_get(void);
uint8_t utc_get_day(void);
uint8_t utc_get_month(void);
uint8_t utc_get_year(void);

#endif /* __UTC_H */
