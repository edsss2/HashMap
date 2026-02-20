#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

static int hash(char *chave, int capacidade) {
    int hash = 0;

    while (*chave) {
        hash += *chave;
        chave++;
    }

    return hash % capacidade;
}

static HashEntry* percorrer_lista(HashMap* map, char *chave) {
    int indice = hash(chave, map->capacidade);
    HashEntry* atual = map->tabela[indice];

    while(atual) {
        if(strcmp(atual->chave, chave) == 0) {
            return atual;
        }
        if(!atual->proximo) {
            return atual;
        }

        atual = atual->proximo;

    }

    return NULL;
}

static int encontrar_proximo_primo(int n) {
    if(n / 2 == 0){n++;}

    return encontrar_primo(n, 3);
}

static int encontrar_primo(int n, int primo) {
    int resto = n % primo;
    int quociente = n / primo;

    if(resto != 0 && quociente < primo) {
        return n;
    }

    if(primo > n) {
        n+2;
    }

    return encontrar_primo(n, encontrar_proximo_primo(primo + 2));
}

static void redimensionar_tabela(HashMap* map) {
    int nova_capacidade = encontrar_proximo_primo(map->capacidade * 2);
}

HashMap* criar() {
    HashMap* hashMap;
    int capacidade = 5;

    hashMap = malloc(sizeof(HashMap));
    hashMap->tabela = calloc(capacidade, sizeof(HashEntry *));
    hashMap->tamanho = 0;
    hashMap->capacidade = capacidade;
}

void add(HashMap* map, char *chave, char *valor) {
    int indice = hash(chave, map->capacidade);
    HashEntry* atual = map->tabela[indice];

    while (atual) {
        if (strcmp(atual->chave, chave) == 0) {
            return -1;
        }
        if (!atual->proximo) break;
        atual = atual->proximo;
    }

    HashEntry* novo = malloc(sizeof(HashEntry));

    novo->chave = chave;
    novo->valor = valor;
    novo->proximo = NULL;

    if (!map->tabela[indice]) {
        map->tabela[indice] = novo;
    } else {
        atual->proximo = novo;
    }

    map->tamanho++;
}

int atualizar(HashMap* map, char *chave, char *valor) {
    HashEntry* atual = percorrer_lista(map, chave);

    if (atual && strcmp(atual->chave, chave) == 0) {
        atual->valor = valor;
        return 1;
    }

    return 0;
}


char* buscar(HashMap* map, char *chave) {
    HashEntry* atual = percorrer_lista(map, chave);

    if (atual && strcmp(atual->chave, chave) == 0) {
        return atual->valor;
    }

    return NULL;
}

char* excluir(HashMap* map, char *chave) {
    int indice = hash(chave, map->capacidade);

    HashEntry* atual = map->tabela[indice];
    HashEntry* anterior = NULL;

    while(atual) {
        if(strcmp(atual->chave, chave) == 0) {
            if(anterior) {
                anterior->proximo = atual->proximo;
            } else {
                map->tabela[indice] = atual->proximo;
            }

            char* valor = atual->valor;
            free(atual);
            map->tamanho--;
            return valor;
        }

        anterior = atual;
        atual = atual->proximo;

    }
    return NULL;

}


