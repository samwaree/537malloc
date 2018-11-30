#ifndef RANGE_TREE_H
#define RANGE_TREE_H

typedef struct TreeNode TreeNode;

int overlapCheck(TreeNode*, TreeNode*);
TreeNode* insertNode(TreeNode*, void*, size_t);
TreeNode* removeNode(TreeNode*, void*);
TreeNode* search(TreeNode*, void*);
void printTree(TreeNode*);

#endif
