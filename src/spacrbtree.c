#include "spacrbtree.h"
#include "retangulo.h"
#include "circulo.h"
#include "texto.h"
#include "linha.h"
#include "lista.h"
#include "svg.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define BLACK "black"
#define RED "red"

typedef struct node
{
    Info item;
    DescritorTipoInfo tipo;
    double x;
    double y;
    struct node *esq;
    struct node *dir;
    struct node *pai;
    char *cor;
} node;

typedef struct spacrbtree
{
    node *raiz;
    FILE *fstat;
    int lrot;
    int rrot;
} arvore;


SpacRbTree newSpacRbTree(char *fstat)
{
    arvore *nova = malloc(sizeof(struct spacrbtree));
    nova->raiz = NULL;
    if (fstat != NULL)
    {
        nova->fstat = fopen(fstat, "w");
        if (nova->fstat == NULL)
        {
            return NULL;
        }else
        {
            fprintf(nova->fstat, "forma, x, y, acao\n");
        }
        
    }
    else
    {
        nova->fstat = NULL;
    }
    return nova;
}

node* newNode(Info i, DescritorTipoInfo d, double x, double y) {
    node *n = (node*)malloc(sizeof(node));
    n->item = i;
    n->tipo = d;
    n->x = x;
    n->y = y;
    n->esq = NULL;
    n->dir = NULL;
    n->pai = NULL;
    n->cor = RED;  // Novo nó é sempre vermelho
    return n;
}

// Rotação à esquerda
void rightRotation(SpacRbTree t, node *x) {
    arvore *tree = (arvore *)t;
    node *y = x->dir;
    x->dir = y->esq;
    if (y->esq != NULL) {
        y->esq->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == NULL) {
        tree->raiz = y;
    } else if (x == x->pai->esq) {
        x->pai->esq = y;
    } else {
        x->pai->dir = y;
    }
    y->esq = x;
    x->pai = y;
    tree->rrot++;
}

// Rotação à direita
void leftRotation(SpacRbTree t, node *y) {
    arvore *tree = (arvore *)t;
    node *x = y->esq;
    y->esq = x->dir;
    if (x->dir != NULL) {
        x->dir->pai = y;
    }
    x->pai = y->pai;
    if (y->pai == NULL) {
        tree->raiz = x;
    } else if (y == y->pai->esq) {
        y->pai->esq = x;
    } else {
        y->pai->dir = x;
    }
    x->dir = y;
    y->pai = x;
    tree->lrot++;
}

// Função auxiliar para corrigir a árvore após a inserção
void fixInsert(SpacRbTree t, node *z) {
    arvore *tree = (arvore *)t;
    while (z->pai != NULL && strcmp(z->pai->cor, RED) == 0) {
        if (z->pai == z->pai->pai->esq) {
            node *y = z->pai->pai->dir;
            if (y != NULL && strcmp(y->cor, RED) == 0) {
                z->pai->cor = BLACK;
                y->cor = BLACK;
                z->pai->pai->cor = BLACK;
                z = z->pai->pai;
            } else {
                if (z == z->pai->dir) {
                    z = z->pai;
                    rightRotation(t, z);
                }
                z->pai->cor = BLACK;
                z->pai->pai->cor = RED;
                leftRotation(t, z->pai->pai);
            }
        } else {
            node *y = z->pai->pai->esq;
            if (y != NULL && strcmp(y->cor, RED) == 0) {
                z->pai->cor = BLACK;
                y->cor = BLACK;
                z->pai->pai->cor = RED;
                z = z->pai->pai;
            } else {
                if (z == z->pai->esq) {
                    z = z->pai;
                    leftRotation(t, z);
                }
                z->pai->cor = BLACK;
                z->pai->pai->cor = RED;
                rightRotation(t, z->pai->pai);
            }
        }
    }
    tree->raiz->cor = BLACK;
}

