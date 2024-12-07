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
    return novo_node;
}

int vermelho(NODE *h){
    if(h==NULL){
        return 0;
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
    if(valor < h->valor) 
        h->esq = inserir_node(h->esq, valor);
    else if(valor > h->valor) 
        h->dir = inserir_node(h->dir, valor);

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

bool RBT_inserir(RBT *tree, int dado){
    if(!tree) return false;
    NODE* no = inserir_node(tree->raiz, dado);
    tree->tam++;
    tree->raiz = no;
    tree->raiz->cor = 0; //a raiz da arvore sempre é preta
    return true;
}

void percurso_em_ordem_aux(NODE *no){
    if(!no) return;
    percurso_em_ordem_aux(no->esq);
    printf("%d ", no->valor);
    percurso_em_ordem_aux(no->dir);
}

void percurso_em_ordem(RBT *tree){
    if(!tree) return;
    printf("Percurso: ");
    percurso_em_ordem_aux(tree->raiz);
    printf("\n");
}

bool RBT_busca_aux(NODE *no, int dado){
    if(!no) return false;
    if(no->valor == dado) return true;
    return (RBT_busca_aux(no->esq, dado) || RBT_busca_aux(no->dir, dado));
}

bool RBT_busca(RBT *tree, int dado){
    if(!tree) return false;
    return RBT_busca_aux(tree->raiz, dado);
}

NODE *move_red_left(NODE *no) {
    inverte(no);
    if (vermelho(no->dir->esq)) {
        no->dir = rotacao_direita(no->dir);
        no = rotacao_esquerda(no);
        inverte(no);
    }
    return no;
}

NODE *move_red_right(NODE *no) {
    inverte(no);
    if (vermelho(no->esq->esq)) {
        no = rotacao_direita(no);
        inverte(no);
    }
    return no;
}

NODE *RBT_remover_aux(NODE *no, int chave){
    if(!no) return NULL;

    //busca da subarvore correta
    if(chave < no->valor){
        if(no->esq && vermelho(no->esq) && !vermelho(no->esq->esq)) {
            //mover vvermelho a direita
        }
    }
}

bool RBT_remover(RBT *tree, int chave) {
    if (!tree || !tree->raiz) return false;

    //chamada da recursao
    tree->raiz = RBT_remover_aux(tree->raiz, chave);

    if (tree->raiz) {
        tree->raiz->cor = 0; // a raiz sempre eh da cor preta
    }

    return true;
}