#include <stdlib.h>
#include <stdio.h>
#include "range_tree.h"

int main() {
    int* ptr = malloc(sizeof(int));
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
}
