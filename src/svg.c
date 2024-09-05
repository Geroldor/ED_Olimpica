#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "svg.h"

struct _ArqSvg
{
    FILE *f;
    char *fn;
};

ArqSvg abreEscritaSvg(char *fn)
{
    struct _ArqSvg *arq = (ArqSvg)malloc(sizeof(struct _ArqSvg));
    if (arq == NULL)
    {
        return NULL;
    }

    arq->fn = fn;
    if (arq->fn == NULL)
    {
        free(arq);
        return NULL;
    }

    arq->f = fopen(fn, "w");
    if (arq->f == NULL)
    {
        return NULL;
    }

    fprintf(arq->f, "<?xml version=\"1.0\" standalone=\"no\"?>\n");
    fprintf(arq->f, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n");
    fprintf(arq->f, "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
    fprintf(arq->f, "<svg width=\"100%%\" height=\"100%%\"\n");
    fprintf(arq->f, "xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    return arq;
}

void escreveCirculoSvg(ArqSvg fsvg, double x, double y, double r, char* corb, char* corp)
{
    struct _ArqSvg *arq = (struct _ArqSvg *)fsvg;
    if (corb == NULL)
    {
        corb = "none";
    }
    if (corp == NULL)
    {
        corp = "none";
    }
    fprintf(arq->f, "<circle cx=\"%lf\" cy=\"%lf\" r=\"%lf\" stroke=\"%s\" fill=\"%s\"/>\n", x, y, r, corb, corp);
}

void escreveRetanguloSvg(ArqSvg fsvg, double x, double y, double larg, double alt, char* corb, char* corp)
{
    struct _ArqSvg *arq = (struct _ArqSvg *)fsvg;
    fprintf(arq->f, "<rect x=\"%lf\" y=\"%lf\" width=\"%lf\" height=\"%lf\" stroke=\"%s\" fill=\"%s\" />\n", x, y, larg, alt, corb, corp);
}

void escreveLinhaSvg(ArqSvg fsvg, double x1, double y1, double x2, double y2, char* cor)
{
    struct _ArqSvg *arq = (struct _ArqSvg *)fsvg;
    fprintf(arq->f, "<line x1=\"%lf\" y1=\"%lf\" x2=\"%lf\" y2=\"%lf\" fill=\"%s\" />\n", x1, y1, x2, y2, cor);
}

void escreveTextoSvg(ArqSvg fsvg, double x, double y, char* family, char* deco, char* tamanho, char* corb, char *corp, char* ancora, char *texto)
{
    struct _ArqSvg *arq = (struct _ArqSvg *)fsvg;
    fprintf(arq->f, "<text x=\"%lf\" y=\"%lf\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\" fill=\"%s\" text-anchor=\"%s\" stroke=\"%s\" stroke-width=\"1px\">%s</text>\n", x, y, family, deco, tamanho, corp, ancora, corb, texto);
}

void fechaSvg(ArqSvg fsvg)
{
    struct _ArqSvg *arq = (struct _ArqSvg *)fsvg;
    fprintf(arq->f, "</svg>\n");
    fclose(arq->f);
    //free(arq->fn);
    free(arq);
}