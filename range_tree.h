#ifndef RANGE_TREE_H
#define RANGE_TREE_H

typedef struct TreeNode TreeNode;

TreeNode* createTree(void*, size_t);
int overlapCheck(TreeNode*, TreeNode*);
void insertNode(TreeNode*, void*, size_t);
void removeNode(TreeNode*, void*, size_t);

#endif
