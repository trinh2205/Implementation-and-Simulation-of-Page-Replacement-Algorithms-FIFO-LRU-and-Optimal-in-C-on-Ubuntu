#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "simulator.h"

/* FIFO Page Replacement */
int simulate_fifo(
    const ReferenceString *reference,
    FrameSet *frames,
    SimulationStats *stats
);

/* LRU Page Replacement */
int simulate_lru(
    const ReferenceString *reference,
    FrameSet *frames,
    SimulationStats *stats
);

/* Optimal Page Replacement */
int simulate_optimal(
    const ReferenceString *reference,
    FrameSet *frames,
    SimulationStats *stats
);

#endif
