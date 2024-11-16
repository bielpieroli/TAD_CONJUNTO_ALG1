#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "lista.h"  // Implementação baseada em lista
#include "arvoreAVL.h" // Implementação baseada em árvore binária

struct SET_ {
    void (*criar)(SET *);                     // Função para criar o conjunto
    void (*destruir)(SET *);                  // Função para destruir o conjunto
    bool (*inserir)(SET *, int elemento);     // Função para inserir um elemento no conjunto
    bool (*remover)(SET *, int elemento);     // Função para remover um elemento do conjunto
    bool (*pertence)(SET *, int elemento);    // Função para verificar se um elemento pertence ao conjunto
    SET *(*uniao)(SET *, SET *);              // Função para a união de dois conjuntos
    SET *(*intersecao)(SET *, SET *);         // Função para a interseção de dois conjuntos
    void (*imprimir)(SET *);                  // Função para imprimir os elementos do conjunto
    void *implementacao;                      // Ponteiro genérico para a implementação específica (ex. array ou árvore)
};

// Função para criar o TAD SET com a implementação escolhida
SET *set_criar(int escolha) {
    SET *set = malloc(sizeof(SET));
    if (set == NULL) {
        printf("Erro de alocação de memória para o conjunto\n");
        return NULL;
    }

    // Configura os ponteiros para funções com base na escolha do usuário
    if (escolha == 0) { // Implementação com lista
        set->criar = (void *(*)(void))lista_criar;
        set->destruir = (void (*)(void *))lista_apagar;
        set->inserir = (bool (*)(void *, int))lista_inserir;
        set->remover = (bool (*)(void *, int))lista_remover;
        set->pertence = (bool (*)(void *, int))lista_int;
        set->imprimir = (void (*)(void *))lista_imprimir;
        set->implementacao = lista_criar(1); // Cria a lista dinâmica ordenada
    } else if (escolha == 1) { // Implementação com árvore binária
        // set->criar = arvore_criar;
        // set->destruir = destruir_conjunto_arvore;
        // set->inserir = inserir_arvore;
        // set->remover = remover_arvore;
        // set->pertence = pertence_arvore;
        // set->uniao = uniao_arvore;
        // set->intersecao = intersecao_arvore;
        // set->imprimir = imprimir_arvore;
        // set->implementacao = criar_implementacao_arvore(); // Cria a árvore binária
    } else {
        fprintf(stderr, "Opção de implementação inválida\n");
        free(set);
        return NULL;
    }

    // Inicializa o conjunto chamando a função criar
    set->criar(set);
    return set;
}

// Função para destruir o conjunto e liberar a memória
void set_destruir(SET *set) {
    if (set != NULL) {
        set->destruir(set);        // Chama a função destruir da implementação
        free(set);                 // Libera a estrutura SET
    }
}

// Função para inserir um elemento no conjunto
bool set_inserir(SET *set, int elemento) {
    return set->inserir(set, elemento);
}

// Função para remover um elemento do conjunto
bool set_remover(SET *set, int elemento) {
    return set->remover(set, elemento);
}

// Função para verificar se um elemento pertence ao conjunto
bool set_pertence(SET *set, int elemento) {
    return set->pertence(set, elemento);
}

// Função para realizar a união de dois conjuntos, retornando um novo conjunto com o resultado
SET *set_uniao(SET *set1, SET *set2) {
    return set1->uniao(set1, set2);
}

// Função para realizar a interseção de dois conjuntos, retornando um novo conjunto com o resultado
SET *set_intersecao(SET *set1, SET *set2) {
    return set1->intersecao(set1, set2);
}

// Função para imprimir os elementos do conjunto
void set_imprimir(SET *set) {
    set->imprimir(set);
}
