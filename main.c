#include <stdio.h>
#include "hashmap.h"
#include "test_hashmap.h"

int main(int argc, const char **argv) {
    test_todos();

    HashMap* hm = criar();

    char* chave_a = "chave a";
    char* valor_a = "valor a";

    char* chave_b = "chave b";
    char* valor_b = "valor b";

    char* chave_c = "chave c";
    char* valor_c = "valor c";

    char* chave_d = "chave d";
    char* valor_d = "valor d";

    inserir(hm, chave_a, valor_a);
    inserir(hm, chave_b, valor_b);
    inserir(hm, chave_c, valor_c);
    inserir(hm, chave_d, valor_d);

    printf("\nCapacidade: %zu\n", hm->capacidade);
    printf("Tamanho: %zu\n", hm->tamanho);
    
}