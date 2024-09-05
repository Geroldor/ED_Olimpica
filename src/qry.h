#ifndef QRY_H
#define QRY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "spacrbtree.h"
#include "hashtable.h"

/**
 * Query é um arquivo que contem comandos para realizar ações sobre as figuras geométricas inseridas na arvore.
 * As ações são: selecionar figuras, preparar figuras, deletar figuras e clonar figuras.
 */


/**
 * Seleciona figuras que estão dentro de um retangulo.
 * 
 */
void sel(SpacRbTree t, HashTable ht, char* nome, double x, double y, double w, double h);

/**
 * Prepara figuras dentro de uma seleção para efetuarem um disparo a distancia @param dist
 * com angulo @param grs.
 * 
 */
void prep(HashTable ht, char* nome, double grs, double dist);


/**
 * Deleta uma figura da arvore.
 * 
 */
void del(HashTable ht, char* nome);

/**
 * Efetua um disparo e clona as figuras atingidas, inserindo elas na arvore com posição @param dx e @param dy.
 * 
 */
void clone(char* nome, int id, double dx, double dy, FILE* rel, SpacRbTree t, HashTable ht);

/**
 * Efetua um disparo e deleta as figuras atingidas, removendo elas da arvore
 * 
 */
void disp(SpacRbTree t, HashTable ht, char* nome, FILE* rel);

#endif