// Função de inserção na árvore rubro-negra
Node insertSrbT(SpacRbTree t, double x, double y, Info i, DescritorTipoInfo d) {
    arvore *tree = (arvore *)t;
    node *z = newNode(i, d, x, y);
    node *yNode = NULL;
    node *xNode = tree->raiz;
    if (tree->raiz == NULL)
    {
        tree->raiz = z;
        z->cor = BLACK;
        return z;
    }
    
    while (xNode != NULL) {
        yNode = xNode;
        if (z->x < xNode->x || (z->x == xNode->x && z->y < xNode->y)) {
            xNode = xNode->esq;
        } else {
            xNode = xNode->dir;
        }
    }

    z->pai = yNode;

    if (yNode == NULL) {
        tree->raiz = z;
    } else if (z->x < yNode->x || (z->x == yNode->x && z->y < yNode->y)) {
        yNode->esq = z;
    } else {
        yNode->dir = z;
    }

    fixInsert(t, z);
    char* buff;
    switch (z->tipo)
    {
    case 1:
        sprintf(buff, "r, %lf, %lf", z->x, z->y);
        getRelatorioSrbT(t, buff, strlen("r, %lf, %lf, insercao"));
        break;

    case 2:
        sprintf(buff, "c, %lf, %lf", z->x, z->y);
        getRelatorioSrbT(t, buff, strlen("r, %lf, %lf, insercao"));
        break;

    case 3:
        sprintf(buff, "l, %lf, %lf", z->x, z->y);
        getRelatorioSrbT(t, buff, strlen("r, %lf, %lf, insercao"));
        break;

    case 4:
        sprintf(buff, "t, %lf, %lf", z->x, z->y);
        getRelatorioSrbT(t, buff, strlen("r, %lf, %lf, insercao"));
        break;

    default:
        break;
    }
    return z;
}

