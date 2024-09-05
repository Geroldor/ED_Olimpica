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


void sel(SpacRbTree t, HashTable ht, char* nome, double x, double y, double w, double h){
    /*Seleciona as formas inteiramente contidas dentro do retângulo (x,y,w,h) como armamento 
    e as identifica conjuntamente com o nome nome.
    TXT: reportar o identificador e o tipo da forma selecionada
    SVG: colocar uma pequena circunferência vermelha na âncora da forma selecionada.*/
    Lista l = createLista(-1);
    getNodesDentroRegiaoSrbT(t, x, y, h, w, l);
    addHt(ht, nome, l, 5);

}

void prep(HashTable ht, char* nome, double grs, double dist){
    /*Prepara a(s) arma(s) designada(s) por nome para fazer(em) um (futuro) disparo com inclinação de grs
    graus a uma distância dist. 
    SVG: colocar um pequeno + vermelho dentro do circunferência da seleção (veja sel)
*/
    Lista l = getHt(ht, nome, NULL);
    if(l == NULL){
        printf("Nao ha formas selecionadas\n");
        return;
    }
    Posic p = getFirst(l);
    while(p != NULL){
        int f = getTipo(p);
        if(getTipo(f) == 1){
            Circulo c = get(l, p);
            double x = circuloGetX(c);
            double y = circuloGetY(c);
            double x1 = x + dist * cos(grs);
            double y1 = y + dist * sin(grs);
            alterX(p, x1);
            alterY(p, y1);
        }else if(getTipo(f) == 2){
            Retangulo r = get(l, p);
            double x = retanguloGetX(r);
            double y = retanguloGetY(r);
            double x1 = x + dist * cos(grs);
            double y1 = y + dist * sin(grs);
            alterX(p, x1);
            alterY(p, y1);
        }else if(getTipo(f) == 3){
            Linha l = get(l, p);
            double x1 = linhaGetX1(l);
            double y1 = linhaGetY1(l);
            double x2 = linhaGetX2(l);
            double y2 = linhaGetY2(l);
            double x = x1 > x2 ? x1 : x2;
            double y = y1 > y2 ? y1 : y2;
            double rx = x + dist * cos(grs);
            double ry = y + dist * sin(grs);
            alterX(p, rx);
            alterY(p, ry);
        }else if(getTipo(f) == 4){
            Texto t = get(l, p);
            double x = textoGetX(t);
            double y = textoGetY(t);
            double x1 = x + dist * cos(grs);
            double y1 = y + dist * sin(grs);
            alterX(p, x1);
            alterY(p, y1);
        }
        p = getNext(l, p);
    }
}

