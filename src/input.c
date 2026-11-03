#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>

#include "input.h"

/* Read and validate an integer */
static int read_integer(
    const char *prompt,
    int min_value,
    int max_value,
    int *result
) {
    char buffer[128];

    while (1) {

        printf("%s", prompt);
        fflush(stdout);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0;
        }

        /* Handle excessively long input lines */
        if (strchr(buffer, '\n') == NULL && !feof(stdin)) {
            int ch;

            while ((ch = getchar()) != '\n' && ch != EOF) {
                /* Discard remaining characters */
            }

            printf("Input is too long. Try again.\n");
            continue;
        }

        errno = 0;

        char *endptr;
        long value = strtol(buffer, &endptr, 10);

        while (isspace((unsigned char)*endptr)) {
            endptr++;
        }

        if (
            endptr == buffer ||
            *endptr != '\0' ||
            errno == ERANGE ||
            value < min_value ||
            value > max_value
        ) {
            printf("Invalid input. Please try again.\n");
            continue;
        }

        *result = (int)value;

        return 1;
    }
}


/* Read the number of frames */
int read_frame_count(int *frame_count) {

    if (frame_count == NULL) {
        return 0;
    }

    printf("\n--- MEMORY CONFIGURATION ---\n");

    return read_integer(
        "Enter number of frames: ",
        1,
        INT_MAX,
        frame_count
    );
}


/* Read the reference string */
int read_reference_string(ReferenceString *reference) {

    if (reference == NULL) {
        return 0;
    }

    reference->values = NULL;
    reference->length = 0;

    int length;

    if (!read_integer(
        "Enter number of page references: ",
        1,
        INT_MAX,
        &length
    )) {
        return 0;
    }

    if ((size_t)length > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    int *values = malloc((size_t)length * sizeof(int));

    if (values == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 0;
    }

    printf("\n--- REFERENCE STRING INPUT ---\n");

    for (int i = 0; i < length; i++) {

        char prompt[64];

        snprintf(
            prompt,
            sizeof(prompt),
            "Page reference %d: ",
            i + 1
        );

        if (!read_integer(prompt, 0, INT_MAX, &values[i])) {

            free(values);

            return 0;
        }
    }

    reference->values = values;
    reference->length = (size_t)length;

    return 1;
}

/* Read algorithm selection */
int read_algorithm_choice(int *choice) {

    if (choice == NULL) {
        return 0;
    }

    printf("\n--- ALGORITHM SELECTION ---\n");
    printf("1. FIFO    - First In First Out\n");
    printf("2. LRU     - Least Recently Used\n");
    printf("3. Optimal - Optimal Page Replacement\n");
    printf("4. Compare All Algorithms\n");

    return read_integer(
        "Enter your choice: ",
        1,
        4,
        choice
    );
}
