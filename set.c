#include <stdio.h>
#include <stdlib.h>
#include "set.h"

// Estrutura de conjunto (SET)
struct SET_ {
    // Um campo inteiro que armazena o tipo de implementação escolhida pelo usuário
    int tipo;
    // Os demais campos são todos ponteiros para funções 
    bool (*inserir)(SET *, int elemento);
    bool (*remover)(SET *, int elemento);
    bool (*pertence)(SET *, int elemento);
    void (*imprimir)(SET *);
    void (*apagar)(SET **);
    SET *(*uniao) (SET *, SET *);
    SET *(*intersecao) (SET *, SET *);
    void *implementacao; 
    
}; 

    // Parâmetro 'escolha': 
    //    - 0 para implementar o conjunto com Árvore AVL
    //    - 1 para implementar o conjunto com Red-Black Tree
    
/// @brief Função que cria o SET segundo a escolha do usuário, definindo os campos de ponteiros para funções da struct, de acordo com a implementação desejada
/// @param escolha 
/// @return SET *, ou seja, o SET criado, com todas as funções definidas segundo a implementação almejada 
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
        set->imprimir = (void (*)(SET *))AVL_em_ordem;
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

/// @brief Função que a implementação da função de apagar da estrutura desejada
/// @param set 
void set_apagar(SET **set) {
    if (*set != NULL) {
         (*set)->apagar((SET **)&(*set)->implementacao); 
        
        free(*set); 
        *set = NULL;  
    }
}

/// @brief Função que chama a implementação da função de inserção da estrutura desejada
/// @param set 
/// @param elemento 
/// @return bool, ou seja, se o elemento foi possível ou não inserir o elemento
bool set_inserir(SET *set, int elemento) {
    return set->inserir(set->implementacao, elemento);
}

/// @brief Função que chama a implementação da função remoção da estrutura desejada
/// @param set 
/// @param elemento 
/// @return bool, ou seja, se o elemento foi possível ou não remover o elemento
bool set_remover(SET *set, int elemento) {
    return set->remover(set->implementacao, elemento);
}

/// @brief Função que chama a implementação de busca da estrutura desejada
/// @param set 
/// @param elemento 
/// @return bool, ou seja, se o elemento foi ou não encontrado dentro do conjunto
bool set_pertence(SET *set, int elemento) {
    return set->pertence(set->implementacao, elemento);
}

/// @brief Função que chama a implementação da função de união da estrutura desejada
/// @param A 
/// @param B 
/// @return SET *, isto é, o ponteiro para o SET resultante da união entre os dois conjuntos
SET *set_uniao(SET *A, SET *B) {
    SET *newset;
    newset = set_criar(A->tipo);
    // Em set_criar, é criada uma implementação, a qual deve ser apagada, antes de receber uma nova
    free(newset->implementacao);
    newset->implementacao = newset->uniao(A->implementacao, B->implementacao);
    return newset;
}

/// @brief Função que chama a implementação da função de interseção da estrutura desejada
/// @param A 
/// @param B 
/// @return SET *, isto é, o ponteiro para o SET resultante da interseção entre os dois conjuntos
SET *set_intersecao(SET *A, SET *B) {
    SET *newset;
    newset = set_criar(A->tipo);
    // Em set_criar, é criada uma implementação, a qual deve ser apagada, antes de receber uma nova
    free(newset->implementacao);
    newset->implementacao = newset->intersecao(A->implementacao, B->implementacao);
    return newset;
}

/// @brief Função que chama a implementação da função de imprimir da estrutura desejada
/// @param set 
void set_imprimir(SET *set) {
    set->imprimir(set->implementacao);
}