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

Node* createNode(void* el) {
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
        list->head = createNode(el);
        list->tail = list->head;
        list->size++;
    } else {
        list->tail->next = createNode(el);
        list->tail = list->tail->next;
        list->size++;
    }
}

Node* getNext(Node* node) {
    return node->next;
}

Node* getElement(Node* node) {
    return node->element;
}
