// Written by:
// Logan Mahan, NetID: lmahan, CSID: mahan
// Sam Ware, NetID: sware2, CSID: sware
#include <stdlib.h>
#include <stdio.h>
#include "range_tree.h"

// Self-balancing interval tree containing intervals returned by malloc/realloc
TreeNode* tree = NULL;

/*
 * Safely allocates a pointer of a given size and does appropriate error checking.
 */
void* malloc537(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        return NULL;
    }
    updateOverlaps(tree, ptr, size);
    if (size == 0) {
        fprintf(stderr, "Warning: you have allocated a block of size 0.\n");
    } 
    tree = insertNode(tree, ptr, size);
    return ptr;
}

/*
 * Safely frees a given pointer and does appropriate error checking.
 */
void free537(void* ptr) {
    switch(setFreed(tree, ptr)) {
        case 0:
            free(ptr);
            break;
        case -1:
            fprintf(stderr, "Error: pointer does not point to the first byte allocated by malloc537.\n");
            exit(-1);
        case -2:
            fprintf(stderr, "Error: pointer was already freed.\n");
            exit(-1);
        case -3:
            if (ptr == NULL) {
                fprintf(stderr, "Error: cannot free a NULL pointer.\n");
            } else {
                fprintf(stderr, "Error: pointer was not allocated by malloc537.\n");
            }
            exit(-1);
    }
}

/*
 * This method reallocates the memory indicated by the pointer to a new location plus the indicated
 * size.
 */
void* realloc537(void* ptr, size_t size) {
    if (ptr == NULL) {
        return malloc537(size);
    }
    if (size == 0 && ptr != NULL) {
        free537(ptr);
        return malloc537(size);
    }

    tree = removeNode(tree, ptr);
    void* new_ptr = realloc(ptr, size);
    if (new_ptr == NULL) {
        return NULL;
    }
    updateOverlaps(tree, new_ptr, size);
    tree = insertNode(tree, new_ptr, size);
    return new_ptr;
}

/*
 * Checks to see if the user has access to the memory indicated by the pointer through the pointer
 * plus the indicated size.
 */
void memcheck537(void* ptr, size_t size) {
    if (!isInnerOverlap(tree, ptr, size)) {
        fprintf(stderr, "Error: User cannot access this range of memory.\n");
        fprintf(stderr, "Starting address: %p\nEnding address: %p\n", ptr, ptr + size);
        exit(-1);
    }    
}

