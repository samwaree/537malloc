// Written by:
// Logan Mahan, NetID: lmahan, CSID: mahan
// Sam Ware, NetID: sware2, CSID: sware
#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    void* element;
    struct Node* next;
}Node;

typedef struct LinkedList{
    Node* head;
    Node* tail;
    int size;
}LinkedList;

/*
 * Creates an empty LinkedList
 */
LinkedList* createList() {
    LinkedList* list =  malloc(sizeof(LinkedList));
    if (list == NULL) {
        fprintf(stderr, "Out of memory.\n");
        exit(-1);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

/*
 * Creates a node from the given element
 */
Node* createListNode(void* el) {
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Out of memory.\n");
        exit(-1);
    }
    node->element = el;
    node->next = NULL;
    return node;
}

/*
 * Appends a node to the end of a given list
 */
LinkedList* append(LinkedList* list, void* el) {
    if (el == NULL) {
        fprintf(stderr, "Cannot append NULL element\n");
        return NULL;
    }

    if (list == NULL) {
        list = createList();
        list->head = createListNode(el);
        list->tail = list->head;
        list->size = list->size + 1;
    } else {
        list->tail->next = createListNode(el);
        list->tail = list->tail->next;
        list->size = list->size + 1;
    }
    return list;
}

/*
 * Gets the next node in a list
 */
Node* getNext(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->next; 
}

/*
 * Gets the element from a node
 */
void* getElement(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->element;
}

/*
 * Gets the head from a LinkedList
 */
Node* getHead(LinkedList* list) {
    if (list == NULL) {
        return NULL;
    }
    return list->head;
}
