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

/*
 * This method evaluates whether or not there is overlap in the tree between two nodes.
 * Returns -1 if node being passed in is NULL.
 * Returns 0 if no overlap.
 * Returns 1 if overlap exists.
 */
int overlapCheck(TreeNode* node1, TreeNode* node2) {
    if(node1 == NULL || node2 == NULL) {
	return -1;
    }

    if((node1->low <= node2->high) && (node2->low <= node1->high)) {
        return 1;
    }

    if((node1->left != NULL) && (node1->left->max >= node2->low)) {
        return overlapCheck(node1->left, node2);
    } else if(node2->right != NULL) {
    	return overlapCheck(node1->right, node2);
    }

    return 0;
}

/*
 * This method inserts a TreeNode into a given tree, updates the max value in the tree if needed,
 * and checks for overlap in the tree.
 */
void insertNode(TreeNode* tree, void* ptr, size_t size) {
    if(tree == NULL){
	tree = createTree(ptr, size);
	return;
    }

    TreeNode* newNode = NULL;  // This is a placeholder for the new node being added to the tree.
    TreeNode* currNode = tree; // This keeps track of the current node being iterated on.
    
    // call balance after setting currNode's children?
    // also have to call overlapping to see if the interval of new node will overlap with root
    
    // Iterate through the left and right halves of the tree until a point is reached where
    // the new node can be added.
    while(newNode == NULL) {
	// If the pointer address is less than the current node's address.
        if(ptr < currNode->low) {
	    if(currNode->left == NULL) {
	        newNode = createNode(ptr, size, currNode);
	        currNode->left = newNode;
	    } else {
		currNode = currNode->left;
	    }
	// If the pointer address is greater than the current node's address.
	} else if(ptr > currNode->low) {
	    if(currNode->right == NULL) {
    		newNode = createNode(ptr, size, currNode);
		// Check and set new max high
		if(currNode->max < newNode->high){
		    currNode->max = newNode->high;
		}
		currNode->right = newNode;
	    } else {
		// Check and set new max high if needed
		if(currNode->max < ptr + size) {
		    currNode->max = ptr + size;
	        }
		currNode = currNode->right;
    	    }
	}	    
    }

    return;
    // implement shifting to ensure balanced tree
}

void removeNode(TreeNode* tree, void* ptr, size_t size) {

}
