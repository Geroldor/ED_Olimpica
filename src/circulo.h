//
// Created by Geraldo Neto on 21/06/2024.
//

#ifndef TRABALHOED_CIRCULO_H
#define TRABALHOED_CIRCULO_H

typedef void* Circulo;

/**
 * 
 * 
 * Circulo contém as informações de um circulo, sendo elas: id, raio, coordenadas X e Y, cor de borda e cor de preenchimento.
 * id é um identificador unico para cada circulo, 
 * raio é o tamanho do raio do circulo, 
 * coordenadas X e Y são as coordenadas do centro do circulo,
 * cor de borda é a cor da borda do circulo,
 * cor de preenchimento é a cor do preenchimento do circulo.
 */

/*Cria e define a forma de um circulo no projeto, o circulo possui coordenadas X e Y, 
sendo sua referencia o centro dele, tambem possui cor de borda e preenchimento, alem de seu diamentro/área*/

Circulo criarCirculo(int id, double diametro, double x, double y, char* corb, char* corp);

/*As Funções set alteram os valores das respectivas variaveis que elas referem, isso é necessario devido
ao void* impossibilitar o acesso direto aos dados das structs*/

//define o id do circulo
void circuloSetId(Circulo set, int id);

//define o raio do circulo
void circuloSetDiametro(Circulo set, double diametro);


//define a coordenada X do circulo
void circuloSetX(Circulo set, double x);


//define a coordenada Y do circulo
void circuloSetY(Circulo set, double y);

//define a cor da borda do circulo
void circuloSetCorBorda(Circulo set, char* corb);

//define a cor de preenchimento do circulo
void circuloSetCorPreenchimento(Circulo set, char* corp);

/*As Funções get retornam os valores das respectivas variaveis que elas referem, isso é necessario devido
ao void* impossibilitar o acesso direto aos dados das structs*/

//retorna o id do circulo
int circuloGetId(Circulo get);


//retorna o raio do circulo
double circuloGetRaio(Circulo get);

//retorna a coordenada X do circulo
double circuloGetX(Circulo get);

//retorna a coordenada Y do circulo
double circuloGetY(Circulo get);

//retorna a cor da borda do circulo
char* circuloGetCorBorda(Circulo get);

//retorna a cor de preenchimento do circulo
char* circuloGetCorPreenchimento(Circulo get);

#endif //TRABALHOED_CIRCULO_H
