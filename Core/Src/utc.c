#include "utc.h"
#include "ds1307.h"

extern I2C_HandleTypeDef hi2c1; 

static DS1307_Time rtc_time;
static uint32_t utc_timestamp = 0;

// Days per month (non-leap year)
static const uint8_t days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

// Leap year check
static bool is_leap(uint16_t year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// Convert RTC date/time to Unix timestamp (seconds since 1970-01-01)
static uint32_t to_unix(DS1307_Time *t) {
    uint32_t days = 0;
    uint16_t y;
    for (y = 1970; y < (2000 + t->year); y++) {
        days += is_leap(y) ? 366 : 365;
    }
    for (uint8_t m = 1; m < t->month; m++) {
        days += days_in_month[m-1];
        if (m == 2 && is_leap(2000 + t->year)) days++;
    }
    days += (t->date - 1);
    return days*86400 + t->hours*3600 + t->minutes*60 + t->seconds;
}

bool utc_init(void) {
    DS1307_GetTime(&hi2c1, &rtc_time);
    utc_timestamp = to_unix(&rtc_time);
    return true;
}

bool utc_update(uint32_t new_utc) {
    utc_timestamp = new_utc;
    return true;
}

uint32_t utc_get(void) {
    return utc_timestamp;
}

uint8_t utc_get_day(void) {
    return rtc_time.date;
}

uint8_t utc_get_month(void) {
    return rtc_time.month;
}

uint8_t utc_get_year(void) {
    return rtc_time.year;
}
