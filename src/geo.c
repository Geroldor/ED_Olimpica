#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "spacrbtree.h"
#include "geo.h"
#include "svg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lerGeo(char* geopath, SpacRbTree t) {
    printf("%s\n", geopath);
    FILE* geo = fopen(geopath, "r");
    if (geo == NULL)
    {
        printf("Erro ao abrir o arquivo .geo\n");
        exit(1);
    }
    
    char comando[10];
    char familia[20];
    char deco[10];
    char tamanho[5];
    ArqSvg arq = abreEscritaSvg("teste.svg");

    while (1) {
        if (feof(geo)) {
            break;
        }
        fscanf(geo, "%s", comando);
        if (strcmp(comando, "c") == 0) {
            int id;
            double raio;
            double x;
            double y;
            char corBorda[20];
            char corPreenchimento[20];
            fscanf(geo, "%d %lf %lf %lf %s %s", &id, &x, &y, &raio, corBorda, corPreenchimento);
            Circulo circulo = criarCirculo(id, raio, x, y, corBorda, corPreenchimento);
            insertSrbT(t, circuloGetX(circulo), circuloGetY(circulo), circulo, 2);
            escreveCirculoSvg(arq, circuloGetX(circulo), circuloGetY(circulo), circuloGetRaio(circulo), circuloGetCorBorda(circulo), circuloGetCorPreenchimento(circulo));
            //inserir na arvore marcando como tipo 2
        } else if (strcmp(comando, "r") == 0) {
            int id;
            double w;
            double h;
            double x;
            double y;
            char corBorda[20];
            char corPreenchimento[20];
            fscanf(geo, "%d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corBorda, corPreenchimento);
            Retangulo retangulo = criarRetangulo(id, w, h, x, y, corBorda, corPreenchimento);
            insertSrbT(t, retanguloGetX(retangulo), retanguloGetY(retangulo), retangulo, 1);
            escreveRetanguloSvg(arq, retanguloGetX(retangulo), retanguloGetY(retangulo), retanguloGetBase(retangulo), retanguloGetAltura(retangulo), retanguloGetCorBorda(retangulo), retanguloGetCorPreenchimento(retangulo));
            //inserir na arvore marcando como tipo 1
        } else if (strcmp(comando, "t") == 0) {
            int id;
            double x;
            double y;
            char texto[255];
            char corb[10];
            char corp[10];
            char ancora[10];
            fscanf(geo, "%d %lf %lf %9s %9s %9s %254s", &id, &x, &y, corb, corp, ancora, texto);
            Texto text = criarTexto(id, x, y, texto, tamanho, deco, familia, corb, corp, ancora);
            insertSrbT(t, textoGetX(text), textoGetY(text), text, 4);
            escreveTextoSvg(arq, textoGetX(text), textoGetY(text), "Arial", "normal", "12pt", textoGetCorb(text), textoGetCorp(text), textoGetAncora(text), textoGetTexto(text));
            //inserir na arvore marcando como tipo 4
        } else if(strcmp(comando, "ts") == 0){
            fscanf(geo, "%9s %9s %9s", familia, tamanho, deco);
            //printf("ts %s %s %s\n", familia, tamanho, deco);
        } else if(strcmp(comando, "l") == 0){
            int id;
            double x1;
            double y1;
            double x2;
            double y2;
            char cor[20];
            fscanf(geo, "%d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);
            Linha linha = criarLinha(id, x1, y1, x2, y2, cor);
            insertSrbT(t, linhaGetX1(linha), linhaGetY1(linha), linha, 3);
            escreveLinhaSvg(arq, linhaGetX1(linha), linhaGetY1(linha), linhaGetX2(linha), linhaGetY2(linha), linhaGetCor(linha));
            //inserir na arvore marcando como tipo 3
        }
    }
    fechaSvg(arq);
}
