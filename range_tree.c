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

/*
* Returns the max of two ints
*/
int max(int a, int b) {
	if (a > b) return a;
	else return b;
}

/*
* Returns the height of given node; 0 if node is null
*/
int getHeight(TreeNode* node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

/*
 * This method returns the balance factor between the two subtrees rooted at the given node.
 */
int balance(TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

/*
* Returns the max of three void pointers
*/
void* maxUpdateHelper3(void* a, void* b, void* c) {
    void* max = a;
    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}

/*
* Returns the max of two void pointers
*/
void* maxUpdateHelper2(void* a, void* b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }    
}

/*
* Updates the max value of a node
*/
void maxUpdate(TreeNode* node) {
    if (node->left == NULL && node->right == NULL) {
        node->max = node->high;
    } else if (node->left == NULL) {
        node->max = maxUpdateHelper2(node->high, node->right);
    } else if (node->right == NULL) {
        node->max = maxUpdateHelper2(node->high, node->left);
    } else {
        node->max =  maxUpdateHelper3(node->high, node->left->max, node->right->max);
    }
}

/*
 * This method performs a left rotate on a subtree with TreeNode root as its root node.
 */
TreeNode* rotateLeft(TreeNode* node) {
    TreeNode* a = node->right;
    TreeNode* b = a->left;

    a->left = node;
    node->right = b;
    
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;
    
    //Updates the max values so they are correct after rotate
    maxUpdate(node);
    maxUpdate(a);

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

    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    a->height = max(getHeight(a->left), getHeight(a->right)) + 1;

    //Updates the max values so they are correct after rotate
    maxUpdate(node);
    maxUpdate(a);

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



/*
 * This method inserts a TreeNode into a given tree, updates the max value in the tree if needed,
 * and checks for overlap in the tree.
 */
TreeNode* insertNodeHelper(TreeNode* tree, void* ptr, size_t size, TreeNode* parent) {
    // Print error statement here?
    if(ptr == NULL) {
	fprintf(stderr, "Null pointer passed in.");
	return;
    }

    if(tree == NULL){
	    tree = createNode(ptr, size, parent);
        return tree;
    }

    // Update max value
    if (ptr + size > tree->max) {
	tree->max = ptr + size;
    }

    if (ptr < tree->low) {
	    tree->left = insertNodeHelper(tree->left, ptr, size, tree);
    } else if (ptr > tree->low) {
	    tree->right = insertNodeHelper(tree->right, ptr, size, tree);
    // In the case that the ptrs are equal
    } else {
	fprintf(stderr, "Tried to insert two pointers of the same value.");
        return;
    }

    tree->height = max(getHeight(tree->left), getHeight(tree->right)) + 1;

    int bal = balance(tree);
    
    // Left Left    
    if (bal > 1 && ptr < tree->left->low) {
	return rotateRight(tree);
    }

    // Right Right
    if (bal < -1 && ptr > tree->right->low) {
	return rotateLeft(tree);
    }

    // Left Right
    if (bal > 1 && ptr > tree->left->low) {
	tree->left = rotateLeft(tree->left);
	return rotateRight(tree);
    }

    // Right Left
    if (bal < -1 && ptr < tree->right->low) {
	tree->right = rotateRight(tree->right);
	return rotateLeft(tree);
    }

    return tree;
}

/*
* 
*/
TreeNode* insertNode(TreeNode* node, void* ptr, size_t size) {
    return insertNodeHelper(node, ptr, size, NULL);
}

void removeNode(TreeNode* tree, void* ptr, size_t size) {

}

/*
* Prints out the tree in a readable format
*/
void printTreeUtil(TreeNode* root, int space) {
    if (root == NULL) {
        return;
    }

    space += 14;

    printTreeUtil(root->right, space);

    printf("\n");
    for (int i = 14; i < space; i++) {
        printf(" ");
    }
    printf("%p, [%p,%p]\n", root->max, root->low, root->high);
    

    printTreeUtil(root->left, space);
}

/*
* Prints out the tree in a readable format
*/
void printTree(TreeNode* tree) {
    printTreeUtil(tree, 0);
}

