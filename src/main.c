#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"
#include "input.h"
#include "algorithms.h"


/* Display statistics */
static void print_statistics(
    const char *name,
    const ReferenceString *reference,
    const SimulationStats *stats
) {

    printf("\n=========================================\n");
    printf("          %s STATISTICS\n", name);
    printf("=========================================\n");

    printf("Total References : %zu\n", reference->length);
    printf("Page Faults      : %zu\n", stats->page_faults);
    printf("Page Hits        : %zu\n", stats->page_hits);

    printf(
        "Fault Ratio      : %.2f%%\n",
        100.0 * (double)stats->page_faults /
        (double)reference->length
    );

    printf(
        "Hit Ratio        : %.2f%%\n",
        100.0 * (double)stats->page_hits /
        (double)reference->length
    );
}


/* Compare all three algorithms */
static void print_comparison(
    const SimulationStats *fifo,
    const SimulationStats *lru,
    const SimulationStats *optimal,
    size_t total
) {

    const SimulationStats *results[] = {
        fifo, lru, optimal
    };

    const char *names[] = {
        "FIFO", "LRU", "Optimal"
    };

    size_t minimum_faults = fifo->page_faults;

    for (size_t i = 1; i < 3; i++) {

        if (results[i]->page_faults < minimum_faults) {
            minimum_faults = results[i]->page_faults;
        }
    }

    printf("\n");
    printf("============================================================\n");
    printf("                  ALGORITHM COMPARISON\n");
    printf("============================================================\n");

    printf(
        "%-12s %10s %10s %12s %12s\n",
        "Algorithm", "Faults", "Hits",
        "Fault(%)", "Hit(%)"
    );

    printf("------------------------------------------------------------\n");

    for (size_t i = 0; i < 3; i++) {

        printf(
            "%-12s %10zu %10zu %11.2f%% %11.2f%%\n",
            names[i],
            results[i]->page_faults,
            results[i]->page_hits,
            100.0 * (double)results[i]->page_faults /
                (double)total,
            100.0 * (double)results[i]->page_hits /
                (double)total
        );
    }

    printf("------------------------------------------------------------\n");
    printf("Minimum Page Faults: %zu\n", minimum_faults);
    printf("Best result: ");

    int first = 1;

    for (size_t i = 0; i < 3; i++) {

        if (results[i]->page_faults == minimum_faults) {

            if (!first) {
                printf(", ");
            }

            printf("%s", names[i]);
            first = 0;
        }
    }

    printf("\n");
    printf("============================================================\n");
}


int main(void) {

    int frame_count;
    int algorithm_choice;

    ReferenceString reference = {NULL, 0};
    FrameSet frames = {NULL, 0};

    SimulationStats stats = {0, 0};

    SimulationStats fifo_stats = {0, 0};
    SimulationStats lru_stats = {0, 0};
    SimulationStats optimal_stats = {0, 0};

    int success = 1;

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
    switch (algorithm_choice) {

        case 1:

            success = simulate_fifo(
                &reference, &frames, &stats
            );

            if (success) {
                print_statistics("FIFO", &reference, &stats);
                print_frames(&frames);
            }

            break;

        case 2:

            success = simulate_lru(
                &reference, &frames, &stats
            );

            if (success) {
                print_statistics("LRU", &reference, &stats);
                print_frames(&frames);
            }

            break;

        case 3:

            success = simulate_optimal(
                &reference, &frames, &stats
            );

            if (success) {
                print_statistics("OPTIMAL", &reference, &stats);
                print_frames(&frames);
            }

            break;

        case 4:

            printf("\n******** RUNNING FIFO ********\n");

            success = simulate_fifo(
                &reference, &frames, &fifo_stats
            );

            if (success) {
                print_statistics("FIFO", &reference, &fifo_stats);
                print_frames(&frames);
            }

            if (!success) {
                break;
            }

            printf("\n******** RUNNING LRU ********\n");

            success = simulate_lru(
                &reference, &frames, &lru_stats
            );

            if (success) {
                print_statistics("LRU", &reference, &lru_stats);
                print_frames(&frames);
            }

            if (!success) {
                break;
            }

            printf("\n******** RUNNING OPTIMAL ********\n");

            success = simulate_optimal(
                &reference, &frames, &optimal_stats
            );

            if (success) {
                print_statistics(
                    "OPTIMAL", &reference, &optimal_stats
                );

                print_frames(&frames);

                print_comparison(
                    &fifo_stats,
                    &lru_stats,
                    &optimal_stats,
                    reference.length
                );
            }

            break;

        default:

            fprintf(stderr, "Invalid algorithm selection.\n");
            success = 0;
            break;
    }

    /* Step 7: Handle simulation result */
    if (!success) {

        fprintf(stderr, "Simulation failed.\n");

        free_frames(&frames);
        free(reference.values);

        return EXIT_FAILURE;
    }

    /* Step 8: Release memory */
    free_frames(&frames);
    free(reference.values);

    printf("\nSimulation completed successfully!\n");

    return EXIT_SUCCESS;
}
