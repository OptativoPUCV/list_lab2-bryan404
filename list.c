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
    list->current->next->next->prev = x;
    list->current->next = x;
    x->next = list->current->next->next;
    x->prev = list->current;
  }else{
    list->current->next = x;
    x->prev = list->tail;
    list->tail = x;
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
  void* aux = list->current->data;

  //Primer caso será el current que tenga 2 nodos a los lados
  if(list->current->prev !=NULL && list->current->next !=NULL){
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    list->current = list->current->next; //actualizamos el current
  }else{
    //Segundo caso será que el current sea el head
    if(list->current->prev == NULL){
      list->head = list->head->next;
      list->head->prev = NULL;
      list->current = list->head; //actualizamos el current
    }else{ //Tercer caso será que el current sea el tail
      list->tail = list->tail->prev;
      list->tail->next = NULL;
      list->current = list->tail; //actualizamos el current
    }
  }
    return aux;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}