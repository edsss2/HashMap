#ifndef HASHMAP_H
#define HASHMAP_H
#define CAPACIDADE 101

#include <stddef.h>

typedef struct HashEntry {
    char* chave;
    char* valor;
    struct HashEntry* proximo;
}HashEntry;

typedef struct HashMap{
    HashEntry **tabela;
    size_t tamanho;
    size_t capacidade;
}HashMap;

HashMap* criar();
int add(HashMap* map, char *chave, char *valor);
int atualizar(HashMap* map, char *chave, char *valor);
char *buscar(HashMap* map, char *chave);
char *excluir(HashMap* map, char *chave);


#endif