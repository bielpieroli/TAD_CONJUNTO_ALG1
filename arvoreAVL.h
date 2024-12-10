#ifndef ARVORE_AVL_H_
    #define ARVORE_AVL_H_

    // ESTE É O TAD ARVORE_AVL_H
    #include <stdbool.h>

    // Typedef do nome das structs NO_ e ARVORE_AVL, para passar utilizar a nomenclatura NO e AVL, apenas
    typedef struct NO_ NO;
    typedef struct ARVORE_AVL AVL;

     
    /// @brief A função "AVL_criar" tem o papel de criar a estrutura de uma AVL e retornar ao usuário
    /// @return  AVL *, isto é, o ponteiro para a estrutura da árvore AVL
    AVL* AVL_criar();

    /// @brief A função "AVL_inserir" é responsável por efetuar a inserção de um dado na estrutura da AVL
    /// @param T 
    /// @param data 
    /// @return bool, ou seja, se foi possível ou não realizar a inserção
    bool AVL_inserir(AVL *T, int data);

    /// @brief A função "AVL_remover" é responsável por efetuar a remoção de determinado valor da AVL
    /// @param T 
    /// @param valor 
    /// @return bool, ou seja, se foi possível ou não realizar a remoção
    bool AVL_remover(AVL *T, int valor);

    /// @brief A função "AVL_consulta" tem a função de retornar ao usuário se determinado valor existe na AVL
    /// @param T 
    /// @param valor 
    /// @return bool, ou seja, se o valor foi encontrado ou não na árvore AVL
    bool AVL_consulta(AVL *T, int valor);

    /// @brief A função "AVL_apagar" tem o papel de liberar toda a memória alocada para a AVL
    /// @param T 
    void AVL_apagar(AVL **T);

    /// @brief A função "AVL_uniao" faz a união entre os conteúdos de duas árvores AVL(A e B), formando uma C com o resultado
    /// @param A 
    /// @param B 
    /// @return AVL *, isto é, o ponteiro para a estrutura AVL, resultado da união entre dois conjuntos
    AVL *AVL_uniao(AVL *A, AVL *B);

    /// @brief A função "AVL_intersecao" faz a intersecao entre os conteúdos de duas árvores AVL(A e B), formando uma C com o resultado
    /// @param A 
    /// @param B 
    /// @return AVL *, isto é, o ponteiro para a estrutura AVL, resultado da interseção entre dois conjuntos
    AVL *AVL_intersecao(AVL *A, AVL *B);

    /// @brief A função "AVL_em_ordem" printa as chaves guardadas na árvore, fazendo o percurso em ordem e, consequentemente, printando-as em ordem crescente
    /// @param T 
    void AVL_imprimir(AVL *T);

    bool AVL_vazia(AVL *T);
    int AVL_altura(AVL *T);
    int AVL_total(AVL *T);
    void AVL_pre_ordem(AVL *T);
    void AVL_pos_ordem(AVL *T);
    void print_arvore(AVL *T);
#endif