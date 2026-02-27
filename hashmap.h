/**
 * @file hashmap.h
 * @brief Interface pública da estrutura HashMap.
 *
 * Define a estrutura de dados e as operações disponíveis
 * para manipulação de uma tabela hash com encadeamento separado.
 */

#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

 /**
  * @brief Estrutura de um elemento da tabela Hash.
  * 
  * Armazena a chave o valor, e um ponteiro para o
  * próximo nó.
  */
typedef struct HashEntry {
    char* chave;
    char* valor;
    struct HashEntry* proximo;
}HashEntry;

/**
 * @brief Estrutura principal da tabela hash.
 *
 * Mantém o vetor, a capacidade atual
 * e a quantidade de elementos armazenados.
 */
typedef struct HashMap{
    HashEntry **tabela;
    size_t tamanho;
    size_t capacidade;
}HashMap;

HashMap* criar();
int inserir(HashMap* map, char *chave, char *valor);
int atualizar(HashMap* map, char *chave, char *valor);
char *buscar(HashMap* map, char *chave);
char *excluir(HashMap* map, char *chave);
int encontrar_proximo_primo(int n);


#endif