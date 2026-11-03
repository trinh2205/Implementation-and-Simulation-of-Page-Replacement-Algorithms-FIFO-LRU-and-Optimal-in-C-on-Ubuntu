#ifndef INPUT_H
#define INPUT_H

#include "simulator.h"

/* Read the number of frames */
int read_frame_count(int *frame_count);

/* Read the reference string */
int read_reference_string(ReferenceString *reference);

/* Read algorithm selection */
int read_algorithm_choice(int *choice);

#endif
