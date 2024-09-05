#ifndef _SPACRB_TREE__
#define _SPACRB_TREE__

#include "lista.h"
#include <stdbool.h>

/*
 * Uma SpacRbTree e' uma arvore rubro-negra espacial, por isso, garante insercao, delicao 
 * e busca (pela chave) em tempo O(log n).
 *
 * A cada no' r da Arvore sao associados: um ponto de 2 dimensoes (r.x e r.y) denominado ancora
 * do no'; uma informacao relacionada tal ponto; e um "descritor" do tipo da informacao.
 * O significado dos valores de tal descritor é definido pela aplicacao.
 * A ancora determina a relacao de ordem entre os elementos armazenados na arvore. 
 * Sejam dois  nos da arvore: s e t. 
 *            s < t: se (s.x < t.x) OU (s.x = t.x E s.y < t.y)
 *
 * A arvore SpacRbTree implementa 2 percursos: em largura e em profundidade.
 * Tais percursos recebem como parametro uma funcao que processa a
 * informacao associada ao no' visitado.
 *
 * Tambem sao providas operacoes de selecao espacial:
 *   A PRIMEIRA seleciona os nos da arvore cujas ancoras
 * sao internas a uma regiao retangular.
 *   A SEGUNDA seleciona os nos da Arvore cujas informacoes associadas
 * podem ser consideradas internas a uma regiao retangular.
 * Esta operacao recebe por parametro uma funcao que decide se
 * tal informacao e' considerada (ou nao) interna.
 *
 */


typedef void *SpacRbTree;
typedef void *Node;
typedef void *Info;
typedef int DescritorTipoInfo;

typedef bool (*FdentroDeRegiao)(Info i, DescritorTipoInfo d,  double x1, double y1, double x2, double y2);
/*
 * Uma funcao deste tipo deve retornar verdadeiro se a informacao i esta'
 * "dentro" da regiao retangular delimitada pelos pontos opostos (x1,y1) e (x2,y2).
 * Retorna falso, caso contrario.
 */


typedef void (*FvisitaNo)(Info i, DescritorTipoInfo d, double x, double y, void *aux);
/*
 * Processa a informacao i (do tipo d)  associada a um no' da arvore, cuja ancora
 * e' o ponto (x,y). O parametro aux aponta para conjunto de dados
 * (provavelmente um registro) que sao compartilhados entre as
 * sucessivas invocacoes a esta funcao.
 */

typedef bool (*FsearchNo)(Info i, DescritorTipoInfo d, double x, double y, void *aux);
/*
 * Verifica se a informacao i (do tipo d) associada a um no' da arvore, cuja ancora
 * e' o ponto (x,y) e' a informacao procurada. Retorna verdadeiro, em caso
 * afirmativo; falso, caso contrário. O parametro aux aponta para conjunto de dados
 * (provavelmente um registro) que sao compartilhados entre as
 * sucessivas invocacoes a esta funcao, incluindo (provavelmente) uma chave de busca.
 */

SpacRbTree newSpacRbTree(char *fstat);
/*
 * Retorna uma arvore SpacRb tree vazia.
 * fstat e' o nome do arquivo onde sao gravadas as estatisticas
 * de uso arvore. Atribuir NULL, caso nao queira gerar e gravar
 * estatisticas.
 * Retorna NULL, caso nao consiga criar o arquivo fstat.
 */

Node insertSrbT(SpacRbTree t, double x, double y, Info i, DescritorTipoInfo d);
/*
 * Insere a informacao i (de tipo d), associada 'a ancora (x,y) na arvore t.
 * d e' um valor (definido pela aplicacao) que identifica, caso existam varias
 * categorias, um categoria específica da informacao i.
 * Retorna um indicador para o no' inserido.
 */

Node getNodeSrbT(SpacRbTree t, double x, double y, double epsilon);
/*
 * Retorna o no' cuja ancora seja o ponto (x,y). Aceita-se uma pequena discrepancia
 * entre a coordenada da ancora (anc.x,anc.y) e o ponto (x,y) de epsilon unidades.
 * Ou seja, |anc.x - x | < epsilon e |anc.y - y | < epsilon.
 * Retorna NULL caso nao tenha encontrado o no'.
 */

bool removeSrbT(SpacRbTree t, double x, double y, double epsilon);
/*
 * Remove o no' n da arvore t cuja ancora seja o ponto (x,y), admitida a 
 * discrepancia epsilon.
 * Retorna true, se tal no' foi encontrado (e removido); caso contrario, false.
 */

void removeNodeSrbT(SpacRbTree t, Node n);
/*
 * Remove o no' n da arvore t.
 */

Info getInfoSrbT(SpacRbTree t, Node n);
/* Retorna a informacao associada ao no' n */

DescritorTipoInfo getTypeInfoSrbT(SpacRbTree t, Node n);
/* Retorna o tipo da informacao associada ao no' n */

bool getNodesDentroRegiaoSrbT(SpacRbTree t, double x1, double y1, double x2, double y2, Lista L);
/* Insere na lista L os nos (Node) da arvore t cujas ancoras estao dentro da regiao delimitada pelos
   pontos (x1,y1) e (x2,y2).
   Retorna falso, caso nao existam nos dentro da regiao; verdadeiro, caso contrario.
 */

bool getInfosDentroRegiaoSrbT(SpacRbTree t, double x1, double y1, double x2, double y2,
				 FdentroDeRegiao f, Lista L);
/* Insere na lista L os nos cujas respectivas informacoes associadas estao dentro da regiao
   delimitada pelos pontos (x1,y1) e (x2,y2). A funcao f e' usada para determinar se uma informacao
   armazenada na arvore esta' dentro da regiao.
   Retorna falso caso nao existam informacoes internas; verdadeiro, caso contrario.
 */

void visitaProfundidadeSrbT(SpacRbTree t, FvisitaNo f, void *aux);
/* Percorre a arvore em profundidade. Invoca a funcao f em cada no visitado.
   O apontador aux e' parametro em cada invocacao de f; assim alguns
   dados podem ser compartilhados entre as diversas invocacoes de f.
 */

void visitaLarguraSrbT(SpacRbTree t, FvisitaNo f, void *aux);
/* Similar a visitaProfundidadeRadialT, porem, faz o percurso em largura.
 */

Node procuraNoSrbT(SpacRbTree t, FsearchNo f, void *aux);
/* Procura o no' da arvore que contenha um dado especifico.
   Visita cada no' da arvore e invoca a funcao f. A funcao f
   retornara' verdadeiro se o no' contem o dado procurado.
   Neste caso, retorna o no' encontrado. Caso a busca falhe,
   retorna NULL.
 */

bool printDotSRbTree(SpacRbTree t, char *fn);
/* Gera representacao da arvore no arquivo fn, usando a Dot Language
   (ver https://graphviz.org/). Retorna falso, caso o arquivo nao possa
   ser criado (para escrita); true, caso contrario)
*/

void getRelatorioSrbT(SpacRbTree t, char *buf, int n);
/* Copia em buf (cujo tamanho e' n) um relatorio sobre o uso
   da árvore.
 */

void killSrbTree(SpacRbTree t);
/* Libera a memoria usada pela arvore t.
 * Fecha o arquivo (eventualmente) aberto em newSpacRbTree.
 */
#endif
