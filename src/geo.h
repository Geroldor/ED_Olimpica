#ifndef GEO_H
#define GEO_H
#include <stdio.h>
#include <stdlib.h>
#include "spacrbtree.h"

/*
    Geo é um arquivo que contem as informações necessarias para criar as formas geometricas,
    como circulos, retangulos, linhas e textos, e inseri-las na estrutura de dados.
*/

/*Função de leitura do arquivo .geo, que possui as informações necessarias para criar as formas e inseri-las
na estrutura de dados*/
void lerGeo(char* geopath, SpacRbTree t);

#endif