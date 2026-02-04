#include <stdio.h>
#include "hashmap.h"

HashMap hashMap = {
    .tabela = {0},
    .tamanho = 0,
    .capacidade = CAPACIDADE
};

int hash(char *chave, int capacidade) {
    int hash = 0;

    while (*chave) {
        hash += *chave;
        chave++;
    }

    return hash % capacidade;
}

void add(HashMap* map, char *chave, char *valor) {
    int indice = hash(chave, map->capacidade);

    map->tabela[indice].chave = chave;
    map->tabela[indice].valor = valor;
    if(!map->tabela[indice].chave) {
        map->tamanho++;
    }

}

char* buscar(HashMap* map, char *chave) {
    int indice = hash(chave, map->capacidade);
    char* chave_tabela = map->tabela[indice].chave;

    if (chave_tabela && strcmp(chave_tabela, chave) == 0){
            return map->tabela[indice].valor;
    }

    return NULL;
}

char* excluir(HashMap* map, char *chave) {
    int indice = hash(chave, map->capacidade);
    char* chave_tabela = map->tabela[indice].chave;

    if (!chave_tabela || strcmp(chave_tabela, chave) != 0){
        return NULL;
    }

    char* elemento = map->tabela[indice].valor;

    map->tabela[indice].valor = 0;
    map->tabela[indice].chave = 0;

    return elemento;

}