Node getNodeSrbT(SpacRbTree t, double x, double y, double epsilon) {
    arvore *tree = (arvore*)t;  // Converte o ponteiro void* para SpacRbTree*
    node *atual = tree->raiz;

    while (atual != NULL) {
        double dx = fabs(atual->x - x);
        double dy = fabs(atual->y - y);

        if (dx < epsilon && dy < epsilon) {
            return atual;
        }

        if (x < atual->x || (x == atual->x && y < atual->y)) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    return NULL;
}

bool removeSrbT(SpacRbTree t, double x, double y, double epsilon)
{
    arvore *tree = (arvore *)t;
    node *atual = tree->raiz;
    node *anterior = NULL;
    while (atual != NULL)
    {
        if (abs(atual->x - x) < epsilon && abs(atual->y - y) < epsilon)
        {
            if (atual->esq == NULL && atual->dir == NULL)
            {
                if (anterior->esq == atual)
                {
                    anterior->esq = NULL;
                }
                else
                {
                    anterior->dir = NULL;
                }
                free(atual);
                return true;
            }
            else if (atual->esq == NULL)
            {
                if (anterior->esq == atual)
                {
                    anterior->esq = atual->dir;
                }
                else
                {
                    anterior->dir = atual->dir;
                }
                free(atual);
                return true;
            }
            else if (atual->dir == NULL)
            {
                if (anterior->esq == atual)
                {
                    anterior->esq = atual->esq;
                }
                else
                {
                    anterior->dir = atual->esq;
                }
                free(atual);
                return true;
            }
            else
            {
                node *aux = atual->dir;
                while (aux->esq != NULL)
                {
                    aux = aux->esq;
                }
                atual->item = aux->item;
                atual->tipo = aux->tipo;
                atual->x = aux->x;
                atual->y = aux->y;
                if (aux->esq == NULL && aux->dir == NULL)
                {
                    if (anterior->esq == aux)
                    {
                        anterior->esq = NULL;
                    }
                    else
                    {
                        anterior->dir = NULL;
                    }
                    char* buff;
    switch (aux->tipo)
    {
    case 1:
        sprintf(buff, "r, %lf, %lf", aux->x, aux->y);
        getRelatorioSrbT(t, buff, strlen("r, %lf, %lf, remocao"));
        break;

    case 2:
        sprintf(buff, "c, %lf, %lf", aux->x, aux->y);
        getRelatorioSrbT(t, buff, strlen("r, %lf, %lf, remocao"));
        break;

    case 3:
        sprintf(buff, "l, %lf, %lf", aux->x, aux->y);
        getRelatorioSrbT(t, buff, strlen("r, %lf, %lf, remocao"));
        break;

    case 4:
        sprintf(buff, "t, %lf, %lf", aux->x, aux->y);
        getRelatorioSrbT(t, buff, strlen("r, %lf, %lf, remocao"));
        break;

    default:
        break;
    }
                    free(aux);
                    return true;
                }
                else if (aux->esq == NULL)
                {
                    if (anterior->esq == aux)
                    {
                        anterior->esq = aux->dir;
                    }
                    else
                    {
                        anterior->dir = aux->dir;
                    }
                    free(aux);
                    return true;
                }
                else if (aux->dir == NULL)
                {
                    if (anterior->esq == aux)
                    {
                        anterior->esq = aux->esq;
                    }
                    else
                    {
                        anterior->dir = aux->esq;
                    }
                    free(aux);
                    return true;
                }
            }
        }
        anterior = atual;
        if (x < atual->x)
        {
            atual = atual->esq;
        }
        else if (x == atual->x && y < atual->y)
        {
            atual = atual->esq;
        }
        else if (x == atual->x && y > atual->y)
        {
            atual = atual->dir;
        }
        else
        {
            atual = atual->dir;
        }
    }
}

void removeNodeSrbT(SpacRbTree t, Node n)
{
    arvore *tree = (arvore *)t;
    node *atual = tree->raiz;
    node *anterior = NULL;
    node *nier = (node *)n;
    while (atual != NULL)
    {
        if (atual == nier)
        {
            if (atual->esq == NULL && atual->dir == NULL)
            {
                if (anterior->esq == atual)
                {
                    anterior->esq = NULL;
                }
                else
                {
                    anterior->dir = NULL;
                }
                free(atual);
                return;
            }
            else if (atual->esq == NULL)
            {
                if (anterior->esq == atual)
                {
                    anterior->esq = atual->dir;
                }
                else
                {
                    anterior->dir = atual->dir;
                }
                free(atual);
                return;
            }
            else if (atual->dir == NULL)
            {
                if (anterior->esq == atual)
                {
                    anterior->esq = atual->esq;
                }
                else
                {
                    anterior->dir = atual->esq;
                }
                free(atual);
                return;
            }
            else
            {
                node *aux = atual->dir;
                while (aux->esq != NULL)
                {
                    aux = aux->esq;
                }
                atual->item = aux->item;
                atual->tipo = aux->tipo;
                atual->x = aux->x;
                atual->y = aux->y;
                if (aux->esq == NULL && aux->dir == NULL)
                {
                    if (anterior->esq == aux)
                    {
                        anterior->esq = NULL;
                    }
                    else
                    {
                        anterior->dir = NULL;
                    }
                    free(aux);
                    return;
                }
                else if (aux->esq == NULL)
                {
                    if (anterior->esq == aux)
                    {
                        anterior->esq = aux->dir;
                    }
                    else
                    {
                        anterior->dir = aux->dir;
                    }
                    free(aux);
                    return;
                }
                else if (aux->dir == NULL)
                {
                    if (anterior->esq == aux)
                    {
                        anterior->esq = aux->esq;
                    }
                    else
                    {
                        anterior->dir = aux->esq;
                    }
                    free(aux);
                    return;
                }
            }
        }
        anterior = atual;
        if (nier->x < atual->x)
        {
            atual = atual->esq;
        }
        else if (nier->x == atual->x && nier->y < atual->y)
        {
            atual = atual->esq;
        }
        else if (nier->x == atual->x && nier->y > atual->y)
        {
            atual = atual->dir;
        }
        else
        {
            atual = atual->dir;
        }
    }
}

Info getInfoSrbT(SpacRbTree t, Node n)
{
    node *no = (node *)n;
    return no->item;
}

DescritorTipoInfo getTypeInfoSrbT(SpacRbTree t, Node n)
{
    node *no = (node *)n;
    return no->tipo;
}

void percorrerArvoreInserirLista(node *n, double x1, double y1, double x2, double y2, Lista L) {
    if (n == NULL) {
        return;
    }

    // Verifica se o nó atual está dentro da região e, se estiver, o insere na lista
    if (n->x >= x1 && n->x <= x2 && n->y >= y1 && n->y <= y2) {
        // Função fictícia que insere o nó na lista
        insert(L, n->item, n->tipo);
    }

    // Percorre a subárvore à esquerda e à direita
    percorrerArvoreInserirLista(n->esq, x1, y1, x2, y2, L);
    percorrerArvoreInserirLista(n->dir, x1, y1, x2, y2, L);
}

// Função principal solicitada
bool getNodesDentroRegiaoSrbT(SpacRbTree t, double x1, double y1, double x2, double y2, Lista L) {
    if (t == NULL || L == NULL) {
        return false; // Verifica se a árvore ou a lista são nulas
    }

    arvore *tree = (arvore*) t; // Cast para o tipo correto da árvore
    percorrerArvoreInserirLista(tree->raiz, x1, y1, x2, y2, L);
    return true;
}

bool getInfosDentroRegiaoSrbT(SpacRbTree t, double x1, double y1, double x2, double y2, FdentroDeRegiao f, Lista L)
{
    arvore *tree = (arvore *)t;
    node *no = tree->raiz;
    if (no->x >= x1 && no->x <= x2 && no->y >= y1 && no->y <= y2)
    {
        insert(L, no->item, no->tipo);

    }
    getInfosDentroRegiaoSrbT(no->esq, x1, y1, x2, y2, f, L);
    getInfosDentroRegiaoSrbT(no->dir, x1, y1, x2, y2, f, L);
    return true;
}

void visitaProfundidadeSrbT(SpacRbTree t, FvisitaNo f, void *aux)
{
    arvore *tree = (arvore *)t;
    node *atual = tree->raiz;
    while (atual != NULL)
    {
        f(atual->item, atual->tipo, atual->x, atual->y, aux);
        if (atual->esq != NULL)
        {
            visitaProfundidadeSrbT(atual->esq, f, aux);
        }
        if (atual->dir != NULL)
        {
            visitaProfundidadeSrbT(atual->dir, f, aux);
        }
    }
}

void visitaLarguraSrbT(SpacRbTree t, FvisitaNo f, void *aux)
{
    arvore *tree = (arvore *)t;
    node *atual = tree->raiz;
    Lista lista = createLista(-1);
    insert(lista, atual, atual->tipo);
    while (lista != NULL)
    {
        node *no = (node *)pop(lista);
        f(no->item, no->tipo, no->x, no->y, aux);
        if (no->esq != NULL)
        {
            insert(lista, no->esq, no->esq->tipo);
        }
        if (no->dir != NULL)
        {
            insert(lista, no->dir, no->dir->tipo);
        }
    }
}

Node procuraNoSrbT(SpacRbTree t, FsearchNo f, void *aux)
{
    arvore *tree = (arvore *)t;
    node *atual = tree->raiz;
    while (atual != NULL)
    {
        if (f(atual->item, atual->tipo, atual->x, atual->y, aux))
        {
            return atual;
        }
        if (atual->esq != NULL)
        {
            procuraNoSrbT(atual->esq, f, aux);
        }
        if (atual->dir != NULL)
        {
            procuraNoSrbT(atual->dir, f, aux);
        }
    }
    return NULL;
}

bool printDotSRbTree(SpacRbTree t, char *fn)
{
    arvore *tree = (arvore *)t;
    FILE *f = fopen(fn, "w");
    if (f == NULL)
    {
        return false;
    }
    fprintf(f, "digraph G {\n");
    node *atual = tree->raiz;
    Lista lista = createLista(-1);
    insert(lista, atual, atual->tipo);
    while (lista != NULL)
    {
        node *no = (node *)pop(lista);
        if (no == NULL)
        {
            break;
        }

        if (no->esq != NULL)
        {
            insert(lista, no->esq, no->esq->tipo);
            switch (no->tipo)
            {
            case 1:
                fprintf(f, "\"R (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->x, no->y, no->cor);
                fprintf(f, "\"R (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->esq->x, no->esq->y, no->esq->cor);
                fprintf(f, "\"R (%.0f, %.0f)\" -> \"R (%.0f, %.0f)\";\n", no->x, no->y, no->esq->x, no->esq->y);
                break;
            case 2:
                fprintf(f, "\"C (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->x, no->y, no->cor);
                fprintf(f, "\"C (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->esq->x, no->esq->y, no->esq->cor);
                fprintf(f, "\"C (%.0f, %.0f)\" -> \"C (%.0f, %.0f)\";\n", no->x, no->y, no->esq->x, no->esq->y);
                break;

            case 3:
                fprintf(f, "\"L (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->x, no->y, no->cor);
                fprintf(f, "\"L (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->esq->x, no->esq->y, no->esq->cor);
                fprintf(f, "\"L (%.0f, %.0f)\" -> \"L (%.0f, %.0f)\";\n", no->x, no->y, no->esq->x, no->esq->y);
                break;
            
            case 4:
                fprintf(f, "\"T (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->x, no->y, no->cor);
                fprintf(f, "\"T (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->esq->x, no->esq->y, no->esq->cor);
                fprintf(f, "\"T (%.0f, %.0f)\" -> \"T (%.0f, %.0f)\";\n", no->x, no->y, no->esq->x, no->esq->y);
                break;
            
            default:
                break;
            }
        }
        if (no->dir != NULL)
        {
            insert(lista, no->dir, no->dir->tipo);
            switch (no->tipo)
            {
            case 1:
                fprintf(f, "\"R (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->x, no->y, no->cor);
                fprintf(f, "\"R (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->dir->x, no->dir->y, no->dir->cor);
                fprintf(f, "\"R (%.0f, %.0f)\" -> \"R (%.0f, %.0f)\";\n", no->x, no->y, no->dir->x, no->dir->y);
                break;
            case 2:
                fprintf(f, "\"C (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->x, no->y, no->cor);
                fprintf(f, "\"C (%.0f, %.0f)\" [fillcolor=%s fontcolor=white] style=filled;\n", no->dir->x, no->dir->y, no->dir->cor);
                fprintf(f, "\"C (%.0f, %.0f)\" -> \"C (%.0f, %.0f)\";\n", no->x, no->y, no->dir->x, no->dir->y);
                break;

            case 3:
                fprintf(f, "\"L (%.0f, %.0f)\" [fillcolor=%s fontcolor=white  style=filled];\n", no->x, no->y, no->cor);
                fprintf(f, "\"L (%.0f, %.0f)\" [fillcolor=%s fontcolor=white style=filled];\n", no->dir->x, no->dir->y, no->dir->cor);
                fprintf(f, "\"L (%.0f, %.0f)\" -> \"L (%.0f, %.0f)\";\n", no->x, no->y, no->dir->x, no->dir->y);
                break;
            
            case 4:
                fprintf(f, "\"T (%.0f, %.0f)\" [color=%s fontcolor=white style=filled];\n", no->x, no->y, no->cor);
                fprintf(f, "\"T (%.0f, %.0f)\" [color=%s fontcolor=white style=filled];\n", no->dir->x, no->dir->y, no->dir->cor);
                fprintf(f, "\"T (%.0f, %.0f)\" -> \"T (%.0f, %.0f)\";\n", no->x, no->y, no->dir->x, no->dir->y);
                break;
            }
        }
    }
    fprintf(f, "}\n");
    fclose(f);
    return true;
}


void getRelatorioSrbT(SpacRbTree t, char *buff, int n)
{
    arvore* tree = (arvore*)t;
    fprintf(tree->fstat, "%s", buff);

}

void killSrbTree(SpacRbTree t)
{
    arvore *tree = (arvore *)t;
    node *atual = tree->raiz;
    Lista lista = createLista(-1);
    insert(lista, atual, atual->tipo);
    while (lista != NULL)
    {
        node *no = pop(lista);
        if (no->esq != NULL)
        {
            insert(lista, no->esq, no->esq->tipo);
        }
        if (no->dir != NULL)
        {
            insert(lista, no->dir, no->dir->tipo);
        }
        free(no);
    }
    fprintf(tree->fstat, "rotacoes esquerda, %d\n", tree->lrot);
    fprintf(tree->fstat, "rotacoes direita, %d\n", tree->rrot);
    fclose(tree->fstat);
    free(tree);
}
