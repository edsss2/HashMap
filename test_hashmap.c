#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "test_hashmap.h"

void test_todos() {
    Metodos metodos[] = {test_criar, test_inserir, test_atualizar, test_buscar, test_excluir, test_encontrar_proximo_primo};
    int length = sizeof(metodos) / sizeof(metodos[0]);
    int n = 0;
    for(int i = 0; i < length; i++){
        n = metodos[i].handler();
        if(n == 1) {
            printf("Ok!\n");
        } else {
            printf("Erro!\n");
        }
    }
}

int test_criar() {
    HashMap* hm = criar();

    if (hm == NULL) return 0;

    if (hm->tamanho != 0) return 0;

    if (hm->capacidade != 5) return 0;

    if (hm->tabela == NULL) return 0;

    free(hm->tabela);
    free(hm);

    return 1;
}

int test_inserir() {
    HashMap* hm = criar();

    char* chave = "chave";
    char* valor = "valor";
    
    int i = inserir(hm, chave, valor);

    free(hm->tabela);
    free(hm);

    return i;
}

int test_atualizar() {
    HashMap* hm = criar();

    char* chave = "chave";
    char* valor = "valor";
    
    int i = inserir(hm, chave, valor);
    if(i == 0) { return i; }

    valor = "novo valor";
    i = atualizar(hm, chave, valor);

    free(hm->tabela);
    free(hm);

    return i;
}

int test_buscar() {
    HashMap* hm = criar();

    char* chave_a = "chave a";
    char* valor_a = "valor a";

    char* chave_b = "chave b";
    char* valor_b = "valor b";

    char* chave_c = "chave c";
    char* valor_c = "valor c";

    inserir(hm, chave_a, valor_a);
    inserir(hm, chave_b, valor_b);
    inserir(hm, chave_c, valor_c);

    //printf("Os valores foram inseridos!\n");

    int i = strcmp(buscar(hm, chave_b), valor_b);

    free(hm->tabela);
    free(hm);

    return i + 1;
}

int test_excluir(){
    HashMap* hm = criar();

    char* chave_a = "chave a";
    char* valor_a = "valor a";

    char* chave_b = "chave b";
    char* valor_b = "valor b";

    char* chave_c = "chave c";
    char* valor_c = "valor c";

    inserir(hm, chave_a, valor_a);
    inserir(hm, chave_b, valor_b);
    inserir(hm, chave_c, valor_c);

    int i = strcmp(excluir(hm, chave_b), valor_b);
    if(i != 0) { return 0; }

    if(buscar(hm, chave_b) != NULL) { return 0; }

    free(hm->tabela);
    free(hm);

    return 1;
}

int test_encontrar_proximo_primo() {
    int primos[] = {5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};
    int length = sizeof(primos) / sizeof(primos[0]);
    int i = 0;
    int p = 2;

    while(i < length) {
        int n = p + 1;
        p = encontrar_proximo_primo(n);
        if(primos[i] != p) { return 0; }

        i++;
    }

    return 1;
}