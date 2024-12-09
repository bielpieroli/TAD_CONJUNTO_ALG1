#ifndef SET_H
    #define SET_H

    // ESTE É O TAD SET_H

    #include <stdbool.h>
    #include "arvoreAVL.h" 
    #include "LLRBT.h"

    // Typedef do nome da struct, para passar utilizar a nomenclatura SET
    typedef struct SET_ SET;

    // Parâmetro 'escolha': 
    //    - 0 para implementar o conjunto com Árvore AVL
    //    - 1 para implementar o conjunto com Red-Black Tree

    /// @brief Função para criar o SET, conforme a escolha da implementação entre duas estruturas de dados (Árvore AVL ou Red-Black Tree))
    /// @param escolha 
    /// @return SET *, isto é, o ponterio para o SET criado segundo a escolha do usuário
    SET *set_criar(unsigned char escolha);

    /// @brief Função para inserir um elemento no conjunto
    /// @param set 
    /// @param elemento 
    /// @return bool, isto é, se a inserção foi ou não bem sucedida
    bool set_inserir(SET *set, int elemento);

    /// @brief Função para remover um elemento do conjunto
    /// @param set 
    /// @param elemento 
    /// @return bool, isto é, se a remoção foi ou não bem sucedida
    bool set_remover(SET *set, int elemento);

    /// @brief Função para buscar o elemento dentro do conjunto
    /// @param set 
    /// @param elemento 
    /// @return bool, isto é, se o elemente existe dentro da estrutura do conjunto
    bool set_pertence(SET *set, int elemento);

    /// @brief Função para realizar a união de dois conjuntos, retornando um novo conjunto com o resultado
    /// @param set1 
    /// @param set2 
    /// @return SET *, ou seja, o ponteiro para o conjunto resultado da união dos dois conjuntos recebidos via parâmetro
    SET *set_uniao(SET *set1, SET *set2);

    /// @brief Função para realizar a interseção de dois conjuntos, retornando um novo conjunto com o resultado
    /// @param set1 
    /// @param set2 
    /// @return SET *, ou seja, o ponteiro para o conjunto resultado da interseção dos dois conjuntos recebidos via parâmetro
    SET *set_intersecao(SET *set1, SET *set2);

    /// @brief Função para apagar o conjunto e liberar toda a memória alocada
    /// @param set 
    void set_apagar(SET **set);

    /// @brief Função para imprimir os elementos do conjunto
    /// @param set 
    void set_imprimir(SET *set);

#endif 
