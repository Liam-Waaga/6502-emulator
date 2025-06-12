#ifndef CLOCK_H
#define CLOCK_H
#include <stdint.h>

/* sets the clock speed in herts */
/* set to zero to use system clock speed */
void clock_init(uint64_t hertz);


/* Busy-wait for a number of cycles at a given clock frequency */
void clock_wait_cycles(uint64_t cycles, uint64_t clock_hz);

/* Sync to a desired cycle count since last sync, to prevent drift */
void clock_sync_cycles(uint64_t cycles_elapsed, uint64_t clock_hz);


/* registers a clock busy-wait, if enough cycles have elapsed since last wait, it waits that many cycles
   if you change the clock rate, make sure to call this with force_synce >= 1, to force a sync at the proper clock speed */
void register_clock_wait(uint64_t cycles, int force_sync);
#endif