void disp(SpacRbTree t, HashTable ht, char* nome){
    /*Dispara a(s) arma(s) designada(s) por nome, previamente preparadas. Remove e contabiliza os 
    alvos atingidos. A potência do disparo de cada arma depende da forma da arma.
    Se a seleção foi feita por comando sel, depois do disparo a seleção é desfeita. 
    Se o disparo atingir um texto que seleciona uma  arma, a seleção deve ser desfeita.
    TXT: reportar identificador e tipo das formas atingidas. Reportar (se for o caso) reportar o 
    identificador dos textos “desarmados”*/
    Lista l = getHt(ht, nome, 5);
    Lista l2 = createLista(-1);
    if(l == NULL){
        printf("\nNao ha formas selecionadas\n");
        return;
    }
    Posic p = getFirst(l);
    Node n = (Node)get(l, p);
    double x, y;
    while(n != NULL){
        x = getX(p);
        y = getY(p);
        int f = getTipo(n);
        if(f == 1){
            Circulo c = get(l, p);
            getNodesDentroRegiaoSrbT(t, circuloGetX(c), circuloGetY(c), x, y, l2);
            if (l2 == NULL) {
            }else{
                Posic p2 = getFirst(l2);
                Node n2 = (Node)get(l2, p2);
                while(n2 != NULL){
                    int f2 = getTipo(n2);
                    if(f2 == 1){
                        Circulo c = get(l, p);
                        removeSrbT(t, circuloGetX(get(l2, p2)), circuloGetY(get(l2, p2)), 0);
                    }else if(f2 == 2){
                        Retangulo r = get(l, p);
                        removeSrbT(t, circuloGetX(get(l2, p2)), circuloGetY(get(l2, p2)), 0);
                    }else if(f2 == 3){
                        Linha l = get(l, p);
                        removeSrbT(t, circuloGetX(get(l2, p2)), circuloGetY(get(l2, p2)), 0);
                    }else if(f2 == 4){
                        Texto t = get(l, p);
                        removeSrbT(t, textoGetX(get(l2, p2)), textoGetY(get(l2, p2)), 0);
                    }
                    p2 = getNext(l2, p2);
                }
            }
            
        }else if(f == 2){
            Retangulo r = get(l, p);
            getNodesDentroRegiaoSrbT(t, retanguloGetX(r), retanguloGetY(r), x, y, l2);
            if (l2 == NULL) {
            }else{
                Posic p2 = getFirst(l2);
                Node n2 = (Node)get(l2, p2);
                while(n2 != NULL){
                    int f2 = getTipo(n2);
                    if(f2 == 1){
                        Circulo c = get(l, p);
                        removeSrbT(t, retanguloGetX(get(l2, p2)), retanguloGetY(get(l2, p2)), 0);
                    }else if(f2 == 2){
                        Retangulo r = get(l, p);
                        removeSrbT(t, retanguloGetX(get(l2, p2)), retanguloGetY(get(l2, p2)), 0);
                    }else if(f2 == 3){
                        Linha l = get(l, p);
                        removeSrbT(t, retanguloGetX(get(l2, p2)), retanguloGetY(get(l2, p2)), 0);
                    }else if(f2 == 4){
                        Texto t = get(l, p);
                        removeSrbT(t, textoGetX(get(l2, p2)), textoGetY(get(l2, p2)), 0);
                    }
                    p2 = getNext(l2, p2);
                }
            }
            
        }else if(f == 3){
            Linha l = get(l, p);
            if (l2 == NULL) {
            }else{
                Posic p2 = getFirst(l2);
                Node n2 = (Node)get(l2, p2);
                while(n2 != NULL){
                    int f2 = getTipo(n2);
                    if(f2 == 1){
                        Circulo c = get(l, p);
                        removeSrbT(t, linhaGetX1(get(l2, p2)), linhaGetY1(get(l2, p2)), 0);
                    }else if(f2 == 2){
                        Retangulo r = get(l, p);
                        removeSrbT(t, linhaGetX1(get(l2, p2)), linhaGetY1(get(l2, p2)), 0);
                    }else if(f2 == 3){
                        Linha l = get(l, p);
                        removeSrbT(t, linhaGetX1(get(l2, p2)), linhaGetY1(get(l2, p2)), 0);
                    }else if(f2 == 4){
                        Texto t = get(l, p);
                        removeSrbT(t, textoGetX(get(l2, p2)), textoGetY(get(l2, p2)), 0);
                    }
                    p2 = getNext(l2, p2);
                }
            }
        }else if(f == 4){
            Texto t = get(l, p);
            if (l2 == NULL) {
            }else{
                Posic p2 = getFirst(l2);
                Node n2 = (Node)get(l2, p2);
                while(n2 != NULL){
                    int f2 = getTipo(n2);
                    if(f2 == 1){
                        Circulo c = get(l, p);
                        removeSrbT(t, textoGetX(get(l2, p2)), textoGetY(get(l2, p2)), 0);
                    }else if(f2 == 2){
                        Retangulo r = get(l, p);
                        removeSrbT(t, textoGetX(get(l2, p2)), textoGetY(get(l2, p2)), 0);
                    }else if(f2 == 3){
                        Linha l = get(l, p);
                        removeSrbT(t, textoGetX(get(l2, p2)), textoGetY(get(l2, p2)), 0);
                    }else if(f2 == 4){
                        Texto t = get(l, p);
                        removeSrbT(t, textoGetX(get(l2, p2)), textoGetY(get(l2, p2)), 0);
                    }
                    p2 = getNext(l2, p2);
                }
            }
        }
        p = getNext(l, p);
    }
}

