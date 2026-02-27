# C HashMap (Tabela de Dispersão)

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue?style=flat-square)
![Status](https://img.shields.io/badge/Status-Conclu%C3%ADdo-success?style=flat-square)
![Compilador](https://img.shields.io/badge/Compilador-GCC-yellow?style=flat-square&logo=gnu)


Implementação de uma estrutura de dados HashMap construída do zero em C. O projeto gerencia dados dinâmicos no formato chave-valor (`char*` -> `char*`) e implementa algoritmos de redimensionamento em tempo de execução.

## 🧠 Funcionamento da Estrutura



Esta implementação utiliza uma **Tabela de Dispersão** com tratamento de colisões por *Separate Chaining*. O funcionamento lógico ocorre nas seguintes etapas:

1. **Hashing:** Uma função matemática processa a string da chave (somando os valores ASCII de seus caracteres) e calcula o módulo com a capacidade atual para determinar um índice exato (Bucket) no vetor.
2. **Armazenamento:** O ponteiro do valor correspondente é guardado neste índice.
3. **Colisões:** Se múltiplas chaves resultarem no mesmo índice numérico, os nós são empilhados no mesmo Bucket utilizando uma Lista Encadeada simples (`HashEntry->proximo`).

## ⚙️ Especificações Técnicas

* **Capacidade Inicial:** O HashMap é inicializado com 5 *buckets*.
* **Fator de Carga (Load Factor):** O monitoramento ocorre a cada inserção. Se a razão entre o tamanho atual e a capacidade exceder `0.60` (60%), a estrutura força um redimensionamento.
* **Rehashing Dinâmico:** A nova capacidade da tabela é calculada buscando matematicamente o próximo **número primo** a partir do dobro da capacidade anterior. O uso de capacidades primas diminui os agrupamentos indexados e melhora a eficiência da busca.
* **Operações Disponíveis:**
  * `criar()`: Instancia e aloca o mapa.
  * `inserir(map, chave, valor)`: Insere novos nós, monitorando o limite de carga.
  * `buscar(map, chave)`: Varredura linear na lista do índice correspondente para retorno do valor.
  * `atualizar(map, chave, valor)`: Substitui valores existentes.
  * `excluir(map, chave)`: Remove nós e reordena os ponteiros da lista encadeada, liberando a memória do nó.

## 💻 Exemplo de Uso

```c
#include <stdio.h>
#include "hashmap.h"

int main() {
    // Inicialização da estrutura
    HashMap* mapa = criar();

    // Inserção de dados
    inserir(mapa, "user_1", "Administrador");
    inserir(mapa, "user_2", "Operador");

    // Busca de dados
    char* permissao = buscar(mapa, "user_1");
    if (permissao != NULL) {
        printf("Permissão encontrada: %s\n", permissao);
    }

    // Atualização
    atualizar(mapa, "user_2", "Supervisor");

    // Exclusão
    excluir(mapa, "user_1");

    return 0;
}
