#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "algorithms.h"


/*
 * LRU Page Replacement Algorithm
 *
 * Replace the page that has not been used
 * for the longest period of time.
 */
int simulate_lru(
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

    /* Check memory allocation size */
    if (frames->capacity > SIZE_MAX / sizeof(size_t)) {
        return 0;
    }

    /*
     * last_used[i] stores the most recent
     * access step of the page in frame i.
     */
    size_t *last_used = malloc(
        frames->capacity * sizeof(size_t)
    );

    if (last_used == NULL) {
        fprintf(stderr, "LRU memory allocation failed.\n");
        return 0;
    }

    /* Initialize statistics */
    stats->page_faults = 0;
    stats->page_hits = 0;

    /* Initialize frames and access history */
    for (size_t i = 0; i < frames->capacity; i++) {

        frames->pages[i] = EMPTY_FRAME;

        last_used[i] = 0;
    }

    printf("\n");
    printf("=========================================\n");
    printf("        LRU PAGE REPLACEMENT\n");
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

        /* Check whether the page is already in memory */
        size_t position = find_page(frames, current_page);

        if (position != SIZE_MAX) {

            /* Page Hit */
            stats->page_hits++;

            /* Update the last access time */
            last_used[position] = i + 1;

            result = "HIT";

        } else {

            /* Page Fault */
            stats->page_faults++;

            /* Find an available frame */
            size_t target = find_empty_frame(frames);

            if (target == SIZE_MAX) {

                /*
                 * Memory is full.
                 * Find the least recently used page.
                 */
                target = 0;

                for (
                    size_t j = 1;
                    j < frames->capacity;
                    j++
                ) {

                    if (last_used[j] < last_used[target]) {
                        target = j;
                    }
                }
            }

            /* Load the new page */
            frames->pages[target] = current_page;

            /* Update access history */
            last_used[target] = i + 1;

            result = "FAULT";
        }

        /* Display current simulation state */
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

    /* Release temporary memory */
    free(last_used);

    return 1;
}
