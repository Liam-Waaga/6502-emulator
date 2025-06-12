#include "clock.h"
#include "types.h"

#include <stdint.h>
#include <time.h>

#define CYCLES_BETWEEN_SYNCS 50

extern SYSTEM_FLAGS flags;

static uint64_t last_sync_ns = 0;
static uint64_t cycles_since_sync = 0;

/* Get current monotonic time in nanoseconds */
static uint64_t get_time_ns(void) {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return (uint64_t)now.tv_sec * 1000000000ULL + now.tv_nsec;
}

void clock_init(uint64_t hertz) {
    last_sync_ns = get_time_ns();
}

void clock_wait_cycles(uint64_t cycles, uint64_t clock_hz) {
    uint64_t start = get_time_ns();
    uint64_t wait_ns = (1000000000ULL * cycles) / clock_hz;

    while (get_time_ns() - start < wait_ns) {
        /* busy-wait loop */
    }
}

void clock_sync_cycles(uint64_t cycles_elapsed, uint64_t clock_hz) {
    uint64_t now = get_time_ns();
    uint64_t expected = last_sync_ns + (1000000000ULL * cycles_elapsed) / clock_hz;

    if (now < expected) {
        while (get_time_ns() < expected) {
            /* spin until real time catches up */
        }
    }

    last_sync_ns = expected;
}


void register_clock_wait(uint64_t cycles, int force_sync) {
    cycles_since_sync += cycles;
    if (force_sync || cycles >= CYCLES_BETWEEN_SYNCS) {
        clock_sync_cycles(cycles_since_sync, flags.clock_speed);
        cycles_since_sync = 0;
    }
}