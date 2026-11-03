#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"
#include "input.h"
#include "algorithms.h"


int main(void) {

    int frame_count;
    int algorithm_choice;

    ReferenceString reference = {NULL, 0};

    FrameSet frames = {NULL, 0};

    SimulationStats stats = {0, 0};

    const char *algorithm_name;

    printf("=========================================\n");
    printf("       PAGE REPLACEMENT SIMULATOR\n");
    printf("=========================================\n");

    /* Step 1: Read frame count */
    if (!read_frame_count(&frame_count)) {

        fprintf(stderr, "Invalid frame configuration.\n");

        return EXIT_FAILURE;
    }

    /* Step 2: Read reference string */
    if (!read_reference_string(&reference)) {

        fprintf(stderr, "Reference input failed.\n");

        free(reference.values);

        return EXIT_FAILURE;
    }

    /* Step 3: Select algorithm */
    if (!read_algorithm_choice(&algorithm_choice)) {

        fprintf(stderr, "Invalid algorithm selection.\n");

        free(reference.values);

        return EXIT_FAILURE;
    }

    /* Step 4: Initialize frames */
    if (!initialize_frames(&frames, (size_t)frame_count)) {

        fprintf(stderr, "Frame initialization failed.\n");

        free(reference.values);

        return EXIT_FAILURE;
    }

    /* Step 5: Display configuration */
    printf("\n=========================================\n");
    printf("          SIMULATION CONFIGURATION\n");
    printf("=========================================\n");

    printf("Number of frames: %d\n", frame_count);

    printf("Number of references: %zu\n", reference.length);

    print_reference_string(&reference);

    /* Step 6: Execute selected algorithm */
    int success = 0;

    if (algorithm_choice == 1) {

        algorithm_name = "FIFO";

        success = simulate_fifo(
            &reference,
            &frames,
            &stats
        );

    } else {

        algorithm_name = "LRU";

        success = simulate_lru(
            &reference,
            &frames,
            &stats
        );
    }

    if (!success) {

        fprintf(stderr, "Simulation failed.\n");

        free_frames(&frames);
        free(reference.values);

        return EXIT_FAILURE;
    }

    /* Step 7: Display statistics */
    printf("\n=========================================\n");
    printf("          %s STATISTICS\n", algorithm_name);
    printf("=========================================\n");

    printf("Total References : %zu\n", reference.length);

    printf("Page Faults      : %zu\n", stats.page_faults);

    printf("Page Hits        : %zu\n", stats.page_hits);

    printf(
        "Fault Ratio      : %.2f%%\n",
        100.0 * (double)stats.page_faults /
        (double)reference.length
    );

    printf(
        "Hit Ratio        : %.2f%%\n",
        100.0 * (double)stats.page_hits /
        (double)reference.length
    );

    /* Step 8: Display final memory */
    print_frames(&frames);

    /* Step 9: Release allocated memory */
    free_frames(&frames);

    free(reference.values);

    printf("\n%s simulation completed successfully!\n", algorithm_name);

    return EXIT_SUCCESS;
}
