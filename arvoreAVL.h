#ifndef ARVORE_AVL_H_
    #define ARVORE_AVL_H_

    // ESTE É O TAD ARVORE_AVL_H
    #include <stdbool.h>

    // Typedef do nome das structs NO_ e ARVORE_AVL, para passar utilizar a nomenclatura NO e AVL, apenas
    typedef struct NO_ NO;
    typedef struct ARVORE_AVL AVL;

    // A função "AVL_criar", cujo retorno tem tipo AVL *, tem o papel de criar a estrutura de uma AVL e retornar ao usuário
    AVL* AVL_criar();

    // A função "AVL_inserir", cujo retorno é do tipo booleano, é responsável por  efetuar a inserção de um dado na estrutura da AVL
    bool AVL_inserir(AVL *T, int data);

    // A função "lista_remover", cujo retorno é do tipo booleano, é responsável por efetuar a remoção de determinado valor da AVL
    bool AVL_remover(AVL *T, int valor);

    // A função "AVL_consulta", cujo retorno é do tipo booleano, tem a função de retornar ao usuário se determinado valor existe na AVL
    bool AVL_consulta(AVL *T, int valor);

    // A função "AVL_apagar", cujo retorno é do tipo void, tem o papel de liberar toda a memória alocada para a AVL */
    void AVL_apagar(AVL **T);

    // A função "AVL_uniao", cujo retorno é do tipo AVL *, faz a união entre os conteúdos de duas árvores AVL(A e B), formando uma C com o resultado
    AVL *AVL_uniao(AVL *A, AVL *B);

    // A função "AVL_intersecao", cujo retorno é do tipo AVL *, faz a intersecao entre os conteúdos de duas árvores AVL(A e B), formando uma C com o resultado
    AVL *AVL_intersecao(AVL *A, AVL *B);
    
    bool AVL_vazia(AVL *T);
    int AVL_altura(AVL *T);
    int AVL_total(AVL *T);
    void AVL_pre_ordem(AVL *T);
    void AVL_em_ordem(AVL *T);
    void AVL_pos_ordem(AVL *T);
    void print_arvore(AVL *T);
#endif