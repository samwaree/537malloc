# **537malloc**
Safe malloc/free written for CS537: Introduction to Operating Systems

# **Citations**
This program was designed to ensure the proper allocation and freeing of memory using the  malloc, realloc, and free commands. The following web pages were used as references while building this program:

These were used to gain an understanding of how to correctly build an interval tree:
https://en.wikipedia.org/wiki/Interval_tree

https://www.geeksforgeeks.org/interval-tree/


These were used to correcly implement a self-balancing binary search tree.
https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

https://www.geeksforgeeks.org/avl-tree-set-2-deletion/

# **File Overview**
## **537malloc**
This file contains the main methods utilized in this program. The malloc537 and realloc537 methods exhibit appropriate error checking while allocating and reallocating memory stored in a self-balancing binary search tree. On the other hand, free537, after error checking, deallocates memory stored in the same binary search tree and returns the updated balanced tree to the user. Finally, the memcheck537 method searches the tree for the pointer passed in by the user and verifies whether or not the user has access to that memory location.

## **Range Tree**
This file contains a custom TreeNode struct that is used to keep track of memory allocation and other nodes sorted in a self-balancing binary search tree. The main methods utilized in this file are insertNode and removeNode methods. These properly add and remove, respectively, a node (whose contents keep track of memory allocated by the user) from the binary search tree and call appropriate balancing methods to keep the height of the tree relatively uniform.

## **Linked List**
This file contains a custom LinkedList struct as well as various methods used to create a linked list of nodes.
