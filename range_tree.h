#ifndef RANGE_TREE_H
#define RANGE_TREE_H

#include "linked_list.h"

typedef struct TreeNode TreeNode;

int existsInInterval(TreeNode*, void*);
TreeNode* updateOverlaps(TreeNode*, void*, size_t);
int overlapCheck(TreeNode*, TreeNode*);
TreeNode* insertNode(TreeNode*, void*, size_t);
TreeNode* removeNode(TreeNode*, void*);
TreeNode* search(TreeNode*, void*);
void printTree(TreeNode*);
int setFreed(TreeNode*, void*);
int isFreed(TreeNode*);

#endif
