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

Node* createListNode(void* el) {
    Node* node = malloc(sizeof(node));
    if (node == NULL) {
        fprintf(stderr, "Out of memory.\n");
        exit(-1);
    }
    node->element = el;
    node->next = NULL;
    return node;
}

void append(LinkedList* list, void* el) {
    if (list == NULL) {
        fprintf(stderr, "List is null.\n");
        return;   
    }
    if (el == NULL) {
        fprintf(stderr, "Cannot append NULL element\n");
        return;
    }

    if (list->size == 0) {
        list->head = createListNode(el);
        list->tail = list->head;
        list->size++;
    } else {
        list->tail->next = createListNode(el);
        list->tail = list->tail->next;
        list->size = list->size + 1;
    }
}

Node* getNext(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->next; 
}

void* getElement(Node* node) {
    if (node == NULL) {
        return NULL;
    }
    return node->element;
}

Node* getHead(LinkedList* list) {
    if (list == NULL) {
        return NULL;
    }
    return list->head;
}
