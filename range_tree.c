// Written by:
// Logan Mahan, NetID: lmahan, CSID: mahan
// Sam Ware, NetID: sware2, CSID: sware
#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

enum state_t{freed, allocated};

// Represents a single node in the range tree
typedef struct TreeNode {
    void* low;
    void* high;
    void* max;          // The maximum high value of all intervals in the subtree
    size_t size;
    enum state_t state; // The state of the interval; freed or allocated
    struct TreeNode* parent;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
}TreeNode;

/*
 * This method creates a new TreeNode for insertion into a tree.
 */
TreeNode* createNode(void* ptr, size_t size, TreeNode* parent) {
    TreeNode* node = malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(-1);
    }
    
    // Set all the values of the node to default value
    node->low = ptr;
    node->high = ptr + size;
    node->max = node->high;
    node->size = size;
    node->state = allocated;
    node->parent = parent;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}   

/*
 * This method copies all the information from one node to another.
 */
void copyNode(TreeNode* dest, TreeNode* source) {
    dest->low = source->low;
    dest->high = source->high;
    dest->max = source->max;
    dest->size = source->size;
    dest->state = source->state;
    dest->parent = source->parent;
    dest->left = source->left;
    dest->right = source->right;
    dest->height = source->height;
}

/*
 * Returns true if the node is freed, false otherwise
 */
int isFreed(TreeNode* node) {
    if (node->state == freed) {
        return 1;
    } else {
        return 0;
    }
}

/*
 * Adds all intervals in the tree that overlap with the given interval to a list
 * Runs in O(log(n) + k) time, where k is the number of overlapping intervals
 */
LinkedList* findOverlaps(TreeNode* node, void* low, void* high, LinkedList* list) {
    if (node == NULL) {
        return list;
    }       

    // If the interval overlaps, add it to the list
    if (node->low <= high && low <= node->high) {
        list = append(list, node);
    }

    // If the max of the left subtreee is larger than the pointer, we still
    // need to search the left subtree as well
    if (node->left != NULL && node->left->max >= low) {
        return findOverlaps(node->left, low, high, list);
    }

    return findOverlaps(node->right, low, high, list);
}

/*
 * Return true if the given interval exists completely inside an 
 * allocated interval in the tree
 * Returns false otherwise
 * Runs in O(log(n)) time
 */
int isInnerOverlap(TreeNode* node, void* ptr, size_t size) {
    if (node == NULL) {
        return 0;
    }

    if (node->low <= ptr && (ptr + size) <= node->high && !isFreed(node)) {
        return 1;
    }

    // If the max of the left subtreee is larger than the pointer, we still
    // need to search the left subtree as well
    if (node->left != NULL && node->left->max >= ptr) {
        return isInnerOverlap(node->left, ptr, size);
    }

    return isInnerOverlap(node->right, ptr, size);
}

/*
 * Searches for a given node in the tree.
 * Runs in O(log(n)) time
 */
TreeNode* search(TreeNode* root, void* ptr) {
    // Base case: the node wasn't found
    if (root == NULL) {
        return NULL;
    }
    if (ptr == NULL) {
        return NULL;
    }

    // Standard binary search
    if (ptr < root->low) {
        return search(root->left, ptr);
    } else if (ptr > root->low) {
        return search(root->right, ptr);
    } else {
        return root;
    }
}

/*
 * Returns true if the ptr exists in any interval in the tree
 * Returns false otherwise
 * Runs in O(log(n)) time
 */
int existsInInterval(TreeNode* root, void* ptr) {
    if (root == NULL) {
        return 0;
    }

    if (root->low <= ptr && root->high >= ptr) {
        return 1;
    }

    // If the max of the left subtreee is larger than the pointer, we still
    // need to search the left subtree as well
    if (root->left != NULL && root->left->max >= ptr) {
        return existsInInterval(root->left, ptr);
    }

    return existsInInterval(root->right, ptr);
}

/*
 * Sets the state of a node to freed
 * Returns 0 if the node was freed successfully
 * Returns -1 if the ptr doesn't point to the first byte
 * Returns -2 if the node was already freed
 * Returns -3 if the pointer doesn't exists anywhere
 */
