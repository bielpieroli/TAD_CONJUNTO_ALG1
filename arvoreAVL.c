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

struct ARVORE_{
    int profundidade;
    NO *raiz;
};
NO* no_criar() {
    NO *novo = (NO *)malloc(sizeof(NO));
    return novo;
}
int no_altura(NO *no) {
    if(no != NULL) {
        return no->alt;
    } else {
        return -1;
    }
}

int fator_de_balanceamento(NO *no) {
    return (labs(no_altura(no->esq) - no_altura(no->dir)));
}

int retorna_maior(int x, int y) {
    if(x > y) {
        return x;
    } else {
        return y;
    }
}

void rotacao_LL(NO **raiz) {
    NO *aux;
    aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = (*raiz);
    (*raiz)->alt =  retorna_maior(no_altura((*raiz)->esq), no_altura((*raiz)->dir)) + 1;
    aux->alt = retorna_maior(no_altura(aux->esq), no_altura((*raiz))) + 1;
    (*raiz)= aux;
}

void rotacao_RR(NO **raiz) {
    NO *aux;
    aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = (*raiz);
    (*raiz)->alt =  retorna_maior(no_altura((*raiz)->esq), no_altura((*raiz)->dir)) + 1;
    aux->alt = retorna_maior(no_altura(aux->dir), no_altura((*raiz))) + 1;
    (*raiz)= aux;
}

void rotacao_LR(NO **raiz) {
    rotacao_RR(&((*raiz)->esq));
    rotacao_LL(raiz);
}

void rotacao_RL(NO **raiz) {
    rotacao_LL(&((*raiz)->dir));
    rotacao_RR(raiz);
}

bool no_inserir(NO **raiz, int valor) {
    bool res;
    if (*raiz == NULL) {
        NO *novo;
        novo = no_criar();
        if (novo == NULL) {
            return 0;
        }
        novo->chave = valor;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    NO *atual = *raiz;
    if(valor < atual->chave) {
        if ((res = no_inserir(&(atual->esq), valor)) == 1) {
            if(fator_de_balanceamento(atual) >= 2) {
                if(valor < atual->esq->chave) {
                    rotacao_LL(raiz);
                } else {
                    rotacao_LR(raiz);
                }
            }
        }
    } else if(valor > atual->chave) {
            if ((res = no_inserir(&(atual->dir), valor)) == 1) {
                if(fator_de_balanceamento(atual) >= 2) {
                    if(valor > atual->dir->chave) {
                        rotacao_RR(raiz);
                    } else {
                        rotacao_RL(raiz);
                    }
                }
            }
    } else {
        printf("Essa chave já existe\n");
        return 0;
    }
    atual->alt = retorna_maior(no_altura(atual->esq), no_altura(atual->dir))+1;
    return res;
}
bool avl_inserir(AVL *T, int valor) {
    return(no_inserir(&(T->raiz), valor));
}
