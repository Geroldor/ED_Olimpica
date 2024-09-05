//
// Created by Geraldo Neto on 21/06/2024.
//

#include "circulo.h"
#include <stdio.h>
#include <string.h>

typedef struct cir{
    int id;
    double diametro;
    double x;
    double y;
    char* corb;
    char* corp;
} circulo;

Circulo criarCirculo(int id, double diametro, double x, double y, char* corb, char* corp)
{
    circulo* novo = malloc(sizeof(struct cir));
    Circulo out;
    novo->id = id;
    novo->diametro = diametro;
    novo->x = x;
    novo->y = y;
    novo->corb = malloc(sizeof(char)*20);
    strcpy(novo->corb, corb);
    novo->corp = malloc(sizeof(char)*20);
    strcpy(novo->corp, corp);
    out = novo;
    return out;
}

void circuloSetId(Circulo set, int id){
    circulo* cir = (circulo*) set;
    cir->id = id;
}


void circuloSetDiametro(Circulo set, double diametro){
    circulo* cir = (circulo*) set;
    cir->diametro = diametro;
}


void circuloSetX(Circulo set, double x){
    circulo* cir = (circulo*) set;
    cir->x = x;
}


void circuloSetY(Circulo set, double y){
    circulo* cir = (circulo*) set;
    cir->y = y;
}


void circuloSetCorBorda(Circulo set, char* corb){
    circulo* cir = (circulo*) set;
    cir->corb = corb;
}

void circuloSetCorPreenchimento(Circulo set, char* corp){
    circulo* cir = (circulo*) set;
    cir->corp = corp;
}

int circuloGetId(Circulo get){
    circulo* cir = (circulo*) get;
    return cir->id;
}

double circuloGetRaio(Circulo get){
    circulo* cir = (circulo*) get;
    return cir->diametro;
}

double circuloGetX(Circulo get){
    circulo* cir = (circulo*) get;
    return cir->x;
}

double circuloGetY(Circulo get){
    circulo* cir = (circulo*) get;
    return cir->y;
}

char* circuloGetCorBorda(Circulo get){
    circulo* cir = (circulo*) get;
    return cir->corb;
}

char* circuloGetCorPreenchimento(Circulo get){
    circulo* cir = (circulo*) get;
    return cir->corp;
}