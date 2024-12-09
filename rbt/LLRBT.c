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

//aloca e retorna um ponteiro para RBT caso haja memória, caso contrário retona NULL 
RBT *RBT_criar(){
    RBT *rbt = (RBT*)malloc(sizeof(RBT));
    if(!rbt) return NULL;

    //inicialização dos valores
    rbt->raiz = NULL;
    rbt->tam = 0;
    return rbt;
}

void apagar_recursivo(NODE *no){
    //liberação de memória em um percurso pós-ordem
    if(no== NULL) return;

    apagar_recursivo(no->esq);
    apagar_recursivo(no->dir);

    free(no);
}

//libera toda a memoria da estrutura, retorna true se conseguir
bool RBT_apagar(RBT **tree){
    if(!tree || !(*tree)) return false;
    apagar_recursivo((*tree)->raiz);
    free(*tree);
    *tree = NULL;

    return true;
}

//aloca e retorna um ponteiro para NODE caso haja memória, caso contrário retona NULL 
NODE *criar_node(int valor){
    NODE *novo_node= (NODE*)malloc(sizeof(NODE));
    if(!novo_node) return NULL;

    //inicialização dos valores
    novo_node->valor = valor;
    novo_node->dir = NULL;
    novo_node->esq = NULL;
    novo_node->cor = 1;
    return novo_node;
}

//ABAIXO ESTÃO FUNÇÕES AUXILIARES PARA BALANCEAR A ÁRVORE

//retorna 1 se vermelho e 0 se preto
int vermelho(NODE *h){
    if(h==NULL){   //nós nulos são pretos
        return 0;
    }
    return (h->cor == 1);
}


//inverte as cores do nó atual, e dos dois filhos
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

    //balanceamento
    NODE *b = c->esq;
    c->esq = b->dir;
    b->dir = c;

    //propagação das cores
    b->cor = c->cor;
    c->cor = 1;
    return b;
}

NODE *rotacao_esquerda(NODE *a){
    if(!a) return NULL;

    //balanceamento
    NODE *b = a->dir;
    b->cor = a->cor;
    a->cor = 1;

    //propagação das cores
    a->dir = b->esq;
    b->esq = a;
    return b;
}

//recursão auxiliar para inserir nó na árvore
NODE *inserir_node(NODE *h, int valor, bool *inserido) {
    //busca do local a ser inserido
    if (!h) {
        *inserido = true; // nó foi realmente inserido
        return criar_node(valor);
    }

    if (valor < h->valor) {
        h->esq = inserir_node(h->esq, valor, inserido);
    } else if (valor > h->valor) {
        h->dir = inserir_node(h->dir, valor, inserido);
    } else {
        // Valor já existe, não fazemos nada
        *inserido = false;
        return h;
    }

    // Correção das regras quebradas da LLRBT
    if (!vermelho(h->esq) && vermelho(h->dir)) {
        h = rotacao_esquerda(h);
    }
    if (vermelho(h->esq) && vermelho(h->esq->esq)) {
        h = rotacao_direita(h);
    }
    if (vermelho(h->esq) && vermelho(h->dir)) {
        inverte(h);
    }

    return h;
}

// Retorna true caso consiga inserir um elemento na RBT, false caso contrário
bool RBT_inserir(RBT *tree, int dado) {
    if (!tree) return false;

    bool inserido = false;
    tree->raiz = inserir_node(tree->raiz, dado, &inserido);

    if (inserido) {
        tree->tam++;          //incrementa o tamanho apenas se algo foi inserido
        tree->raiz->cor = 0;  //a raiz da árvore sempre é preta
    }

    return inserido;
}

//recursão auxiliar para o percurso
void percurso_em_ordem_aux(NODE *no){
    if(!no) return;
    percurso_em_ordem_aux(no->esq);
    printf("%d ", no->valor);
    percurso_em_ordem_aux(no->dir);
}

//faz um percurso em ordem e printa seus elementos
void percurso_em_ordem(RBT *tree){
    if(!tree) return;
    printf("Percurso: ");
    percurso_em_ordem_aux(tree->raiz);
    printf("\n");
}

//recursão auxiliar para busca
bool RBT_busca_aux(NODE *no, int dado){
    if(!no) return false;
    if(no->valor == dado) return true;
    return (RBT_busca_aux(no->esq, dado) || RBT_busca_aux(no->dir, dado));
}

//busca um elemento na RBT e retorna true caso tenha achado
bool RBT_busca(RBT *tree, int dado){
    if(!tree) return false;
    return RBT_busca_aux(tree->raiz, dado);
}

//propagação da aresta vermelha quando se está atravessando a árvore pela esquerda
NODE *move_red_left(NODE *no) {
    inverte(no);
    if (vermelho(no->dir->esq)) {
        no->dir = rotacao_direita(no->dir);
        no = rotacao_esquerda(no);
        inverte(no);
    }
    return no;
}

