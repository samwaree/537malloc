#include <stdlib.h>
#include <stdio.h>
#include "range_tree.h"

TreeNode* tree = NULL;

void* malloc537(size_t size) {
    void* ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Error: Out of memory.\n");
        exit(-1);
    }
    updateOverlaps(tree, ptr, size);
    if (size == 0) {
        fprintf(stderr, "Warning: you have allocated a block of size 0.\n");
    } 
    tree = insertNode(tree, ptr, size);
    //printTree(tree);
    return ptr;
}

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
            fprintf(stderr, "Error: pointer was not allocated by malloc537.\n");
            exit(-1);
    }
    //printTree(tree);
}

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
    updateOverlaps(tree, new_ptr, size);
    tree = insertNode(tree, new_ptr, size);
    //printTree(tree);
    return new_ptr;
}

void memcheck537(void* ptr, size_t size) {
    if (!isInnerOverlap(tree, ptr, size)) {
        fprintf(stderr, "Error: Range was not allocated by malloc537() / was already freed.\n");
        fprintf(stderr, "Starting address: %p\nEnding address: %p\n", ptr, ptr + size);
        exit(-1);
    }    
}
