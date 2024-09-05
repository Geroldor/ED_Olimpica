#ifndef TRABALHOED_RETANGULO_H
#define TRABALHOED_RETANGULO_H

/**
 * Retangulo é um ponteiro para uma estrutura que contém um retangulo.
 * O retangulo é definido por um id, uma base, uma altura, um x, um y, uma cor de borda e uma cor de preenchimento.
 * O id é um inteiro que identifica o retangulo.
 * A base é um double que representa a base do retangulo.
 * A altura é um double que representa a altura do retangulo.
 * O x é um double que representa a coordenada x do retangulo.
 * O y é um double que representa a coordenada y do retangulo.
 * A cor de borda é uma string que representa a cor da borda do retangulo.  
 * A cor de preenchimento é uma string que representa a cor de preenchimento do retangulo.
 * 
 * 
 */

typedef void* Retangulo;

Retangulo criarRetangulo(int id, double base, double altura, double x, double y, char* corb, char* corp);

/*As Funções set alteram os valores das respectivas variaveis que elas referem, isso é necessario devido
ao void* impossibilitar o acesso direto aos dados das structs*/

void retanguloSetId(int id, Retangulo set);

void retanguloSetBase(double base, Retangulo set);

void retanguloSetAltura(double altura, Retangulo set);

void retanguloSetX(double x, Retangulo set);

void retanguloSetY(double y, Retangulo set);

void retanguloSetCorBorda(char* corb, Retangulo set);

void retanguloSetCorPreenchimento(char* corp, Retangulo set);

/*As Funções get retornam os valores das respectivas variaveis que elas referem, isso é necessario devido
ao void* impossibilitar o acesso direto aos dados das structs*/

int retanguloGetId(Retangulo get);

double retanguloGetBase(Retangulo get);

double retanguloGetAltura(Retangulo get);

double retanguloGetX(Retangulo get);

double retanguloGetY(Retangulo get);

char* retanguloGetCorBorda(Retangulo get);

char* retanguloGetCorPreenchimento(Retangulo get);
#endif //TRABALHOED_RETANGULO_H
