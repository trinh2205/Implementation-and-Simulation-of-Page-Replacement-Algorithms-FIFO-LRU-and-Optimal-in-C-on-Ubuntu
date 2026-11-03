#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "algorithms.h"


/*
 * FIFO Page Replacement Algorithm
 *
 * The oldest loaded page is replaced first.
 */
int simulate_fifo(
    const ReferenceString *reference,
    FrameSet *frames,
    SimulationStats *stats
) {

    /* Validate input */
    if (
        reference == NULL ||
        reference->values == NULL ||
        reference->length == 0 ||
        frames == NULL ||
        frames->pages == NULL ||
        frames->capacity == 0 ||
        stats == NULL
    ) {
        return 0;
    }

    /* Initialize statistics */
    stats->page_faults = 0;
    stats->page_hits = 0;

    /* Reset all frames */
    for (size_t i = 0; i < frames->capacity; i++) {
        frames->pages[i] = EMPTY_FRAME;
    }

    /*
     * next_victim indicates the frame
     * that will be replaced next.
     */
    size_t next_victim = 0;

    printf("\n");
    printf("=========================================\n");
    printf("       FIFO PAGE REPLACEMENT\n");
    printf("=========================================\n");

    /* Print table header */
    printf("\n%-6s %-8s", "Step", "Page");

    for (size_t i = 0; i < frames->capacity; i++) {
        printf(" F%-9zu", i + 1);
    }

    printf(" %-10s\n", "Result");

    printf("--------------------------------------------------\n");

    /* Process each page reference */
    for (size_t i = 0; i < reference->length; i++) {

        int current_page = reference->values[i];

        const char *result;

        /* Check whether page already exists */
        size_t position = find_page(frames, current_page);

        if (position != SIZE_MAX) {

            /* Page Hit */
            stats->page_hits++;

            result = "HIT";

        } else {

            /* Page Fault */
            stats->page_faults++;

            size_t empty_frame = find_empty_frame(frames);

            if (empty_frame != SIZE_MAX) {

                /* Use an available frame */
                frames->pages[empty_frame] = current_page;

            } else {

                /*
                 * Replace the oldest page.
                 */
                frames->pages[next_victim] = current_page;

                /* Move to the next victim frame */
                next_victim = (next_victim + 1) % frames->capacity;
            }

            result = "FAULT";
        }

        /* Print current simulation step */
        printf("%-6zu %-8d", i + 1, current_page);

        for (size_t j = 0; j < frames->capacity; j++) {

            if (frames->pages[j] == EMPTY_FRAME) {
                printf(" %-10s", "-");
            } else {
                printf(" %-10d", frames->pages[j]);
            }
        }

        printf(" %-10s\n", result);
    }

    printf("--------------------------------------------------\n");

    return 1;
}
