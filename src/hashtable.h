#ifndef HASHTABLE__H_
#define HASHTABLE__H_
#include <stdbool.h>
/*
 * HashTable é um ponteiro para uma estrutura que contém uma tabela hash.
    * A tabela hash é uma lista encadeada de elementos do tipo hash.
    * Cada elemento hash contém uma chave, um valor e um tipo de valor.
    * O tipo de valor é um inteiro que indica o tipo do valor armazenado.
    * O valor é um ponteiro para uma lista.
    * A chave é uma string que identifica o valor na tabela.
    * 
 */


typedef void *HashTable;
typedef int DescTpValue;
typedef void *Value;


// cria uma nova tabela hash
HashTable newHashTable(char *fstat);
// fstat: arquivo para gravar estatisticas

// adiciona um valor à tabela hash
void addHt(HashTable h, char *chave, Value v, DescTpValue d);

// remove um valor da tabela hash
Value getHt(HashTable h, char *chave, DescTpValue *d);
// retorna valor e tipo do valor

// verifica se uma chave existe na tabela hash
bool existsHt(HashTable h, char *chave);

// retorna o relatório da tabela hash
void getRelatorioHt(HashTable h, char *buf, int n);

// libera a memória alocada pela tabela hash
void killHt(HashTable h);



#endif
