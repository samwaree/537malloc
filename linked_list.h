#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node Node;
typedef struct LinkedList LinkedList;

LinkedList* createList();
void append(LinkedList*, void*);
Node* getNext(Node*);
Node* getHead(LinkedList*);
void* getElement(Node*);

#endif
