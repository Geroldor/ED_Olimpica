//
// Created by Geraldo Neto on 21/06/2024.
//

#ifndef TRABALHOED_LINHA_H
#define TRABALHOED_LINHA_H

typedef void* Linha;

/**
 * 
 * 
 * Linha contém as informações de uma linha, sendo elas: id, coordenadas X e Y de seus pontos inicial e final e cor.
 * id é um identificador unico para cada linha, 
 * coordenadas X e Y são as coordenadas dos pontos inicial e final da linha,
 * cor é a cor da linha.
 */

/*Cria e define a forma de uma linha no projeto, a Linha possui cor, 
e coordenadas X e Y de seus pontos inicial e final*/
Linha criarLinha(int id, double x1, double x2, double y1, double y2, char* cor);

/*As Funções set alteram os valores das respectivas variaveis que elas referem, isso é necessario devido
ao void* impossibilitar o acesso direto aos dados das structs*/

//define o id da linha
void linhaSetId(Linha set, int id);

//define a coordenada X do ponto inicial da linha
void linhaSetX1(Linha set, double x1);

//define a coordenada X do ponto final da linha
void linhaSetX2(Linha set, double x2);

//define a coordenada Y do ponto inicial da linha
void linhaSetY1(Linha set, double y1);

//define a coordenada Y do ponto final da linha
void linhaSetY2(Linha set, double y2);

//define a cor da linha
void linhaSetCor(Linha set, char* cor);

/*As Funções get retornam os valores das respectivas variaveis que elas referem, isso é necessario devido
ao void* impossibilitar o acesso direto aos dados das structs*/

//retorna o id da linha
int linhaGetId(Linha get);

//retorna a coordenada X do ponto inicial da linha
double linhaGetX1(Linha get);

//retorna a coordenada X do ponto final da linha
double linhaGetX2(Linha get);

//retorna a coordenada Y do ponto inicial da linha
double linhaGetY1(Linha get);

//retorna a coordenada Y do ponto final da linha
double linhaGetY2(Linha get);

//retorna a cor da linha
char* linhaGetCor(Linha get);

#endif //TRABALHOED_LINHA_H
