#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "circulo.h"
#include "retangulo.h"
#include "linha.h"
#include "texto.h"
#include "geo.h"
#include "spacrbtree.h"
#include "hashtable.h"
#include "lista.h"
#include "svg.h"

int main(int argc, char* argv[]) {


    char geoPath[100];
    char qryPath[100];
    char svgPath[100];
    char fstatsPath[100];
    char outputFile[100];
    char outputPath[100];
    char geoFilename[100];
    char qryFilename[100];
    char path[100];
    char ext[5];
    int i = 0;

    memset(geoPath, 0, 100);
    memset(qryPath, 0, 100);
    memset(svgPath, 0, 100);
    memset(fstatsPath, 0, 100);
    memset(outputFile, 0, 100);
	memset(outputPath, 0, 100);
    memset(geoFilename, 0, 100);
    memset(qryFilename, 0, 100);
    memset(path, 0, 100);
    memset(ext, 0, 5);
    

    while (i < argc)
    {
        if (strcmp(argv[i], "-e") == 0)
        {
            strcpy(path, argv[i+1]);
        }
        else if (strcmp(argv[i], "-q") == 0)
        {
            strcpy(qryFilename, argv[i+1]);
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            strcpy(outputPath, argv[i+1]);
        }
        else if(strcmp(argv[i], "-f") == 0)
        {
            strcpy(geoFilename, argv[i+1]);
        }
        i++;
    }

    strcat(path, "/");
    strcat(outputPath, "/");
    strtok(geoFilename, ".");
    strtok(qryFilename, ".");
    strcat(outputFile, outputPath);


    strcat(outputFile, geoFilename);
    strcat(outputFile, "-");
    char* k = strchr(qryFilename, '/');
    k++;
    strcat(outputFile, k);    
    
    strcat(geoFilename, ".geo");
    strcat(qryFilename, ".qry");
    strcat(geoPath, path);
    strcat(qryPath, path);
    strcat(geoPath, geoFilename);
    strcat(qryPath, qryFilename);
    
    char* fstat = outputFile;
    
    strcat(fstat, ".csv");
    SpacRbTree t = newSpacRbTree(fstat);
    HashTable ht = newHashTable(fstat);

    lerGeo(geoPath, t);
    qry(qryPath, t, ht);

    char* svgFile = outputFile;
    strtok(svgFile, ".");
    strcat(svgFile, ".svg");

    ArqSvg arq = abreEscritaSvg(svgFile);
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo .svg\n");
        exit(1);
    }
    
    Lista svg = createLista(-1);
    getNodesDentroRegiaoSrbT(t, 0, 0, 999999, 999999, svg);
    Posic p = getFirst(svg);
    while (1 && p != NIL)
    {
        switch (getTipo(p))
        {
        case 1:
            Retangulo r = get(svg, p);
            escreveRetanguloSvg(arq, retanguloGetX(r), retanguloGetY(r), retanguloGetBase(r), retanguloGetAltura(r), retanguloGetCorBorda(r), retanguloGetCorPreenchimento(r));
            break;
        
        case 2:
            Circulo c = get(svg, p);
            escreveCirculoSvg(arq, circuloGetX(c), circuloGetY(c), circuloGetRaio(c), circuloGetCorBorda(c), circuloGetCorPreenchimento(c));
            break;

        case 3:
            Linha l = get(svg, p);
            escreveLinhaSvg(arq, linhaGetX1(l), linhaGetY1(l), linhaGetX2(l), linhaGetY2(l), linhaGetCor(l));
            break;

        case 4:
            Texto t = get(svg, p);
            escreveTextoSvg(arq, textoGetX(t), textoGetY(t), textoGetFamilia(t), textoGetDeco(t), textoGetTamanho(t), textoGetCorb(t), textoGetCorp(t), textoGetAncora(t), textoGetTexto(t));
            break;
        }
        p = getNext(svg, p);
        if (p == NIL)
        {
            break;
        }
    }
    strtok(svgFile, ".");
    strcat(svgFile, " .dot");
    printDotSRbTree(t, svgFile);
    fechaSvg(arq);
        return 0;
}
