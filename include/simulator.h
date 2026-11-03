#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <stddef.h>
#include <stdint.h>

/* Value representing an empty frame */
#define EMPTY_FRAME (-1)

/* Reference String */
typedef struct {
    int *values;
    size_t length;
} ReferenceString;

/* Physical Memory Frame Set */
typedef struct {
    int *pages;
    size_t capacity;
} FrameSet;

/* Simulation Statistics */
typedef struct {
    size_t page_faults;
    size_t page_hits;
} SimulationStats;


/* Frame management functions */
int initialize_frames(FrameSet *frames, size_t capacity);

void free_frames(FrameSet *frames);

/* Page searching functions */
size_t find_page(const FrameSet *frames, int page);

size_t find_empty_frame(const FrameSet *frames);

/* Display functions */
void print_reference_string(const ReferenceString *reference);

void print_frames(const FrameSet *frames);

#endif
