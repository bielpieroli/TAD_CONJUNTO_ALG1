#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvoreAVL.h"

struct NO_{
    int chave;
    int alt;
    NO *esq;
    NO *dir;
};

struct ARVORE_AVL{
    int profundidade;
    NO *raiz;
};

AVL* AVL_criar() {
    AVL* T = (AVL*)malloc(sizeof(AVL));
    if (T != NULL) {
        T->profundidade = -1;
        T->raiz = NULL;
    }
    return T;
}

void no_liberar(NO** raiz) {
    if (*raiz != NULL) {
        no_liberar(&(*raiz)->esq);
        no_liberar(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }
}

void AVL_apagar(AVL** T) {
    if (*T == NULL)
        return;
    no_liberar(&((*T)->raiz));
    free(*T);
    T = NULL;
}

int no_altura(NO* no) {
    if (no == NULL) {
        return -1;
    }
    return no->alt;
}

int max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    } 
}

int fator_de_balanceamento(NO* no) {
    return (no_altura(no->esq) - no_altura(no->dir));
}

bool AVL_vazia(AVL* avl) {
    if(avl == NULL || avl->raiz == NULL) {
        return true;
    }
}

int AVL_total_nos(NO* no) {
    if (no == NULL) {
        return 0;
    }
    return (AVL_total_nos(no->esq) + AVL_total_nos(no->dir) + 1);
}

int AVL_total(AVL *T) {
    if (T != NULL) {
        return (AVL_total_nos(T->raiz));
    }
    return 0;
}

int AVL_altura(AVL* avl) {
    if (avl == NULL || avl->raiz == NULL)
        return 0;
    return avl->raiz->alt;
}

void no_pre_ordem(NO* no) {
    if (no == NULL)
        return;
    printf("Nó %d: Altura(%d)\n", no->chave, no->alt);
    no_pre_ordem(no->esq);
    no_pre_ordem(no->dir);
}

void AVL_pre_ordem(AVL* avl) {
    if (avl != NULL)
        no_pre_ordem(avl->raiz);
}

void no_em_ordem(NO* no) {
    if (no == NULL)
        return;
    no_em_ordem(no->esq);
    printf("Nó %d: Altura(%d), Fator de Balanceamento(%d)\n", no->chave, no->alt, fator_de_balanceamento(no));
    no_em_ordem(no->dir);
}

void AVL_em_ordem(AVL* avl) {
    if (avl != NULL)
        no_em_ordem(avl->raiz);
}

void no_pos_ordem(NO* no) {
    if (no == NULL)
        return;
    no_pos_ordem(no->esq);
    no_pos_ordem(no->dir);
    printf("%d\n", no->chave);
}

void AVL_pos_ordem(AVL* avl) {
    if (avl != NULL)
        no_pos_ordem(avl->raiz);
}

NO *rotacaoL(NO* A) {
    if (A == NULL) {
        printf("Erro: A é nulo\n");
        return NULL; 
    }
    NO* B = A->dir;
    if (B == NULL) {
        printf("Erro: B é nulo\n");
        return NULL; 
    }
    A->dir = B->esq;
    B->esq = A;
    A->alt = max(no_altura(A->esq), no_altura(A->dir)) + 1;
    B->alt = max(no_altura(A), no_altura(B->dir)) + 1;
    return B;
}

NO *rotacaoR(NO* A) {
    if (A == NULL) {
        printf("Erro: A é nulo\n");
        return NULL; 
    }
    NO* B = A->esq;
    if (B == NULL) {
        printf("Erro: B é nulo\n");
        return NULL; 
    }
    A->esq = B->dir;
    B->dir = A;
    A->alt = max(no_altura(A->esq), no_altura(A->dir)) + 1;
    B->alt = max(no_altura(B->esq), no_altura(A)) + 1;
    return B;
}

NO *rotacaoLR(NO* A) {
    A->esq = rotacaoL(A->esq);
    return rotacaoR(A);
}

