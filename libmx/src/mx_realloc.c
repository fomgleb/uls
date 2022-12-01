#include "../inc/libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    void *new;

    if (!ptr) {
        new = malloc(size);
    } else {
        // For linux
        // if (malloc_usable_size(ptr) < size) {
        // For macos
        if (malloc_size(ptr) < size) {
            new = malloc(size);
            // For linux
            // mx_memcpy(new, ptr, malloc_usable_size(ptr));
            // For macos
            mx_memcpy(new, ptr, malloc_size(ptr));
            free(ptr);
        } else {
            new = ptr;
        }
    }

    return new;
}

