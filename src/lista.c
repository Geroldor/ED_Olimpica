#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

typedef struct listanode{
    Item info;
    double x, y;
    int tipo;
    struct listanode *prox;
} listanode;

typedef struct lista{
    listanode *head;
    listanode *tail;
    int length;
    int maxLength;
} lista;

Lista createLista(int capacidade){
    lista *L = (lista*)malloc(sizeof(lista));
    L->head = NULL;
    L->tail = NULL;
    L->length = 0;
    L->maxLength = capacidade;
    return L;
}

int length(Lista L){
    lista *l = (lista*)L;
    return l->length;
}

int maxLength(Lista L){
    lista *l = (lista*)L;
    return l->maxLength;
}

bool isEmpty(Lista L){
    lista *l = (lista*)L;
    return l->length == 0;
}

bool isFull(Lista L){
    lista *l = (lista*)L;
    return l->length == l->maxLength;
}

Posic insert(Lista L, Item info, int tipo){
    lista *l = (lista*)L;
    if(isFull(L)){
        return NIL;
    }
    listanode *n = (listanode*)malloc(sizeof(listanode));
    n->info = info;
    n->prox = NULL;
    n->tipo = tipo;
    n->x = 0;
    n->y = 0;
    if(isEmpty(L)){
        l->head = n;
        l->tail = n;
    }else{
        l->tail->prox = n;
        l->tail = n;
    }
    l->length++;
    return n;
}

Item pop(Lista L){
    lista *l = (lista*)L;
    if(isEmpty(L)){
        return NIL;
    }
    listanode *n = l->head;
    Item info = n->info;
    l->head = n->prox;
    free(n);
    l->length--;
    return info;
}

void remover(Lista L, Posic p){
    lista *l = (lista*)L;
    if(isEmpty(L)){
        return;
    }
    listanode *n = (listanode*)p;
    if(n == l->head){
        l->head = n->prox;
    }else{
        listanode *aux = l->head;
        while(aux->prox != n){
            aux = aux->prox;
        }
        aux->prox = n->prox;
    }
    free(n);
    l->length--;
}

Item get(Lista L, Posic p){
    listanode *n = (listanode*)p;
    return n->info;
}

Posic insertBefore(Lista L, Posic p, Item info){
    lista *l = (lista*)L;
    if(isFull(L)){
        return NIL;
    }
    listanode *n = (listanode*)p;
    listanode *new = (listanode*)malloc(sizeof(listanode));
    new->info = info;
    new->prox = n;
    if(n == l->head){
        l->head = new;
    }else{
        listanode *aux = l->head;
        while(aux->prox != n){
            aux = aux->prox;
        }
        aux->prox = new;
    }
    l->length++;
    return new;
}

Posic insertAfter(Lista L, Posic p, Item info){
    lista *l = (lista*)L;
    if(isFull(L)){
        return NIL;
    }
    listanode *n = (listanode*)p;
    listanode *new = (listanode*)malloc(sizeof(listanode));
    new->info = info;
    new->prox = n->prox;
    n->prox = new;
    if(n == l->tail){
        l->tail = new;
    }
    l->length++;
    return new;
}

Posic getFirst(Lista L){
    lista *l = (lista*)L;
    return l->head;
}

Posic getNext(Lista L, Posic p){
    listanode *n = (listanode*)p;
    if (n->prox == NULL || n == NULL)
    {
        return NULL;
    }else{
        return n->prox;
    }
    
}

Posic getLast(Lista L){
    lista *l = (lista*)L;
    return l->tail;
}

Posic getPrevious(Lista L, Posic p){
    lista *l = (lista*)L;
    listanode *n = (listanode*)p;
    if(n == l->head){
        return NIL;
    }
    listanode *aux = l->head;
    while(aux->prox != n){
        aux = aux->prox;
    }
    return aux;
}

void alterX(Posic p, double x){
    listanode *n = (listanode*)p;
    n->x = x;
}

void alterY(Posic p, double y){
    listanode *n = (listanode*)p;
    n->y = y;
}

double getX(Posic p){
    listanode *n = (listanode*)p;
    return n->x;
}

double getY(Posic p){
    listanode *n = (listanode*)p;
    return n->y;
}

int getTipo(Posic p){
    listanode *n = (listanode*)p;
    return n->tipo;
}

void killLista(Lista L){
    lista* l = (lista*) L;
    listanode* n = l->head;
    while (n->prox != NULL)
    {
       free(n);
    }
    free(l);
}