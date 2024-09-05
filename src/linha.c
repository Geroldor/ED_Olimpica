//
// Created by Geraldo Neto on 21/06/2024.
//

#include "linha.h"
#include <stdlib.h>
#include <string.h>

typedef struct lin {
    int id;
    double x1;
    double x2;
    double y1;
    double y2;
    char* cor;
}linha;

Linha criarLinha(int id, double x1, double x2, double y1, double y2, char* cor)
{
    linha* novo = malloc(sizeof(struct lin));
    Linha out;
    novo->id = id;
    novo->x1 = x1;
    novo->x2 = x2;
    novo->y1 = y1;
    novo->y2 = y2;
    novo->cor = malloc(sizeof(char)*20);
    strcpy(novo->cor, cor);
    out = novo;
    return out;
}

void linhaSetId(Linha set, int id)
{
    linha* lin = (linha*) set;
    lin->id = id;
}

void linhaSetX1(Linha set, double x1)
{
    linha* lin = (linha*) set;
    lin->x1 = x1;
}

void linhaSetX2(Linha set, double x2)
{
    linha* lin = (linha*) set;
    lin->x2 = x2;
}

void linhaSetY1(Linha set, double y1)
{
    linha* lin = (linha*) set;
    lin->y1 = y1;
}

void linhaSetY2(Linha set, double y2)
{
    linha* lin = (linha*) set;
    lin->y2 = y2;
}

void linhaSetCor(Linha set, char* cor)
{
    linha* lin = (linha*) set;
    lin->cor = cor;
}

int linhaGetId(Linha get)
{
    linha* lin = (linha*) get;
    return lin->id;
}

double linhaGetX1(Linha get)
{
    linha* lin = (linha*) get;
    return lin->x1;
}

double linhaGetX2(Linha get)
{
    linha* lin = (linha*) get;
    return lin->x2;
}

double linhaGetY1(Linha get)
{
    linha* lin = (linha*) get;
    return lin->y1;
}

double linhaGetY2(Linha get)
{
    linha* lin = (linha*) get;
    return lin->y2;
}

char* linhaGetCor(Linha get)
{
    linha* lin = (linha*) get;
    return lin->cor;
}