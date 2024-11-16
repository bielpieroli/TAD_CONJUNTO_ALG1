#include <stdbool.h>
#ifndef SET_H
    #define SET_H

    typedef struct SET_ SET;


    // Função para criar o TAD SET, permitindo escolher a implementação (array ou árvore)
    // Parâmetro 'escolha': 
    //    - 0 para implementar o conjunto com lista
    //    - 1 para implementar o conjunto com árvore binária
    SET *criar_set(int escolha);

    // Função para destruir o conjunto e liberar toda a memória alocada
    void destruir_set(SET *set);

    // Função para inserir um elemento no conjunto
    bool inserir_set(SET *set, int elemento);

    // Função para remover um elemento do conjunto
    bool remover_set(SET *set, int elemento);

    // Função para verificar se um elemento pertence ao conjunto
    bool pertence_set(SET *set, int elemento);

    // Função para realizar a união de dois conjuntos, retornando um novo conjunto com o resultado
    SET *uniao_set(SET *set1, SET *set2);

    // Função para realizar a interseção de dois conjuntos, retornando um novo conjunto com o resultado
    SET *intersecao_set(SET *set1, SET *set2);

    // Função para imprimir os elementos do conjunto
    void imprimir_set(SET *set);

#endif // SET_H
