#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "simulator.h"


/* Initialize memory frames */
int initialize_frames(FrameSet *frames, size_t capacity) {

    if (frames == NULL || capacity == 0) {
        return 0;
    }

    frames->pages = NULL;
    frames->capacity = 0;

    if (capacity > SIZE_MAX / sizeof(int)) {
        return 0;
    }

    frames->pages = malloc(capacity * sizeof(int));

    if (frames->pages == NULL) {
        fprintf(stderr, "Frame allocation failed.\n");
        return 0;
    }

    frames->capacity = capacity;

    for (size_t i = 0; i < capacity; i++) {
        frames->pages[i] = EMPTY_FRAME;
    }

    return 1;
}


/* Release allocated frame memory */
void free_frames(FrameSet *frames) {

    if (frames != NULL) {

        free(frames->pages);

        frames->pages = NULL;
        frames->capacity = 0;
    }
}


/* Search for a page in memory */
size_t find_page(const FrameSet *frames, int page) {

    if (frames == NULL || frames->pages == NULL) {
        return SIZE_MAX;
    }

    for (size_t i = 0; i < frames->capacity; i++) {

        if (frames->pages[i] == page) {
            return i;
        }
    }

    return SIZE_MAX;
}


/* Find an empty frame */
size_t find_empty_frame(const FrameSet *frames) {

    if (frames == NULL || frames->pages == NULL) {
        return SIZE_MAX;
    }

    for (size_t i = 0; i < frames->capacity; i++) {

        if (frames->pages[i] == EMPTY_FRAME) {
            return i;
        }
    }

    return SIZE_MAX;
}


/* Display reference string */
void print_reference_string(const ReferenceString *reference) {

    if (reference == NULL || reference->values == NULL) {
        return;
    }

    printf("\nReference String: ");

    for (size_t i = 0; i < reference->length; i++) {
        printf("%d ", reference->values[i]);
    }

    printf("\n");
}


/* Display frame status */
void print_frames(const FrameSet *frames) {

    if (frames == NULL || frames->pages == NULL) {
        return;
    }

    printf("\n--- FRAME STATUS ---\n");

    for (size_t i = 0; i < frames->capacity; i++) {

        printf("Frame %zu: ", i + 1);

        if (frames->pages[i] == EMPTY_FRAME) {
            printf("EMPTY\n");
        } else {
            printf("%d\n", frames->pages[i]);
        }
    }
}
