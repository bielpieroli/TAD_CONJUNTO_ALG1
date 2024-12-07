#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "LLRBT.h"

typedef struct node_{
    int cor;    //0=preto, 1=vermelho
    int valor;
    struct node_ *esq, *dir;
}NODE; 

struct red_black_tree{
    NODE *raiz;
    int tam;

};

RBT *RBT_criar(){
    RBT *rbt = (RBT*)malloc(sizeof(RBT));
    if(!rbt) return NULL;

    rbt->raiz = NULL;
    rbt->tam = 0;
    return rbt;
}

NODE *criar_node(int valor){
    NODE *novo_node= (NODE*)malloc(sizeof(NODE));
    if(!novo_node) return NULL;
    novo_node->valor = valor;
    novo_node->dir = NULL;
    novo_node->esq = NULL;
    novo_node->cor = 1;
}

int vermelho(NODE *h){
    if(h==NULL){
        return NULL;
    }
    return (h->cor == 1);
}

void inverte(NODE *no){
    if(!no) return;
    no->cor = !no->cor;
    if(no->dir)
        no->dir->cor = !no->dir->cor;
    if(no->esq)
        no->esq->cor = !no->esq->cor;
}

NODE *rotacao_direita(NODE *c){
    if(!c) return NULL;

    NODE *b = c->esq;
    c->esq = b->dir;
    b->dir = c;
    b->cor = c->cor;
    c->cor = 1;
    return b;
}

NODE *rotacao_esquerda(NODE *a){
    if(!a) return NULL;

    NODE *b = a->dir;
    b->cor = a->cor;
    a->cor = 1;
    a->dir = b->esq;
    b->esq = a;
    return b;
}

NODE *inserir_node(NODE *h, int valor){
    //busca do local a ser inserido
    if(!h) return criar_node(valor);
    if(valor < h->valor) return inserir_node(h->esq, valor);
    else if(valor > h->valor) return inserir_node(h->dir, valor);

    //correção das regras quebradas
    if(!vermelho(h->esq) && vermelho (h->dir)){
        h = rotacao_esquerda(h);
    }
    if(vermelho(h->esq) && vermelho (h->esq->esq)){
        h = rotacao_direita(h);
    }
    if(vermelho(h->esq) && vermelho (h->dir)){
        inverte(h);
    }

    return h;
}

bool *RBT_inserir(RBT *tree, int item){
    if(!tree) return false;


}