int setFreed(TreeNode* tree, void* ptr) {
    TreeNode* node = search(tree, ptr);
    if (node != NULL) {         // If the ptr exists in the tree
        if (isFreed(node)) {    // It was already freed
            return -2;
        }
        node->state = freed;
        return 0;               // Successful free
    } else {                    // The ptr doesn't exist in the tree
        if (existsInInterval(tree, ptr)) { // ptr was not the first byte of an
            return -1;                     // interval 
        } else {                // ptr doesn't exists in any interval
            return -3;
        }
    }
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
 * Updates the max value of a node by checking the max between the nodes
 * high value, and it's childrens max value
 */
void maxUpdate(TreeNode* node) {
    if(node == NULL) {
        return;
    }
    if (node->left == NULL && node->right == NULL) {
        node->max = node->high;
    } else if (node->left == NULL) {
        node->max = maxUpdateHelper2(node->high, node->right->max);
    } else if (node->right == NULL) {
        node->max = maxUpdateHelper2(node->high, node->left->max);
    } else {
        node->max = maxUpdateHelper3(node->high, node->left->max, node->right->max);
    }
}

/*
 * Updates the max value of all parents of a node
 * Runs in O(log(n))
 */
void maxUpdateParent(TreeNode* node) {
    if (node == NULL) {
        return;
    }
    maxUpdate(node);
    maxUpdateParent(node->parent);
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
 * This method inserts a TreeNode into a given tree and updates the max values 
 * in the tree.
 */
TreeNode* insertNodeHelper(TreeNode* tree, void* ptr, size_t size, TreeNode* parent) {
    if(ptr == NULL) {
        fprintf(stderr, "Null pointer passed in to tree.");
        exit(-1);
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
        fprintf(stderr, "Cannot insert two pointers of the same value.");
        return tree;
    }

    // Updates the height of the current node and checks the balance of the tree.
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
 * Inserts a node into a given tree.
 */
TreeNode* insertNode(TreeNode* node, void* ptr, size_t size) {
    return insertNodeHelper(node, ptr, size, NULL);
}

/*
 * Returns the left-most child from given subtree.
 */
TreeNode* getMinNode(TreeNode* node) {
    TreeNode* curr = node;
    while(curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

/*
 * Removes a node from the tree and updates max values after removal.
 */
TreeNode* removeNodeHelper(TreeNode* tree, TreeNode* node) {
    if(tree == NULL){
        return tree;
    }
    
    // Recursively finds the given node to remove, updating max on the way up
    if (node->low < tree->low) {
        tree->left = removeNodeHelper(tree->left, node);
        maxUpdate(tree);
    } else if (node->low > tree->low) {
        tree->right = removeNodeHelper(tree->right, node);
        maxUpdate(tree);
    } else {
        TreeNode* curr = NULL;
        if ((tree->left == NULL) || (tree->right == NULL)) {
            // The tree has no left and/or no right
            if (tree->left != NULL) {
                curr = tree->left;
            } else {
                curr = tree->right;
            }
            if (curr == NULL) { // No children
                curr = tree;
                tree = NULL;
            } else { // One child
                copyNode(tree, curr);
            }
            free(curr);
        } else {
            // Replace the node with the in-order successor
            curr = getMinNode(tree->right);
            tree->low = curr->low;
            tree->high = curr->high;
            tree->state = curr->state;
            tree->right = removeNodeHelper(tree->right, curr);
        }
    }

    // In the case that the node removed was the only node in the tree.
    if (tree == NULL) {
        return tree;
    }

    // Updates the height of the current node and checks balance of the tree.
    tree->height = 1 + max(getHeight(tree->left), getHeight(tree->right));
    int bal = balance(tree);

    // Left Left
    if (bal > 1 && balance(tree->left) >= 0) {
        return rotateRight(tree);
    }

    // Left Right
    if (bal > 1 && balance(tree->left) < 0) {
        tree->left = rotateLeft(tree->left);
        return rotateRight(tree);
    }

    // Right Right
    if (bal < -1 && balance(tree->right) <= 0) {
        return rotateLeft(tree);
    }

    // Right Left
    if (bal < -1 && balance(tree->right) > 0) {
        tree->right = rotateRight(tree->right);
        return rotateLeft(tree);
    }

    return tree;
}

/*
 * Removes a node from a given tree.
 */
TreeNode* removeNode(TreeNode* root, void* ptr) {
    TreeNode* node = search(root, ptr);
    if (node == NULL) {
        return root;
    } else {
        root = removeNodeHelper(root, node);
        maxUpdate(root);
        return root;
    }
}

/*
 * Updates the intervals to fit the guidelines of malloc
 * If the first byte of a freed node is overlapped, remove the node
 * Else, update the high value of freed node to the ptr
 */
TreeNode* updateOverlaps(TreeNode* tree, void* ptr, size_t size) {
    LinkedList* list = NULL;

    // A list containing all overlapping intervals
    list = findOverlaps(tree, ptr, ptr + size, list);

    Node* curr = getHead(list);
    while(curr != NULL) { // Get each node in the list
        TreeNode* node = getElement(curr);
        if (ptr <= node->low && isFreed(node)) {
            // The new ptr overlaps the first byte, so we can remove it
            tree = removeNodeHelper(tree, node);
            maxUpdate(tree);
        } else {
            if (isFreed(node)) {
                // The new ptr does not overlap the first byte
                // Update the high value for error checking
                node->high = ptr;
                maxUpdateParent(node);
            }
        }
        Node* temp = curr;
        curr = getNext(curr);
        free(temp);
    }
    free(list);
    return tree;
}

/*
 * Recursive method to print out the tree in a readable format
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
    if (root->state == freed) {
        printf("F: %p, [%p,%p]\n", root->max, root->low, root->high);
    } else {
        printf("A: %p, [%p,%p]\n", root->max, root->low, root->high);
    }
    printTreeUtil(root->left, space);
}

/*
 * Prints out the tree in a readable format
 */
void printTree(TreeNode* tree) {
    printTreeUtil(tree, 0);
}

