#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

typedef struct HashEntry {
    char* chave;
    char* valor;
    struct HashEntry* proximo;
}HashEntry;

typedef struct {
    []HashEntry tabela;
    size_t tamanho;
}HashMap;

void add(char *chave, char *valor);
char *buscar(char *chave);
char *excluir(char *chave);
int hash(char *chave);



#endif