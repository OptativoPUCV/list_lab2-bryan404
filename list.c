#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = (void*)data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * x = (List*)malloc(sizeof(List));

  x->head = NULL;
  x->tail = NULL;
  x->current = NULL;
     return x;
}

void * firstList(List * list) {

  if(list->head && list->head->data){
  list->current = list->head;
  return list->head->data;
  }

  return NULL;
}

void * nextList(List * list) {

  if(list->current && list->current->next && list->current->next->data){
    list->current = list->current->next;
    return list->current->data;
  }
    return NULL;
}

void * lastList(List * list) {

  if(list->tail && list->tail->data){
    list->current = list->tail;
    return list->tail->data;
  }

    return NULL;
}

void * prevList(List * list) {

  if(list->current && list->current->prev && list->current->prev->data){
    list->current = list->current->prev;
    return list->current->data;
  }
    return NULL;
}

void pushFront(List * list, const void * data) {
  Node* x = createNode(data);
  if(list->head == NULL){
    //list->head = x; <- no es necesario
    list->tail = x;
  }else{
    list->current = list->head;
    list->head->prev = x;
  }
  list->head=x;
  list->head->next = list->current;

  //printf(" AAAAAAA %d AAAAAAAA",(char) list->head->data);
}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  Node* x = createNode(data);
  if(list->current->next){
    list->current->next = x;
    x->next = list->current->next->next;
    x->prev = list->current;
    list->current->next->next->prev = x;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}