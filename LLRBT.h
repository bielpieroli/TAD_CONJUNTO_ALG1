#ifndef LLRBT_H
    #define LLRBT_H
    typedef struct red_black_tree RBT;

    /// @brief A função "RBT_criar" aloca memória dinamicamente a estrutura da Red Black Tree
    /// @return RBT *, isto é, retorna um ponteiro para a Red Black Tree
    RBT *RBT_criar();

    /// @brief A função "RBT_apagar" libera toda a memoria da estrutura,
    /// @param tree 
    /// @return bool, isto é, true se conseguir apagar, false se não conseguir
    bool RBT_apagar(RBT **tree);

    /// @brief A função "RBT_inserir" faz a inserção de um dado dentro da estrutura da Red Black Tree
    /// @param tree 
    /// @param dado 
    /// @return bool, isto é, retorna true caso consiga inserir o dado na árvore, e false caso contrário
    bool RBT_inserir(RBT *tree, int dado);

    /// @brief A função "RBT_imprimir" faz um percurso em ordem e printa o dado de cada nó
    /// @param tree 
    void RBT_imprimir(RBT *tree);

    /// @brief A função "RBT_busca" faz a busca por um dado na estrutura da Red Black Tree
    /// @param tree 
    /// @param dado 
    /// @return bool, isto é, retorna true se o elemento está presente na árvore, e false caso contrário
    bool RBT_busca(RBT *tree, int dado);

    
    /// @brief A função "RBT_remover" procura por uma chave e a remove da Red Black Tree
    /// @param tree 
    /// @param chave 
    /// @return bool, isto é, tRetorna true caso consiga remover, e false caso contrário (o elemento pode não existir)
    bool RBT_remover(RBT *tree, int chave);

    /// @brief A função "RBT_uniao" realiza a operação de união dos conteúdos de duas árvores RBT
    /// @param A 
    /// @param B 
    /// @return RBT *, ou seja, o ponteiro para a Red Black Tree resultante da união
    RBT *RBT_uniao(RBT *A, RBT *B);


    /// @brief A função "RBT_intersecao" realiza a operação de interseção dos conteúdos de duas árvores RBT
    /// @param A 
    /// @param B 
    /// @return RBT *, ou seja, o ponteiro para a Red Black Tree resultante da interseção
    RBT *RBT_intersecao(RBT *A, RBT *B);


    void RBT_imprimir_estrutura(RBT *arv);
#endif