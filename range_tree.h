#ifndef RANGE_TREE_H
#define RANGE_TREE_H

#include "linked_list.h"

typedef struct TreeNode TreeNode;

TreeNode* updateOverlaps(TreeNode*, void*, size_t);
int isInnerOverlap(TreeNode*, void*, size_t);
TreeNode* insertNode(TreeNode*, void*, size_t);
TreeNode* removeNode(TreeNode*, void*);
TreeNode* search(TreeNode*, void*);
void printTree(TreeNode*);
int setFreed(TreeNode*, void*);

#endif
