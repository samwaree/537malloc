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
    int height;
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
    node->height = 1;
    return node;
}

// Don't use anymore.
TreeNode* createTree(void* ptr, size_t size) {
    return createNode(ptr, size, NULL);
}   

int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

/*
 * This method returns the balance factor between the two subtrees rooted at the given node.
 */
int balance(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return node->left->height - node->right->height;
}

/*
 * This method performs a left rotate on a subtree with TreeNode root as its root node.
 */
TreeNode* rotateLeft(TreeNode* node) {
    TreeNode* a = node->right;
    TreeNode* b = a->left;

    a->left = node;
    node->right = b;

    node->height = max(node->left->height, node->right->height) + 1;
    a->height = max(a->left->height, a->right->height) + 1;

    return a;
}

/*
 * This method performs a right rotate on a subtree with TreeNode root as its root node.
 */
TreeNode* rotateRight(TreeNode* node) {
    TreeNode* a = node->left;
    TreeNode* b = a->right;

    a->right = node;
    node->left = b;

    node->height = max(node->left->height, node->right->height) + 1;
    a->height = max(a->left->height, a->right->height) + 1;

    return a;
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

void maxUpdate(TreeNode* node) {
    if (node->left != NULL && node->left->max > node->max) {
	node->max = node->left->max;
    }
    if (node->right != NULL && node->right->max > node->max) {
	node->max = node->right->max;
    }
}


/*
 * This method inserts a TreeNode into a given tree, updates the max value in the tree if needed,
 * and checks for overlap in the tree.
 */
void insertNode(TreeNode* tree, void* ptr, size_t size, TreeNode* parent) {
    // Print error statement here?
    if(ptr == NULL){
	fprintf(stderr, "Null pointer passed in.");
	return;
    }

    if(tree == NULL){
	tree = createNode(ptr, size, parent);
    }

/*    TreeNode* newNode = NULL;  // This is a placeholder for the new node being added to the tree.
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
		currNode->left->max = newNode->high;
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
*/
    // Update max value
    if (ptr + size > tree->max) {
	tree->max = ptr + size;
    }

    if (ptr < tree->low) {
	
	insertNode(tree->left, ptr, size, tree);
    } else if (ptr > tree->low) {
	insertNode(tree->right, ptr, size, tree);
    // In the case that the ptrs are equal
    } else {
	fprintf(stderr, "Tried to insert two pointers of the same value.");
        return;
    }

    tree->height = max(tree->left->height, tree->right->height) + 1;

    int bal = balance(tree);
    
    // Left Left    
    if (bal > 1 && ptr < tree->left->low) {
	rotateRight(tree);
    }

    // Right Right
    if (bal < -1 && ptr > tree->right->low) {
	rotateLeft(tree);
    }

    // Left Right
    if (bal > 1 && ptr > tree->left->low) {
	rotateLeft(tree->left);
	rotateRight(tree);
    }

    // Right Left
    if (bal < -1 && ptr < tree->right->low) {
	rotateRight(tree->right);
	rotateLeft(tree);
    }

    return;
}

void removeNode(TreeNode* tree, void* ptr, size_t size) {

}
