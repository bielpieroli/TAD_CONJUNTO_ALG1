#ifndef LLRBT_H
    #define LLRBT_H
    typedef struct red_black_tree RBT;

    // Aloca memória e retorna um ponteiro para Red Black Tree
    RBT *RBT_criar();

    // Libera toda a memoria da estrutura, retorna true se conseguir
    bool RBT_apagar(RBT **tree);

    // Retorna true caso consiga inserir o dado na árvore, e false caso contrário
    bool RBT_inserir(RBT *tree, int dado);

    // Faz um percurso em ordem e printa o dado de cada nó
    void percurso_em_ordem(RBT *tree);

    // Retorna true se o elemento está presente na árvore, e false caso contrário
    bool RBT_busca(RBT *tree, int dado);

    // Procura um item pela chave e o remove da árvore.
    // Retorna true caso consiga remover, e false caso contrário (o elemento pode não existir)
    bool RBT_remover(RBT *tree, int chave);

    RBT *RBT_uniao(RBT *A, RBT *B);
#endif