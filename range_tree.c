#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode {
    void* low;
    void* high;
    void* max;
    size_t size;
    struct TreeNode* parent;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

TreeNode* createNode(void* ptr, size_t size, TreeNode* parent) {
    TreeNode* node = malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(-1);
    }
    node->low = ptr;
    node->high = ptr + size;
    node->max = node->high;
    node->size = size;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* createTree(void* ptr, size_t size) {
    return createNode(ptr, size, NULL);
}   

void insertNode(TreeNode* tree, void* ptr, size_t size) {
    if(tree == NULL){
	tree = createTree(ptr, size);
	return;
    }
    // placeholder for treenode = null
    TreeNode* newNode = NULL;
    TreeNode* currNode = tree;
    // iterate through left and right sides of tree until placeholder node is not null
    // call balance after setting currNode's children?
    while(newNode == NULL) {
	if(ptr < currNode->low) {
	    if(currNode->left == NULL) {
	        newNode = createNode(ptr, size, currNode);
	        currNode->left = newNode;
		return;
	    } else {
		currNode = currNode->left;
	    }
	} else if(ptr > currNode->low) {
	    if(currNode->right == NULL) {
    		newNode = createNode(ptr, size, currNode);
		currNode->right = newNode;
		return;
	    } else {
		currNode = currNode->right;
    	    }
	}	    
    }

    // implement shifting to ensure balanced tree
}

void removeNode(TreeNode* tree, void* ptr, size_t size) {

}