void clone(char* nome, int id, double dx, double dy, SpacRbTree t, HashTable ht){
    /*Semelhante a disp, porém, alvos “atingidos” não são destruídos, mas são “clonados”. Ou seja, novas 
    forma de mesmo tipo e mesmas dimensões são criadas, porém, posicionadas a um deslocamento 
    dx,dy da forma original. Os identificadores das novas formas são sequenciais, a partir de id.
    TXT: reportar os identificadores das formas (originais) clonadas.*/
    Lista l = getHt(ht, nome, NULL);
    Lista l2 = createLista(-1);
    if(l == NULL){
        return;
    }
    Posic p = getFirst(l);
    Node n = (Node)get(l, p);
    double x, y;
    while(n != NULL){
        x = getX(p);
        y = getY(p);
        int f = getTipo(n);
        if(f == 1){
            Circulo c = get(l, p);
            getNodesDentroRegiaoSrbT(t, circuloGetX(c), circuloGetY(c), x, y, l2);
            if (l2 == NULL) {
            }else{
                Posic p2 = getFirst(l2);
                Node n2 = (Node)get(l2, p2);
                while(n2 != NULL){
                    int f2 = getTipo(n2);
                    if(f2 == 1){
                        Circulo c = get(l, p);
                        c = criarCirculo(circuloGetId(c), circuloGetX(c) + dx, circuloGetY(c) + dy, circuloGetRaio(c), circuloGetCorBorda(c), circuloGetCorPreenchimento(c));
                        insertSrbT(t, circuloGetX(c), circuloGetY(c), c, f2);
                    }else if(f2 == 2){
                        Retangulo r = get(l, p);
                        Circulo c = criarCirculo(circuloGetId(get(l2, p2)), circuloGetRaio(get(l2, p2)), circuloGetX(get(l2, p2)) + dx, circuloGetY(get(l2, p2)) + dy, circuloGetCorBorda(get(l2, p2)), circuloGetCorPreenchimento(get(l2, p2)));
                    }else if(f2 == 3){
                        Linha l = get(l, p);
                        Circulo c = criarCirculo(circuloGetId(get(l2, p2)), circuloGetX(get(l2, p2)) + dx, circuloGetY(get(l2, p2)) + dy, circuloGetRaio(get(l2, p2)), circuloGetCorBorda(get(l2, p2)), circuloGetCorPreenchimento(get(l2, p2)));
                        insertSrbT(t, circuloGetX(c), circuloGetY(c), c, f2);
                    }else if(f2 == 4){
                        Texto tx = get(l, p);
                        tx = criarTexto(textoGetId(tx), textoGetX(tx) + dx, textoGetY(tx) + dy, textoGetTexto(tx), textoGetTamanho(tx), textoGetDeco(tx), textoGetFamilia(tx), textoGetCorb(tx), textoGetCorp(tx), textoGetAncora(tx));
                        insertSrbT(t, textoGetX(tx), textoGetY(tx), tx, f2);
                    }
                    p2 = getNext(l2, p2);
                }
            }
            
        }else if(f == 2){
            Retangulo r = get(l, p);
            getNodesDentroRegiaoSrbT(t, retanguloGetX(r), retanguloGetY(r), x, y, l2);
            if (l2 == NULL) {
            }else{
                Posic p2 = getFirst(l2);
                Node n2 = (Node)get(l2, p2);
                while(n2 != NULL){
                    int f2 = getTipo(n2);
                    if(f2 == 1){
                        Circulo c = get(l, p);
                        Retangulo r = criarRetangulo(retanguloGetId(get(l2, p2)), retanguloGetX(get(l2, p2)) + dx, retanguloGetY(get(l2, p2)) + dy, retanguloGetBase(get(l2, p2)), retanguloGetAltura(get(l2, p2)), retanguloGetCorBorda(get(l2, p2)), retanguloGetCorPreenchimento(get(l2, p2)));
                        insertSrbT(t, retanguloGetX(r), retanguloGetY(r), r, f2);
                    }else if(f2 == 2){
                        Retangulo r = get(l, p);
                        r = criarRetangulo(retanguloGetId(r), retanguloGetX(r) + dx, retanguloGetY(r) + dy, retanguloGetBase(r), retanguloGetAltura(r), retanguloGetCorBorda(r), retanguloGetCorPreenchimento(r));
                        insertSrbT(t, retanguloGetX(r), retanguloGetY(r), r, f2);
                    }else if(f2 == 3){
                        Linha l = get(l, p);
                        Retangulo r = criarRetangulo(retanguloGetId(get(l2, p2)), retanguloGetX(get(l2, p2)) + dx, retanguloGetY(get(l2, p2)) + dy, retanguloGetBase(get(l2, p2)), retanguloGetAltura(get(l2, p2)), retanguloGetCorBorda(get(l2, p2)), retanguloGetCorPreenchimento(get(l2, p2)));
                        insertSrbT(t, retanguloGetX(r), retanguloGetY(r), r, f2);
                    }else if(f2 == 4){
                        Texto tx = get(l, p);
                        Retangulo r = criarRetangulo(retanguloGetId(get(l2, p2)), retanguloGetX(get(l2, p2)) + dx, retanguloGetY(get(l2, p2)) + dy, retanguloGetBase(get(l2, p2)), retanguloGetAltura(get(l2, p2)), retanguloGetCorBorda(get(l2, p2)), retanguloGetCorPreenchimento(get(l2, p2)));
                        insertSrbT(t, retanguloGetX(r), retanguloGetY(r), r, f2);
                    }
                    p2 = getNext(l2, p2);
                }
            }
            
        }else if(f == 3){
            Linha l = get(l, p);
            if (l2 == NULL) {
            }else{
                Posic p2 = getFirst(l2);
                Node n2 = (Node)get(l2, p2);
                while(n2 != NULL){
                    int f2 = getTipo(n2);
                    if(f2 == 1){
                        Circulo c = get(l, p);
                        Linha l = criarLinha(linhaGetId(get(l2, p2)), linhaGetX1(get(l2, p2)) + dx, linhaGetY1(get(l2, p2)) + dy, linhaGetX2(get(l2, p2)) + dx, linhaGetY2(get(l2, p2)) + dy, linhaGetCor(get(l2, p2)));
                        insertSrbT(t, linhaGetX1(l), linhaGetY1(l), l, f2);
                    }else if(f2 == 2){
                        Retangulo r = get(l, p);
                        Linha l = criarLinha(linhaGetId(get(l2, p2)), linhaGetX1(get(l2, p2)) + dx, linhaGetY1(get(l2, p2)) + dy, linhaGetX2(get(l2, p2)) + dx, linhaGetY2(get(l2, p2)) + dy, linhaGetCor(get(l2, p2)));
                        insertSrbT(t, linhaGetX1(l), linhaGetY1(l), l, f2);
                    }else if(f2 == 3){
                        Linha l = get(l, p);
                        l = criarLinha(linhaGetId(l), linhaGetX1(l) + dx, linhaGetY1(l) + dy, linhaGetX2(l) + dx, linhaGetY2(l) + dy, linhaGetCor(l));
                        insertSrbT(t, linhaGetX1(l), linhaGetY1(l), l, f2);
                    }else if(f2 == 4){
                        Texto tx = get(l, p);
                        Linha l = criarLinha(linhaGetId(get(l2, p2)), linhaGetX1(get(l2, p2)) + dx, linhaGetY1(get(l2, p2)) + dy, linhaGetX2(get(l2, p2)) + dx, linhaGetY2(get(l2, p2)) + dy, linhaGetCor(get(l2, p2)));
                        insertSrbT(t, linhaGetX1(l), linhaGetY1(l), l, f2);

                    }
                    p2 = getNext(l2, p2);
                }
            }
        }else if(f == 4){
            Texto t = get(l, p);
            if (l2 == NULL) {
            }else{
                Posic p2 = getFirst(l2);
                Node n2 = (Node)get(l2, p2);
                while(n2 != NULL){
                    int f2 = getTipo(n2);
                    if(f2 == 1){
                        Circulo c = get(l, p);
                        Texto tx = criarTexto(textoGetId(get(l2, p2)), textoGetX(get(l2, p2)) + dx, textoGetY(get(l2, p2)) + dy, textoGetTexto(get(l2, p2)), textoGetTamanho(get(l2, p2)), textoGetDeco(get(l2, p2)), textoGetFamilia(get(l2, p2)), textoGetCorb(get(l2, p2)), textoGetCorp(get(l2, p2)), textoGetAncora(get(l2, p2)));
                        insertSrbT(t, textoGetX(tx), textoGetY(tx), tx, f2);
                    }else if(f2 == 2){
                        Retangulo r = get(l, p);
                        Texto tx = criarTexto(textoGetId(get(l2, p2)), textoGetX(get(l2, p2)) + dx, textoGetY(get(l2, p2)) + dy, textoGetTexto(get(l2, p2)), textoGetTamanho(get(l2, p2)), textoGetDeco(get(l2, p2)), textoGetFamilia(get(l2, p2)), textoGetCorb(get(l2, p2)), textoGetCorp(get(l2, p2)), textoGetAncora(get(l2, p2)));
                        insertSrbT(t, textoGetX(tx), textoGetY(tx), tx, f2);
                    }else if(f2 == 3){
                        Linha l = get(l, p);
                        Texto tx = criarTexto(textoGetId(get(l2, p2)), textoGetX(get(l2, p2)) + dx, textoGetY(get(l2, p2)) + dy, textoGetTexto(get(l2, p2)), textoGetTamanho(get(l2, p2)), textoGetDeco(get(l2, p2)), textoGetFamilia(get(l2, p2)), textoGetCorb(get(l2, p2)), textoGetCorp(get(l2, p2)), textoGetAncora(get(l2, p2)));
                        insertSrbT(t, textoGetX(tx), textoGetY(tx), tx, f2);
                    }else if(f2 == 4){
                        Texto txt = get(l, p);
                        Texto tx = criarTexto(textoGetId(get(l2, p2)), textoGetX(get(l2, p2)) + dx, textoGetY(get(l2, p2)) + dy, textoGetTexto(get(l2, p2)), textoGetTamanho(get(l2, p2)), textoGetDeco(get(l2, p2)), textoGetFamilia(get(l2, p2)), textoGetCorb(get(l2, p2)), textoGetCorp(get(l2, p2)), textoGetAncora(get(l2, p2)));
                        insertSrbT(t, textoGetX(tx), textoGetY(tx), tx, f2);
                    }
                    p2 = getNext(l2, p2);
                }
            }
        }
        p = getNext(l, p);
    }
}

