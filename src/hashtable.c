#include "hashtable.h"
#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct h{
    char *chave;
    FILE* fstat;
    Value v;
    DescTpValue d;
    struct h *prox;
} hash;

HashTable newHashTable(char *fstat){
    hash *h = (hash *)malloc(sizeof(hash));
    h->chave = NULL;
    h->v = NULL;
    h->d = 0;
    h->prox = NULL;
    h->fstat = fopen(fstat, "w");
    getRelatorioHt(h, "forma, x, y, chave, acao", strlen("forma, x, y, chave, acao"));
    return h;
}

void addHt(HashTable h, char *chave, Value v, DescTpValue d){
    hash *aux = (hash *)h;
    while(aux != NULL){
        aux = aux->prox;
    }
    aux = (hash *)malloc(sizeof(hash));
    aux->chave = chave;
    aux->v = v;
    aux->d = d;
    Lista l = (Lista) v;
    Posic p = getFirst(l);
    char* buff;
    while(p != NIL){
        switch (getTipo(p))
        {
        case 1:
            strcpy(buff, ("r, %lf, %lf, %s, add", getX(p), getY(p), chave));
            getRelatorioHt(h, buff, strlen(buff));
            break;
        
        case 2:
            strcpy(buff, ("c, %lf, %lf, %s, add", getX(p), getY(p), chave));
            getRelatorioHt(h, buff, strlen(buff));
            break;

        case 3:
            strcpy(buff, ("t, %lf, %lf, %lf, %lf, %lf, %lf, %s, add", getX(p), getY(p), getX(getNext(l, p)), getY(getNext(l, p)), getX(getNext(l, getNext(l, p))), getY(getNext(l, getNext(l, p))), chave));
            getRelatorioHt(h, buff, strlen(buff));
            break;

        case 4:
            strcpy(buff, ("q, %lf, %lf, %lf, %lf, %s, add", getX(p), getY(p), getX(getNext(l, p)), getY(getNext(l, p)), chave));
            getRelatorioHt(h, buff, strlen(buff));
            break;

        default:
            break;
        }
        p = getNext(l, p);
    }

}

Value getHt(HashTable h, char *chave, DescTpValue *d){
    hash *aux = (hash *)h;
    while(aux->prox != NULL){
        if(aux->chave == chave){
            return aux->v;
        }
        aux = aux->prox;
    }
}

bool existsHt(HashTable h, char *chave){
    hash *aux = (hash *)h;
    while(aux->prox != NULL){
        if(aux->chave == chave){
            return true;
        }
        aux = aux->prox;
    }
    return false;
}


// gera relatorio da Hashtable no buf
void getRelatorioHt(HashTable h, char *buf, int n){
    hash* ht = (hash*) h;
    //fprintf(ht->fstat, "%s\n", buf);    
}

void killHt(HashTable h){
    hash *aux = (hash *)h;
    while (aux->prox != NULL)
    {
        free(aux);
    }
}


