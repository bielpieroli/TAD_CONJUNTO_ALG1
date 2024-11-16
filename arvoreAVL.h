#ifndef ARVORE_AVL_H_
    #define ARVORE_AVL_H_
    #include <stdbool.h>
    #define INF 100000010
    typedef struct NO_ NO;
    typedef struct ARVORE_AVL AVL;

    AVL* AVL_criar();
    void AVL_apagar(AVL **T);
    bool AVL_inserir(AVL *T, int data);
    bool AVL_remover(AVL *T, int valor);
    bool AVL_vazia(AVL *T);
    int AVL_altura(AVL *T);
    int AVL_total(AVL *T);
    bool AVL_consulta(AVL *T, int valor);
    void AVL_pre_ordem(AVL *T);
    void AVL_em_ordem(AVL *T);
    void AVL_pos_ordem(AVL *T);
    void print_arvore(AVL *T);
#endif