void del(HashTable ht, char* nome){
    /*Remove a(s) forma(s) designada(s) por nome. Se a seleção foi feita por comando sel, a seleção é desfeita.
    TXT: reportar os identificadores e tipos das formas removidas.*/
    Lista l = (Lista)getHt(ht, nome, NULL);
    killLista(l);
}

void qry(char* comando, SpacRbTree t, HashTable ht){
    FILE *comand = fopen(comando, "r");
    if (comand == NULL)
    {
        printf("Erro ao abrir o arquivo .qry\n");
        exit(1);
    }
    char op[6];
    while(1){
        fscanf(comand, "%s", op);
        if(strcmp(op, "sel") == 0){
            char nome[100];
            double x, y, w, h;
            fscanf(comand, "%s %lf %lf %lf %lf", nome, &x, &y, &w, &h);
            sel(t, ht, nome, x, y, w, h);
        }else if(strcmp(op, "prep") == 0){
            char nome[100];
            double grs, dist;
            fscanf(comand, "%s %lf %lf", nome, &grs, &dist);
            prep(ht, nome, grs, dist);
        }else if(strcmp(op, "disp") == 0){
            char nome[100];
            fscanf(comand, "%s", nome);
            disp(t, ht, nome);
        }else if(strcmp(op, "clone") == 0){
            char nome[100];
            int id;
            double dx, dy;
            fscanf(comand, "%s %d %lf %lf", nome, &id, &dx, &dy);
            clone(nome, id, dx, dy, t, ht);
        }else if(strcmp(op, "del") == 0){
            char nome[100];
            fscanf(comand, "%s", nome);
            del(ht, nome);
        }
        if (feof(comando)) {
            break;
        }
        
    }
    fclose(comand);
}