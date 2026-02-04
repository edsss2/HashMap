#ifndef HASHMAP_H
#define HASHMAP_H
#define CAPACIDADE 101

#include <stddef.h>

typedef struct HashEntry {
    char* chave;
    char* valor;
}HashEntry;

typedef struct {
    HashEntry tabela[CAPACIDADE];
    size_t tamanho;
    size_t capacidade;
}HashMap;

int hash(char *chave, int capacidade);
void add(HashMap* map, char *chave, char *valor);
char *buscar(HashMap* map, char *chave);
char *excluir(HashMap* map, char *chave);


#endif