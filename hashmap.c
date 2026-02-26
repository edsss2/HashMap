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

static int encontrar_primo(int n, int primo) {
    int resto = n % primo;
    int quociente = n / primo;

    if(resto != 0 && quociente < primo) {
        return n;
    }

    if(primo == n | resto == 0) {
        return encontrar_primo(n + 2, 3);
    } else {
        return encontrar_primo(n, encontrar_proximo_primo(primo + 2));
    }
}

static int add(HashMap* map, HashEntry* entry) {
    int indice = hash(entry->chave, map->capacidade);
    HashEntry* atual = map->tabela[indice];

    while (atual) {
        if (strcmp(atual->chave, entry->chave) == 0) {
            return -1;
        }
        if (!atual->proximo) break;
        atual = atual->proximo;
    }

    map->tabela[indice] = entry;
    map->tamanho++;
}

static void redimensionar_tabela(HashMap* map) {
    int nova_capacidade, antiga_capacidade;
    HashEntry **nova_tabela, **antiga_tabela;

    nova_capacidade = encontrar_proximo_primo(map->capacidade * 2);
    nova_tabela = calloc(nova_capacidade, sizeof(HashEntry *));
    antiga_capacidade = map->capacidade;
    antiga_tabela = map->tabela;

    map->tabela = nova_tabela;
    map->capacidade = nova_capacidade;
    map->tamanho = 0;

    for(int i = 0; i < antiga_capacidade; i++) {
        if(antiga_tabela[i] != NULL) {
            HashEntry* atual = antiga_tabela[i];
            int indice = hash(atual->chave, nova_capacidade);
            add(map, atual);
        }
    }

    free(antiga_tabela);

}

HashMap* criar() {
    HashMap* hashMap;
    int capacidade = 5;

    hashMap = malloc(sizeof(HashMap));
    hashMap->tabela = calloc(capacidade, sizeof(HashEntry *));
    hashMap->tamanho = 0;
    hashMap->capacidade = capacidade;

    return hashMap;
}

int inserir(HashMap* map, char *chave, char *valor) {
    int indice = hash(chave, map->capacidade);
    HashEntry* atual = map->tabela[indice];
    //Fator de Carga
    float fc = (float) map->tamanho / map->capacidade;

    if(fc > 0.60) {
        redimensionar_tabela(map);
    }

    while (atual) {
        printf("\nAtual chave: %s\n", atual->chave);
        printf("\nChave do parametro: %s\n", chave);
        if (strcmp(atual->chave, chave) == 0) {
            printf("\nEle entrou na atualização\n");
            return 0;
        }
        if (!atual->proximo) break;
        atual = atual->proximo;
    }

    HashEntry* novo = malloc(sizeof(HashEntry));

    novo->chave = chave;
    novo->valor = valor;
    novo->proximo = NULL;

    if (!atual) {
        map->tabela[indice] = novo;
    } else {
        atual->proximo = novo;
    }

    map->tamanho++;
    return 1;
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

int encontrar_proximo_primo(int n) {
    if(n % 2 == 0){n++;}

    return encontrar_primo(n, 3);
}


