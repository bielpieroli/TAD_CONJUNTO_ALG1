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

void no_liberar(NO* raiz) {
    if (raiz != NULL) {
        no_liberar(raiz->esq);
        no_liberar(raiz->dir);
        free(raiz);
        raiz = NULL;
    }
}

void AVL_apagar(AVL** T) {
    if (*T == NULL)
        return;
    no_liberar((*T)->raiz);
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

void rotacaoLL(NO** raiz) {
    if (*raiz == NULL || (*raiz)->esq == NULL) {
        printf("Erro: não há nó à esquerda para rotação\n");
        return;  // Retorna sem fazer nada se não houver nó à esquerda
    }
    NO* aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    (*raiz)->alt = max(no_altura((*raiz)->esq), no_altura((*raiz)->dir)) + 1;
    aux->alt = max(no_altura(aux->esq), no_altura(*raiz)) + 1;
    *raiz = aux;
}

void rotacaoRR(NO** raiz) {
    NO* aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    (*raiz)->alt = max(no_altura((*raiz)->esq), no_altura((*raiz)->dir)) + 1;
    aux->alt = max(no_altura(aux->dir), no_altura(*raiz)) + 1;
    *raiz = aux;
}

void rotacaoLR(NO** raiz) {
    rotacaoRR(&(*raiz)->esq);
    rotacaoLL(raiz);
}

void rotacaoRL(NO** raiz) {
    rotacaoLL(&(*raiz)->dir);
    rotacaoRR(raiz);
}

bool AVL_no_inserir(NO** raiz, int chave) {
    int resultado;
    if (*raiz == NULL) { 
        NO* novo = (NO*)malloc(sizeof(NO));
        if (novo == NULL)
            return 0;

        novo->chave = chave;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    NO* atual = *raiz;
    if (chave < atual->chave) {
        resultado = AVL_no_inserir(&(atual->esq), chave);
        if (resultado == 1) {
            if (fator_de_balanceamento(atual) >= 2) {
                if (chave < atual->esq->chave)
                    rotacaoLL(raiz);
                else
                    rotacaoLR(raiz);
            }
        }
    } else if (chave > atual->chave) {
        resultado = AVL_no_inserir(&(atual->dir), chave);
        if (resultado == 1) {
            if (fator_de_balanceamento(atual) <= -2) {
                if (chave > atual->dir->chave)
                    rotacaoRR(raiz);
                else
                    rotacaoRL(raiz);
            }
        }
    } else {
        printf("Chave duplicada!\n");
        return false;
    }

    atual->alt = max(no_altura(atual->esq),no_altura(atual->dir)) + 1;
    return resultado;
}

bool AVL_inserir(AVL* avl, int chave) {
    if (avl == NULL) {
        return false;
    }
    int resultado = AVL_no_inserir(&(avl->raiz), chave);
    avl->profundidade = AVL_altura(avl);
    return resultado;
}


NO* AVL_procura_menor_no(NO* atual) {
    NO* anterior = atual;
    NO* sucessor = atual->esq;
    while (sucessor != NULL) {
        anterior = sucessor;
        sucessor = sucessor->esq;
    }
    return anterior;
}

bool AVL_no_remover(NO** raiz, int chave) {
    if (*raiz == NULL) { // Valor não encontrado
        printf("Chave não encontrada!\n");
        return false;
    }

    int resultado;
    if (chave < (*raiz)->chave) {
        resultado = AVL_no_remover(&(*raiz)->esq, chave);
        if (resultado == 1) {
            if (fator_de_balanceamento(*raiz) <= -2) { 
                NO* dir = (*raiz)->dir;
                if (fator_de_balanceamento(dir) <= 0)
                    rotacaoLL(raiz); 
                else
                    rotacaoLR(raiz); 
            }
        }
    } else if (chave > (*raiz)->chave) {
        resultado = AVL_no_remover(&(*raiz)->dir, chave);
        if (resultado == 1) {
            if (fator_de_balanceamento(*raiz) >= 2) { 
                NO* esq = (*raiz)->esq;
                if (fator_de_balanceamento(esq) >= 0)
                    rotacaoRR(raiz); 
                else
                    rotacaoRL(raiz); 
            }
        }
    } else { // Encontrou o nó a ser removido
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) { // Nó com 1 ou nenhum filho
            NO* temp = *raiz;
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(temp);
        } else { // Nó com 2 filhos
            NO* temp = AVL_procura_menor_no((*raiz)->dir);
            (*raiz)->chave = temp->chave;
            AVL_no_remover(&(*raiz)->dir, temp->chave);
            if (fator_de_balanceamento(*raiz) >= 2) { 
                NO* esq = (*raiz)->esq;
                if (fator_de_balanceamento(esq) >= 0)
                    rotacaoLL(raiz); 
                else
                    rotacaoLR(raiz); 
            }
        }
    }

    if (*raiz != NULL) {
        (*raiz)->alt = max(no_altura((*raiz)->esq), no_altura((*raiz)->dir)) + 1;
    }
    return true;
}

bool AVL_remover(AVL* avl, int chave) {
    if (avl == NULL)
        return 0;
    int resultado = AVL_no_remover(&(avl->raiz), chave);
    avl->profundidade = AVL_altura(avl);
    return resultado;
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
