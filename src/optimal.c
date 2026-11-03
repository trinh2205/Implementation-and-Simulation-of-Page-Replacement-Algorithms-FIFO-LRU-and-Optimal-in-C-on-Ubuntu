#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include "algorithms.h"


/*
 * Find the next occurrence of a page
 * in the future reference string.
 */
static size_t find_next_use(
    const ReferenceString *reference,
    int page,
    size_t current_step
) {

    for (
        size_t i = current_step + 1;
        i < reference->length;
        i++
    ) {

        if (reference->values[i] == page) {
            return i;
        }
    }

    /*
     * SIZE_MAX means the page
     * will never be used again.
     */
    return SIZE_MAX;
}


/*
 * Optimal Page Replacement Algorithm
 *
 * Replace the page whose next use is
 * farthest in the future.
 */
int simulate_optimal(
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

    /* Initialize all frames */
    for (size_t i = 0; i < frames->capacity; i++) {
        frames->pages[i] = EMPTY_FRAME;
    }

    printf("\n");
    printf("=========================================\n");
    printf("       OPTIMAL PAGE REPLACEMENT\n");
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

        /* Check whether page exists in memory */
        size_t position = find_page(frames, current_page);

        if (position != SIZE_MAX) {

            /* Page Hit */
            stats->page_hits++;

            result = "HIT";

        } else {

            /* Page Fault */
            stats->page_faults++;

            /* Find an empty frame */
            size_t target = find_empty_frame(frames);

            if (target == SIZE_MAX) {

                /*
                 * All frames are occupied.
                 * Find the page used farthest
                 * in the future.
                 */

                target = 0;

                size_t farthest_use = 0;

                for (
                    size_t j = 0;
                    j < frames->capacity;
                    j++
                ) {

                    size_t next_use = find_next_use(
                        reference,
                        frames->pages[j],
                        i
                    );

                    /*
                     * Page will never be used again.
                     * Replace it immediately.
                     */
                    if (next_use == SIZE_MAX) {

                        target = j;

                        break;
                    }

                    /*
                     * Select the page whose
                     * next access is farthest.
                     */
                    if (next_use > farthest_use) {

                        farthest_use = next_use;

                        target = j;
                    }
                }
            }

            /* Load the new page */
            frames->pages[target] = current_page;

            result = "FAULT";
        }

        /* Display current memory state */
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