NO *rotacaoRL(NO* A) {
    A->dir = rotacaoR(A->dir);
    return rotacaoL(A);
}
NO *no_criar(int chave) {
    NO* novo = (NO*)malloc(sizeof(NO));
    if (novo != NULL) {
        novo->chave = chave;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

NO *AVL_no_inserir(NO* raiz, int chave) {
    if (raiz == NULL) { 
        raiz = no_criar(chave);
    } else if (chave < raiz->chave) {
        raiz->esq = AVL_no_inserir(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = AVL_no_inserir(raiz->dir, chave);
    }
    raiz->alt = max(no_altura(raiz->esq),no_altura(raiz->dir)) + 1;
    if (fator_de_balanceamento(raiz) <= -2) {
        if (fator_de_balanceamento(raiz->dir) <= 0)
            raiz = rotacaoL(raiz);
        else
            raiz = rotacaoRL(raiz);
    }
    if (fator_de_balanceamento(raiz) >= 2) {
        if (fator_de_balanceamento(raiz->esq) >= 0)
            raiz = rotacaoR(raiz);
        else
            raiz = rotacaoLR(raiz);
    }
    return raiz;
}

bool AVL_inserir(AVL* avl, int chave) {
    if (avl == NULL) {
        return false;
    }
    NO* pos_insercao = AVL_no_inserir(avl->raiz, chave);
    bool resultado;
    if (pos_insercao == NULL) {
        resultado = false;
    } else {
        avl->raiz = pos_insercao;
        avl->profundidade = AVL_altura(avl);
        resultado = true;
    }
    return resultado;
}


void AVL_troca_no_max_esq(NO* troca, NO *raiz, NO *ant) {
    if(troca->dir != NULL) {
        AVL_troca_no_max_esq(troca->dir, raiz, troca);
        return;
    }
    if (raiz == ant) {
        ant->esq = troca->esq;
    } else {
        ant->dir = troca->esq;
    }
    raiz->chave = troca->chave;
    free(troca);
    troca = NULL;
}

NO *AVL_no_remover(NO** raiz, int chave) {
    if (*raiz == NULL) { // Valor não encontrado
        //printf("Chave não encontrada!\n");
        return NULL;
    } else if (chave < (*raiz)->chave) {
        (*raiz)->esq = AVL_no_remover(&(*raiz)->esq, chave);
    } else if (chave > (*raiz)->chave) {
        (*raiz)->dir = AVL_no_remover(&(*raiz)->dir, chave);
    } else if (chave == (*raiz)->chave) { // Encontrou o nó a ser removido
        NO *aux;
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) { // Nó com 1 ou nenhum filho
            aux = *raiz;
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(aux);
            aux = NULL;
        } else { // Nó com 2 filhos
            AVL_troca_no_max_esq((*raiz)->esq,(*raiz), (*raiz));
        }
    }
    if (*raiz != NULL) {
        (*raiz)->alt = max(no_altura((*raiz)->esq), no_altura((*raiz)->dir)) + 1;
        if (fator_de_balanceamento(*raiz) >= 2) { 
            if (fator_de_balanceamento((*raiz)->esq) >= 0)
                *raiz = rotacaoR(*raiz); 
            else
                *raiz = rotacaoLR(*raiz); 
        }
        if (fator_de_balanceamento(*raiz) <= -2) { 
            if (fator_de_balanceamento((*raiz)->dir) <= 0)
                *raiz = rotacaoL(*raiz); 
            else
                *raiz = rotacaoRL(*raiz); 
        }
    }
    return *raiz;
}

bool AVL_remover(AVL* avl, int chave) {
    if (avl == NULL) {
        return false;
    }
    if (AVL_consulta(avl, chave)) {
        NO* pos_remocao = AVL_no_remover(&(avl->raiz), chave);
        bool resultado;
        if (pos_remocao == NULL) {
            resultado = false;
        } else {
            avl->raiz = pos_remocao;
            avl->profundidade = AVL_altura(avl);
            resultado = true;
        }
        return resultado;
    } else {
        return false;
    }
}


bool no_consulta(NO* no, int chave) {
    while (no != NULL) {
        if (chave == no->chave)
            return true;
        if (chave < no->chave)
            no = no->esq;
        else
            no = no->dir;
    }
    return false;
}

bool AVL_consulta(AVL* avl, int chave) {
    if (avl == NULL || avl->raiz == NULL)
        return 0;
    return no_consulta(avl->raiz, chave);
}


void print_espacos(int nivel) {
    for (int i = 0; i < nivel; i++) {
        printf("    "); 
    }
}


void print_estrutura(NO* raiz, int nivel) {
    if (raiz == NULL) {
        print_espacos(nivel);
        printf("~\n"); 
        return;
    }
    print_estrutura(raiz->dir, nivel + 1);
    print_espacos(nivel);
    printf("%d\n", raiz->chave);
    print_estrutura(raiz->esq, nivel + 1);
}

void print_arvore(AVL *T) {
    printf("Árvore AVL:\n");
    print_estrutura(T->raiz, 0);
}
