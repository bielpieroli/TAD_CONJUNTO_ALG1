#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lista.h"  
#include "arvoreAVL.h" 

// Estrutura de conjunto (SET)
struct SET_ {
    // Ponteiros para as funções
    void (*criar) (SET *);
    bool (*inserir)(SET *, int elemento);
    bool (*remover)(SET *, int elemento);
    bool (*pertence)(SET *, int elemento);
    void (*imprimir)(SET *);
    void (*apagar)(SET **);
    void *implementacao; 
}; 

// Funções para o TAD SET
SET *set_criar(unsigned char escolha) {
    SET *set = malloc(sizeof(SET));
    if (!set) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    if (escolha == 0) { // Implementação com lista
        set->inserir = (bool (*)(SET *, int))lista_inserir;
        set->remover = (bool (*)(SET *, int))lista_remover;
        set->pertence = (bool (*)(SET *, int))lista_procura;
        set->imprimir = (void (*)(SET *))lista_imprimir;
        set->apagar = (void (*)(SET **))lista_apagar;
        set->implementacao = lista_criar(true); 
    } else if (escolha == 1) {
        set->inserir = (bool (*)(SET *, int))AVL_inserir;
        set->remover = (bool (*)(SET *, int))AVL_remover;
        set->pertence = (bool (*)(SET *, int))AVL_consulta;
        set->imprimir = (void (*)(SET *))AVL_em_ordem;
        set->apagar = (void (*)(SET **))AVL_apagar;
        set->implementacao = AVL_criar();
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
    SET *resultado;
    return resultado;
}

SET *set_intersecao(SET *A, SET *B) {
    SET *resultado = criar_set()
    return resultado;
}

void set_imprimir(SET *set) {
    set->imprimir(set->implementacao);
}