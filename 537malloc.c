#include <stdlib.h>
#include <stdio.h>
#include "range_tree.h"

TreeNode* tree = NULL;

void* malloc537(size_t size) {
    void* ptr = malloc(size);
    updateOverlaps(tree, ptr, size);
    if (size == 0) {
        fprintf(stderr, "Warning: you have allocated a block of size 0.\n");
    } 
    tree = insertNode(tree, ptr, size);
    printTree(tree);
    return ptr;
}

void free537(void* ptr) {

}

void* realloc537(void* ptr, size_t size) {

}

void memcheck537(void* ptr, size_t size) {

}
