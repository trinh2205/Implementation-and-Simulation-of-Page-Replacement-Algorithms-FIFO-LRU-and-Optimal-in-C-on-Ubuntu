#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "simulator.h"

/* FIFO Page Replacement Algorithm */
int simulate_fifo(
    const ReferenceString *reference,
    FrameSet *frames,
    SimulationStats *stats
);

#endif
