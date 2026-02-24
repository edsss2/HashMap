#ifndef TEST_HASHMAP_H
#define TEST_HASHMAP_H

#include <stddef.h>
#include "hashmap.h"

typedef int (*command_fn)();

typedef struct {
    command_fn handler;
} Metodos;

void test_todos();
int test_criar();
int test_inserir();
int test_atualizar();
int test_buscar();
int test_excluir();
int test_encontrar_proximo_primo();

#endif