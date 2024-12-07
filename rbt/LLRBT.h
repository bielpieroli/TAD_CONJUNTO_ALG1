#ifndef LLRBT_H
    #define LLRBT_H
    typedef struct red_black_tree RBT;

    RBT *RBT_criar();
    bool RBT_inserir(RBT *tree, int dado);
    void percurso_em_ordem(RBT *tree);

    //retorna true se o elemento está presente na árvore, e false caso contrário
    bool RBT_busca(RBT *tree, int dado);
    bool RBT_remover(RBT *tree, int chave);
#endif