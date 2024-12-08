#include <stdio.h>
#include <stdlib.h>
#include "set.h"
// Estrutura de conjunto (SET)
struct SET_ {
    // Os seus campos são ponteiros para funções
    void (*criar) (SET *);
    bool (*inserir)(SET *, int elemento);
    bool (*remover)(SET *, int elemento);
    bool (*pertence)(SET *, int elemento);
    void (*imprimir)(SET *);
    void (*apagar)(SET **);
    SET *(*uniao) (SET *, SET *);
    SET *(*intersecao) (SET *, SET *);
    void *implementacao; 
    int tipo;
}; 

// Funções para o TAD SET
SET *set_criar(unsigned char escolha) {
    SET *set = malloc(sizeof(SET));
    if (set == NULL) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    if (escolha == 0) { // Implementação com AVL
        set->inserir = (bool (*)(SET *, int))AVL_inserir;
        set->remover = (bool (*)(SET *, int))AVL_remover;
        set->pertence = (bool (*)(SET *, int))AVL_consulta;
        set->imprimir = (void (*)(SET *))print_arvore;
        set->apagar = (void (*)(SET **))AVL_apagar;
        set->uniao = (SET *(*)(SET *, SET *))AVL_uniao;
        set->intersecao = (SET *(*)(SET *, SET *))AVL_intersecao;
        set->implementacao = AVL_criar();
        set->tipo = 0;
    } else if (escolha == 1) { // Implementação com Red-Black Tree
        set->inserir = (bool (*)(SET *, int))RBT_inserir;
        set->remover = (bool (*)(SET *, int))RBT_remover;
        set->pertence = (bool (*)(SET *, int))RBT_busca;
        set->imprimir = (void (*)(SET *))RBT_imprimir;
        set->apagar = (void (*)(SET **))RBT_apagar;
        set->uniao = (SET *(*)(SET *, SET *))RBT_uniao;
        set->intersecao = (SET *(*)(SET *, SET *))RBT_intersecao;
        set->implementacao = RBT_criar();
        set->tipo = 1;
    } else {
        printf("A escolha deve ser 0 ou 1, essa escolha é inválida\n");
    }
    return set;
}

void set_apagar(SET **set) {
    if (*set != NULL) {
         (*set)->apagar((SET **)&(*set)->implementacao); 
        
        free(*set); 
        *set = NULL;  
    }
}

bool set_inserir(SET *set, int elemento) {
    return set->inserir(set->implementacao, elemento);
}

bool set_remover(SET *set, int elemento) {
    return set->remover(set->implementacao, elemento);
}

bool set_pertence(SET *set, int elemento) {
    return set->pertence(set->implementacao, elemento);
}


SET *set_uniao(SET *A, SET *B) {
    SET *newset;
    newset = set_criar(A->tipo);
    free(newset->implementacao);
    newset->implementacao = newset->uniao(A->implementacao, B->implementacao);
    return newset;
}


SET *set_intersecao(SET *A, SET *B) {
    SET *newset;
    newset = set_criar(A->tipo);
    free(newset->implementacao);
    newset->implementacao = newset->intersecao(A->implementacao, B->implementacao);
    return newset;
}

void set_imprimir(SET *set) {
    set->imprimir(set->implementacao);
}