#include <stdbool.h>
#ifndef SET_H
    #define SET_H

    typedef struct SET_ SET;


    // Função para criar o TAD SET, permitindo escolher a implementação (lista ou árvore)
    // Parâmetro 'escolha': 
    //    - 0 para implementar o conjunto com lista
    //    - 1 para implementar o conjunto com árvore binária
    SET *set_criar(unsigned char escolha);

    // Função para inserir um elemento no conjunto
    bool set_inserir(SET *set, int elemento);

    // Função para remover um elemento do conjunto
    bool set_remover(SET *set, int elemento);

    // Função para verificar se um elemento pertence ao conjunto
    bool set_pertence(SET *set, int elemento);

    // Função para realizar a união de dois conjuntos, retornando um novo conjunto com o resultado
    SET *set_uniao(SET *set1, SET *set2);

    // Função para realizar a interseção de dois conjuntos, retornando um novo conjunto com o resultado
    SET *set_intersecao(SET *set1, SET *set2);

    // Função para apagar o conjunto e liberar toda a memória alocada
    void set_apagar(SET **set);

    // Função para imprimir os elementos do conjunto
    void set_imprimir(SET *set);

#endif // SET_H
