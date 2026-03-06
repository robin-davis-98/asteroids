#include "win32_common.h"
#include <petrichor_time.h>

void time_init(Timer* timer) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    timer->frequency = (uint64_t)freq.QuadPart;

    LARGE_INTEGER start;
    QueryPerformanceCounter(&start);
    timer->start_ticks = (uint64_t)start.QuadPart;
    timer->last_ticks = timer->start_ticks;
}

uint64_t time_get_raw_ticks() {
    LARGE_INTEGER ticks;
    QueryPerformanceCounter(&ticks);
    return (uint64_t)ticks.QuadPart;
}

float time_get_delta(Timer* timer) {
    uint64_t now = time_get_raw_ticks();
    uint64_t elapsed_ticks = now - timer->last_ticks;

    float delta = (float)elapsed_ticks / (float)timer->frequency;

    timer->last_ticks = now;
    return delta;
}