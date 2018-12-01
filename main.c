#include <stdlib.h>
#include <stdio.h>
#include "537malloc.h"

int main() {
/*    int* ptr = malloc(sizeof(int));
    TreeNode* tree = insertNode(tree, ptr, sizeof(int));
    int* ptr1 = malloc(sizeof(int) * 3);
    char* ptr3 = malloc(sizeof(char) * 8);
    int* ptr4 = malloc(sizeof(int));
    char** ptr5 = malloc(sizeof(char*) * 8);
    tree = insertNode(tree, ptr5, sizeof(char*) * 8);
    tree = insertNode(tree, ptr4, sizeof(int));   
    tree = insertNode(tree, ptr3, 8 * sizeof(char));
    tree = insertNode(tree, ptr1, sizeof(int) * 3);
    tree = insertNode(tree, malloc(sizeof(int) * 10), sizeof(int) * 10);
    tree = insertNode(tree, malloc(sizeof(char) * 200), sizeof(char) * 200);
    printTree(tree);
    printf("Does %p exist in interval: %d\n", ptr5 + 1, existsInInterval(tree, ptr5 + 1));

    printf("Does %p exist in interval: %d\n", ptr5 + 9, existsInInterval(tree, ptr5 + 9));
    printf("Freed value: %d\n", setFreed(tree, ptr1));
    printf("Freed value: %d\n", setFreed(tree, ptr1 +1));
    printf("Freed value: %d\n", setFreed(tree, ptr1));
    printf("Freed value; %d\n", setFreed(tree, 100));
    tree = updateOverlaps(tree, ptr1 + 1, sizeof(int));
    tree = insertNode(tree, ptr1 + 1, sizeof(int));
    printTree(tree);*/ 
    int* test = malloc537(sizeof(int));
    char* string = malloc537(sizeof(char) * 20);
    memcheck537(test, sizeof(int));
    memcheck537(test + 10000, sizeof(int));
}
