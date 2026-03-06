#ifndef PET_TIME_H
#define PET_TIME_H

#include <stdint.h>

struct Timer {
    uint64_t start_ticks;
    uint64_t last_ticks;
    uint64_t frequency;
};

void time_init(Timer* timer);
float time_get_delta(Timer* timer);
uint64_t time_get_raw_ticks();

#endif