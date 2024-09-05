#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "retangulo.h"

typedef struct r{
    int id;
    double base;
    double altura;
    double x;
    double y;
    char* corb;
    char* corp;
} retangulo;

Retangulo criarRetangulo(int id, double base, double altura, double x, double y, char* corb, char* corp)
{
    retangulo* novo = malloc(sizeof(struct r));
    Retangulo ret;
    novo->id = id;
    novo->base = base;
    novo->altura = altura;
    novo->x = x;
    novo->y = y;
    novo->corb = malloc(sizeof(char)*20);
    strcpy(novo->corb, corb);
    novo->corp = malloc(sizeof(char)*20);
    strcpy(novo->corp, corp);
    ret = novo;
    return ret;
}

void retanguloSetId(int id, Retangulo set){
    retangulo* ret = (retangulo*) set;
    ret->id = id;
}

void retanguloSetBase(double base, Retangulo set){
    retangulo* ret = (retangulo*) set;
    ret->base = base;
}

void retanguloSetAltura(double altura, Retangulo set){
    retangulo* ret = (retangulo*) set;
    ret->altura = altura;
}

void retanguloSetX(double x, Retangulo set){
    retangulo* ret = (retangulo*) set;
    ret->x = x;
}

void retanguloSetY(double y, Retangulo set){
    retangulo* ret = (retangulo*) set;
    ret->y = y;
}

void retanguloSetCorBorda(char* corb, Retangulo set){
    retangulo* ret = (retangulo*) set;
    ret->corb = corb;
}

void retanguloSetCorPreenchimento(char* corp, Retangulo set){
    retangulo* ret = (retangulo*) set;
    ret->corp = corp;
}

int retanguloGetId(Retangulo get){
    retangulo* ret = (retangulo*) get;
    return ret->id;
}

double retanguloGetBase(Retangulo get){
    retangulo* ret = (retangulo*) get;
    return ret->base;
}

double retanguloGetAltura(Retangulo get){
    retangulo* ret = (retangulo*) get;
    return ret->altura;
}

double retanguloGetX(Retangulo get){
    retangulo* ret = (retangulo*) get;
    return ret->x;
}

double retanguloGetY(Retangulo get){
    retangulo* ret = (retangulo*) get;
    return ret->y;
}

char* retanguloGetCorBorda(Retangulo get){
    retangulo* ret = (retangulo*) get;
    return ret->corb;
}

char* retanguloGetCorPreenchimento(Retangulo get){
    retangulo* ret = (retangulo*) get;
    return ret->corp;
}