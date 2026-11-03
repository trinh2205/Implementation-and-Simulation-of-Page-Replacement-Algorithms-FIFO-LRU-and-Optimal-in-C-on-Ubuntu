#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"
#include "input.h"
#include "algorithms.h"

int main(void) {

    int frame_count;

    ReferenceString reference = {NULL, 0};
    FrameSet frames = {NULL, 0};
    SimulationStats stats = {0, 0};

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

    /* Step 3: Initialize frames */
    if (!initialize_frames(&frames, (size_t)frame_count)) {
        fprintf(stderr, "Frame initialization failed.\n");
        free(reference.values);
        return EXIT_FAILURE;
    }

    /* Step 4: Display configuration */
    printf("\n=========================================\n");
    printf("          SIMULATION CONFIGURATION\n");
    printf("=========================================\n");

    printf("Number of frames: %d\n", frame_count);
    printf("Number of references: %zu\n", reference.length);

    print_reference_string(&reference);

    /* Step 5: Run FIFO */
    if (!simulate_fifo(&reference, &frames, &stats)) {

        fprintf(stderr, "FIFO simulation failed.\n");

        free_frames(&frames);
        free(reference.values);

        return EXIT_FAILURE;
    }

    /* Step 6: Display statistics */
    printf("\n=========================================\n");
    printf("            FIFO STATISTICS\n");
    printf("=========================================\n");

    printf("Total References : %zu\n", reference.length);
    printf("Page Faults      : %zu\n", stats.page_faults);
    printf("Page Hits        : %zu\n", stats.page_hits);

    printf(
        "Fault Ratio      : %.2f%%\n",
        100.0 * (double)stats.page_faults / (double)reference.length
    );

    printf(
        "Hit Ratio        : %.2f%%\n",
        100.0 * (double)stats.page_hits / (double)reference.length
    );

    /* Step 7: Display final memory */
    print_frames(&frames);

    /* Step 8: Release allocated memory */
    free_frames(&frames);
    free(reference.values);

    printf("\nFIFO simulation completed successfully!\n");

    return EXIT_SUCCESS;
}
