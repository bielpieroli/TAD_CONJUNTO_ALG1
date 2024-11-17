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
    void (*destruir)(SET **);
    void *implementacao; 
}; 

// Funções para o TAD SET
SET *criar_set(int escolha) {
    SET *set = malloc(sizeof(SET));
    if (!set) {
        printf("Erro ao alocar memória\n");
        return NULL;
    }

    if (escolha == 0) { // Implementação com lista
        set->inserir = (bool (*)(SET *, int))lista_inserir;
        set->remover = (bool (*)(SET *, int))lista_remover;
        set->pertence = (bool (*)(SET *, int))lista_int;
        set->imprimir = (void (*)(SET *))lista_imprimir;
        set->destruir = (void (*)(SET **))lista_apagar;
        set->implementacao = lista_criar(true); 
    } else if (escolha == 1) {
        set->inserir = (bool (*)(SET *, int))AVL_inserir;
        set->remover = (bool (*)(SET *, int))AVL_remover;
        set->pertence = (bool (*)(SET *, int))AVL_consulta;
        set->imprimir = (void (*)(SET *))AVL_em_ordem;
        set->destruir = (void (*)(SET **))AVL_apagar;
        set->implementacao = AVL_criar();
    }


    return set;
}

void destruir_set(SET **set) {
    if (*set != NULL) {
         (*set)->destruir((SET **)&(*set)->implementacao); 
        
        free(*set); 
        *set = NULL;  
    }
}

bool inserir_set(SET *set, int elemento) {
    return set->inserir(set->implementacao, elemento);
}

bool remover_set(SET *set, int elemento) {
    return set->remover(set->implementacao, elemento);
}

bool pertence_set(SET *set, int elemento) {
    return set->pertence(set->implementacao, elemento);
}

void imprimir_set(SET *set) {
    set->imprimir(set->implementacao);
}