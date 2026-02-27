/**
 * @file hashmap.c
 * @brief Implementação de uma tabela hash.
 *
 * Este arquivo fornece operações para criação, inserção, busca e remoção
 * de elementos em uma estrutura de dados do tipo HashMap.
 *
 * A resolução de colisões é realizada por meio de listas encadeadas, e
 * possui redimensionamento automático.
 *
 * @author Edson
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

 /**
  * @brief Gera um índice para o vetor de acordo com a capacidade.
  * 
  * @param chave String utilizada para gerar a posição no vetor.
  * @param capacidade Capacidade da tabela hash.
  * @return Índice da tabela hash.
  */
static int hash(char *chave, int capacidade) {
    int hash = 0;

    while (*chave) {
        hash += *chave;
        chave++;
    }

    return hash % capacidade;
}

/**
 * @brief percorre a lista a fim de encontrar um elemento compátivel.
 * 
 * @param map Ponteiro do HashMap a ser percorrido.
 * @param chave String utilizada para a busca do elemento.
 * @return O ponteiro do elemento encontrado, nulo, ou o
 * ultimo nó da lista encadeada.
*/
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

/**
 * @brief Encontra recursivamente o menor número primo maior ou igual a n.
 *
 * O método verifica se o número n é divisível por valores primos menores,
 * iniciando a verificação a partir de 3. Caso n não seja divisível pelo
 * primo atual e o quociente da divisão seja menor que o primo divisor,
 * conclui-se que n é primo.
 *
 * Se n for divisível pelo primo atual ou o processo atingir o próprio valor
 * de n, o número é incrementado e a verificação é reiniciada a partir do
 * menor primo disponível.
 *
 * @param n Número candidato à verificação de primalidade.
 * @param primo Número primo utilizado como divisor na verificação.
 * @return O menor número primo maior ou igual a n.
 */
static int encontrar_primo(int n, int primo) {
    int resto = n % primo;
    int quociente = n / primo;

    if(resto != 0 && quociente < primo) {
        return n;
    }

    if(primo == n || resto == 0) {
        return encontrar_primo(n + 2, 3);
    } else {
        return encontrar_primo(n, encontrar_proximo_primo(primo + 2));
    }
}

/**
 * @brief Transfere todos os elementos da tabela antiga para a nova.
 * 
 * Este método é utilizado exclusivamente no redimensionamento da tabela,
 * colocando elementos novos no início da lista encadeada.
 * 
 * @param map O Hashmap como um todo, com capacidade e tabela zeradas.
 * @param antiga_tabela Ponteiro da tabela com os nós que devem ser transferidos.
 * @param antiga_capacidade A capacidade de elementos que o map possuía antes
 * do redimensionamento.
 */
static void transferir_elementos(HashMap* map, HashEntry** antiga_tabela, int antiga_capacidade) {
    for(int i = 0; i < antiga_capacidade; i++) {
        HashEntry* atual = antiga_tabela[i];
        while (atual) {
            HashEntry* proximo_no = atual->proximo;
            int novo_indice = hash(atual->chave, map->capacidade);

            //Transfere o nó para início da lista no novo vetor
            atual->proximo = map->tabela[novo_indice];
            map->tabela[novo_indice] = atual;
            map->tamanho++;
            atual = proximo_no;
        }
    }  
}

/**
 * @brief Redimensiona o HashMap para que suporte novos elementos.
 * 
 * A tabela é completamente substituída para reposicionar os elementos de
 * acordo com um novo Hash que é gerado com a nova capacidade.
 * 
 * A capacidade do HashMap após o redimensionamento é o número primo maior e mais
 * próximo que o dobro da capacidade atual. 
 * 
 * @param map Ponteiro do HashMap
 */
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

    transferir_elementos(map, antiga_tabela, antiga_capacidade);

    free(antiga_tabela);

}

/**
 * @brief Aloca e inicializa uma nova instância de HashMap.
 *
 * Cria dinamicamente a estrutura HashMap com capacidade inicial de 5 posições.
 *
 * @return Ponteiro para o HashMap criado.
 */
HashMap* criar() {
    HashMap* hashMap;
    int capacidade = 5;

    hashMap = malloc(sizeof(HashMap));
    hashMap->tabela = calloc(capacidade, sizeof(HashEntry *));
    hashMap->tamanho = 0;
    hashMap->capacidade = capacidade;

    return hashMap;
}

/**
 * @brief Adiciona um novo elemento no HashMap
 * 
 * Se necessário redimensiona a tabela antes da inserção.
 * 
 * Encontra a posição do novo elemento no vetor e percorre a lista encadeada
 * para aloca-lo como último nó.
 * 
 * @param map Ponteiro do HashMap.
 * @param chave String que gera a posição do elemento no vetor.
 * @param valor String a ser guardado pelo HashMap.
 * @return 1 caso o método tenha sucesso, e 0 caso a chave já exista na estrutura.
 */
int inserir(HashMap* map, char *chave, char *valor) {
    //Fator de Carga
    float fc = (float) map->tamanho / map->capacidade;

    if(fc > 0.60) {
        redimensionar_tabela(map);
    }

    int indice = hash(chave, map->capacidade);
    HashEntry* atual = map->tabela[indice];

    while (atual) {
        if (strcmp(atual->chave, chave) == 0) {
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

/**
 * @brief Atualiza um item do HashMap.
 * 
 * @param map Ponteiro do HashMap.
 * @param chave A chave do item que vai ser atualizado.
 * @param valor O novo valor que irá substituir o valor atual.
 * @return Retorna 1 se um item foi atualizado e 0 caso não exista um elemento
 * com a chave passada como parâmetro.
 */
int atualizar(HashMap* map, char *chave, char *valor) {
    HashEntry* atual = percorrer_lista(map, chave);

    if (atual && strcmp(atual->chave, chave) == 0) {
        atual->valor = valor;
        return 1;
    }

    return 0;
}


/**
 * @brief Busca um membro do HashMap.
 * 
 * @param map Ponteiro do HashMap.
 * @param chave Chave utilizada para encontrar o elemento.
 * @return O valor guardado pela chave ou nulo caso nenhum elemento seja encontrado.
 */
char* buscar(HashMap* map, char *chave) {
    HashEntry* atual = percorrer_lista(map, chave);

    if (atual && strcmp(atual->chave, chave) == 0) {
        return atual->valor;
    }

    return NULL;
}

/**
 * @brief Remove um elemento do HashMap
 * 
 * @param map Ponteiro do HashMap.
 * @param chave Chave utilizada para encontrar o elemento.
 * @return O valor guardado pela chave ou nulo caso nenhum elemento seja encontrado.
 */
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

/**
 * @brief Ajusta o valor inicial de n e inicia a busca pelo próximo número primo.
 * 
 * Caso n seja par, seu valor é incrementado em 1 para que a verificação seja realizada
 * apenas em números ímpares.
 * 
 * A verificação se inicia utilizando o número 3 como primeiro divisor primo, por ser o 
 * menor número primo ímpar.
 * 
 * @param n Número candidato à verificação de primalidade.
 * @return A resposta do método que de fato implementa a recursão para encontrar
 * o número primo.
 */
int encontrar_proximo_primo(int n) {
    if(n % 2 == 0){n++;}

    return encontrar_primo(n, 3);
}


