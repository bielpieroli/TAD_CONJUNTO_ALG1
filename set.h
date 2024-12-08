#ifndef SET_H
    #define SET_H

    // ESTE É O TAD SET_H

    #include <stdbool.h>
    #include "arvoreAVL.h" 
    #include "LLRBT.h"

    // Typedef do nome da struct, para passar utilizar a nomenclatura SET
    typedef struct SET_ SET;

    // Função para criar o TAD SET, conforme a escolha da implementação entre duas estruturas de dados (Árvore AVL ou Red-Black Tree))
    // Parâmetro 'escolha': 
    //    - 0 para implementar o conjunto com Árvore AVL
    //    - 1 para implementar o conjunto com Red-Black Tree
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

#endif 
