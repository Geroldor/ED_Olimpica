//
// Created by Geraldo Neto on 22/06/2024.
//

#ifndef TRABALHOED_TEXTO_H
#define TRABALHOED_TEXTO_H

typedef void* Texto;

/*
    Texto é uma struct que contém informações de um texto, sendo elas: id, texto, tamanho, decoração, familia, 
    cor da borda, cor do preenchimento, coordenadas X e Y.
    id é um inteiro que identifica o texto.
    texto é uma string que contém o texto a ser mostrado.
    tamanho é uma string que contém o tamanho da fonte.
    decoração é uma string que contém a decoração da fonte.
    familia é uma string que contém a familia da fonte.
    corb é uma string que contém a cor da borda.
    corp é uma string que contém a cor do preenchimento.
    x é um double que contém a coordenada X do texto.
    y é um double que contém a coordenada Y do texto.
    ancora é uma string que contém a ancora do texto.	
*/

/*Cria e define a forma de um texto no projeto, o texto possui o texto a ser mostrado,
fonte, tamanho da fonte, decoração da fonte, alem da coordenada X e Y*/
Texto criarTexto(int id, double x, double y, char* info, char* tamanho, char* deco, char* familia, char* corb, char* corp, char* ancora);

/*As Funções set alteram os valores das respectivas variaveis que elas referem, isso é necessario devido
ao void* impossibilitar o acesso direto aos dados das structs*/

//define o id do texto
void textoSetId(Texto set, int id);

//define a coordenada X do texto
void textoSetX(Texto set, double x);


//define a coordenada Y do texto
void textoSety(Texto set, double y);

//define o texto a ser mostrado
void textoSetInfo(Texto set, char* info);

//define a familia da fonte
void textoSetFamilia(Texto set, char* familia);

//define a decoração da fonte
void textoSetDeco(Texto set, char* deco);

//define o tamanho da fonte
void textoSetTamanho(Texto set, char* tamanho);

//define a cor da borda
void textoSetCorb(Texto set, char* corb);

//define a cor do preenchimento
void textoSetCorp(Texto set, char* corp);

//define a ancora do texto
void textoSetAncora(Texto set, char* ancora);

/*As Funções get retornam os valores das respectivas variaveis que elas referem, isso é necessario devido
ao void* impossibilitar o acesso direto aos dados das structs*/

//retorna o id do texto
int textoGetId(Texto get);

//retorna a coordenada X do texto
double textoGetX(Texto get);

//retorna a coordenada Y do texto
double textoGetY(Texto get);

//retorna o texto a ser mostrado
char* textoGetInfo(Texto get);

//retorna a familia da fonte
char* textoGetDeco(Texto get);

//retorna a decoração da fonte
char* textoGetFamilia(Texto get);

//retorna o tamanho da fonte
char* textoGetTamanho(Texto get);

//retorna a cor da borda
char* textoGetCorb(Texto get);

//retorna a cor do preenchimento
char* textoGetCorp(Texto get);

//retorna a ancora do texto
char* textoGetAncora(Texto get);

//retorna o texto a ser mostrado
char* textoGetTexto(Texto get);

//destroi o texto
void killTexto(Texto get);

#endif //TRABALHOED_TEXTO_H
