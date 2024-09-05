//
// Created by Geraldo Neto on 22/06/2024.
//

#include "texto.h"
#include <stdlib.h>
#include <string.h>

typedef struct tex{
    int id;
    double x;
    double y;
    char* info;
    char* tamanho;
    char* deco;
    char* ancora;
    char* familia;
    char* corb;
    char* corp;
} texto;

Texto criarTexto(int id, double x, double y, char* info, char* tamanho, char* deco, char* familia, char* corb, char* corp, char* ancora)
{
    texto* novo = malloc(sizeof(struct tex));
    Texto out;
    novo->id = id;
    novo->x = x;
    novo->y = y;
    novo->info = malloc(sizeof(char)*100);
    strcpy(novo->info, info);
    if(familia == NULL){
        novo->familia = malloc(sizeof(char)*20);
        novo->familia = "sans";
    }else{
        novo->familia = malloc(sizeof(char)*20);
        novo->familia = familia;
    }
    if(tamanho == NULL){
        novo->tamanho = malloc(sizeof(char)*20);
        novo->tamanho = "8pt";
    }else{
        novo->tamanho = malloc(sizeof(char)*20);
        strcpy(novo->tamanho, tamanho);
    }
    if(deco == NULL){
        novo->deco = "l";
    }
    novo->corb = malloc(sizeof(char)*20);
    strcpy(novo->corb, corb);
    novo->corp = malloc(sizeof(char)*20);
    strcpy(novo->corp, corp);
    novo->ancora = malloc(sizeof(char)*2);
    strcpy(novo->ancora, ancora);
    out = novo;
    return out;
}

void textoSetId(Texto set, int id)
{
    texto* tex = (texto*) set;
    tex->id = id;
}

void textoSetX(Texto set, double x)
{
    texto* tex = (texto*) set;
    tex->x = x;
}

void textoSety(Texto set, double y)
{
    texto* tex = (texto*) set;
    tex->y = y;
}

void textoSetInfo(Texto set, char* info)
{
    texto* tex = (texto*) set;
    tex->info = info;
}

void textoSetFamilia(Texto set, char* familia)
{
    texto* tex = (texto*) set;
    tex->familia = familia;
}

void textoSetDeco(Texto set, char* deco)
{
    texto* tex = (texto*) set;
    tex->deco = deco;
}

void textoSetTamanho(Texto set, char* tamanho)
{
    texto* tex = (texto*) set;
    tex->tamanho = tamanho;
}

void textoSetCorb(Texto set, char* corb)
{
    texto* tex = (texto*) set;
    tex->corb = corb;
}

void textoSetCorp(Texto set, char* corp)
{
    texto* tex = (texto*) set;
    tex->corp = corp;
}

void textoSetAncora(Texto set, char* ancora)
{
    texto* tex = (texto*) set;
    tex->ancora = ancora;
}

int textoGetId(Texto get)
{
    texto* tex = (texto*) get;
    return tex->id;
}

double textoGetX(Texto get)
{
    texto* tex = (texto*) get;
    return tex->x;
}

double textoGetY(Texto get)
{
    texto* tex = (texto*) get;
    return tex->y;
}

char* textoGetInfo(Texto get)
{
    texto* tex = (texto*) get;
    return tex->info;
}

char* textoGetDeco(Texto get)
{
    texto* tex = (texto*) get;
    return tex->deco;
}

char* textoGetFamilia(Texto get)
{
    texto* tex = (texto*) get;
    return tex->familia;
}

char* textoGetTamanho(Texto get)
{
    texto* tex = (texto*) get;
    return tex->tamanho;
}

char* textoGetCorb(Texto get)
{
    texto* tex = (texto*) get;
    return tex->corb;
}

char* textoGetCorp(Texto get)
{
    texto* tex = (texto*) get;
    return tex->corp;
}

char* textoGetAncora(Texto get)
{
    texto* tex = (texto*) get;
    return tex->ancora;
}

char* textoGetTexto(Texto get)
{
    texto* tex = (texto*) get;
    return tex->info;
}

void killTexto(Texto get)
{
    texto* tex = (texto*) get;
    free(tex);
}