//propagação da aresta vermelha quando se está atravessando a árvore pela direita
NODE *move_red_right(NODE *no) {
    inverte(no);
    if (vermelho(no->esq->esq)) {
        no = rotacao_direita(no);
        inverte(no);
    }
    return no;
}

//Essa função adequa a árvore às regras da RBT no após uma remoção
NODE *balancear(NODE *no) {
    if (vermelho(no->dir)) no = rotacao_esquerda(no);
    if (vermelho(no->esq) && vermelho(no->esq->esq)) no = rotacao_direita(no);
    if (vermelho(no->esq) && vermelho(no->dir)) inverte(no);
    return no;
}

//retorna o menor elemento de uma subárvore
NODE *encontrar_min(NODE *no) {
    while (no->esq) no = no->esq;
    return no;
}

//remove o menor elemento da subárvore, para auxiliar na remoção em RBT
NODE *remover_min(NODE *no) {
    if (!no->esq) {
        free(no);
        return NULL;
    }
    if (!vermelho(no->esq) && !vermelho(no->esq->esq)) {
        no = move_red_left(no);
    }
    no->esq = remover_min(no->esq);
    return balancear(no);
}

NODE *RBT_remover_aux(NODE *no, int chave, bool *removido){
    if(!no) return NULL;

    //busca da subarvore correta
    if(chave < no->valor){
        if(no->esq && !vermelho(no->esq) && !vermelho(no->esq->esq)) {
            //para garantir a propriedade das cores
            no = move_red_left(no);
        }
        no->esq = RBT_remover_aux(no->esq, chave, removido);
    }
    else {
        if (vermelho(no->esq)) {
            no = rotacao_direita(no);
        }
        //encontrou o item
        if (chave == no->valor) {
            *removido = true; 
            //caso em que é folha
            if (!no->dir) { 
                free(no);
                return NULL;
            }
            // caso contrário, substituir pelo menor da direita
            NODE *min = encontrar_min(no->dir);
            no->valor = min->valor;
            no->dir = remover_min(no->dir);
        } else {
            if (no->dir && !vermelho(no->dir) && !vermelho(no->dir->esq)) {
                no = move_red_right(no); //garantindo a propriedade rubro-negra
            }
            no->dir = RBT_remover_aux(no->dir, chave, removido);
        }
    }

    //a volta da recursão vai balanceando a árvore
    return balancear(no);
}

//retorna true caso consiga remover o elemento da árvore
bool RBT_remover(RBT *tree, int chave) {
    if (!tree || !tree->raiz) return false;

    bool removido = false;

    //chamada da recursao
    tree->raiz = RBT_remover_aux(tree->raiz, chave, &removido);

    if (tree->raiz) {
        tree->raiz->cor = 0; // a raiz sempre é da cor preta
    }

    return removido;
}

//percorre recursivamente a árvore para adicionar todos os nós na nova árvore
void RBT_uniao_aux(NODE *no, RBT *nova_arvore) {
    if (!no) return;

    //inserindo o nó atual na nova árvore
    RBT_inserir(nova_arvore, no->valor);

    RBT_uniao_aux(no->esq, nova_arvore);
    RBT_uniao_aux(no->dir, nova_arvore);
}

RBT *RBT_uniao(RBT *A, RBT *B) {
    if (!A || !B) return NULL; // Árvores nulas

    //criamos uma nova RBT para armazenar a união
    RBT *nova_arvore = RBT_criar();
    if(!nova_arvore) return NULL;

    //percorremos as duas árvores e inserimos os elementos
    if (A && A->raiz) {
        RBT_uniao_aux(A->raiz, nova_arvore);
    }
    if (B && B->raiz) {
        RBT_uniao_aux(B->raiz, nova_arvore);
    }

    return nova_arvore;
}

void RBT_intersec_aux(NODE *no, RBT *B, RBT *nova_arvore) {
    if (!no) return;

    //Percurso em ordem pela arvore

    RBT_intersec_aux(no->esq, B, nova_arvore);

    //verificamos se o elemento está presente na árvore B para inserir na nova arvore
    if (RBT_busca(B, no->valor)) {
        RBT_inserir(nova_arvore, no->valor); 
    }

    RBT_intersec_aux(no->dir, B, nova_arvore);
}

//Retorna a intersecção entre os elementos de 2 árvores
RBT *RBT_intersec(RBT *A, RBT *B) {
    if (!A || !B) return NULL; // Se uma das árvores é nula, a interseção é nula

    //criamos uma nova RBT para armazenar a intersecção
    RBT *nova_arvore = RBT_criar();
    if(!nova_arvore) return NULL;

    //percorremos a árvore A e verificamos se os elementos estão em B
    RBT_intersec_aux(A->raiz, B, nova_arvore);

    return nova_arvore;
}
