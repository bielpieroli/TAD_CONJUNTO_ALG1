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

// Aloca e retorna um ponteiro para RBT caso haja memória, caso contrário retona NULL 
RBT *RBT_criar(){
    RBT *rbt = (RBT*)malloc(sizeof(RBT));
    if(!rbt) return NULL;

    //inicialização dos valores
    rbt->raiz = NULL;
    rbt->tam = 0;
    return rbt;
}

// Liberação de memória em um percurso pós-ordem
void apagar_recursivo(NODE *no){
    
    if(no== NULL) return;
    apagar_recursivo(no->esq);
    apagar_recursivo(no->dir);

    free(no);
}

// Libera toda a memoria da estrutura, retorna true se conseguir
bool RBT_apagar(RBT **tree){
    if(!tree || !(*tree)) return false;
    apagar_recursivo((*tree)->raiz);
    free(*tree);
    *tree = NULL;

    return true;
}

// Aloca e retorna um ponteiro para o NODE criado, caso haja memória, caso contrário retona NULL 
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

// ABAIXO ESTÃO FUNÇÕES AUXILIARES PARA BALANCEAR A ÁRVORE:

// Retorna 1 se vermelho e 0 se preto
int vermelho(NODE *h){
    // Nós nulos são pretos
    if(h==NULL){   
        return 0;
    }
    return (h->cor == 1);
}


// Inverte as cores do nó atual, e dos dois filhos
void inverte(NODE *no){
    if(!no) return;
    no->cor = !no->cor;
    if(no->dir)
        no->dir->cor = !no->dir->cor;
    if(no->esq)
        no->esq->cor = !no->esq->cor;
}

// Função que realiza a rotação direita
NODE *rotacao_direita(NODE *c){
    if(!c) return NULL;

    // Balanceamento na posição dos nós
    NODE *b = c->esq;
    c->esq = b->dir;
    b->dir = c;

    // Propagação das cores
    b->cor = c->cor;
    c->cor = 1;
    return b;
}

// Função que realiza a rotação esquerda
NODE *rotacao_esquerda(NODE *a){
    if(!a) return NULL;

    // Balanceamento
    NODE *b = a->dir;
    b->cor = a->cor;
    a->cor = 1;

    // Propagação das cores
    a->dir = b->esq;
    b->esq = a;
    return b;
}

// Recursão auxiliar para inserir nó na árvore
NODE *inserir_node(NODE *h, int valor, bool *inserido) {
    // Busca do local a ser inserido
    if (!h) {
        // Nó foi realmente inserido
        *inserido = true; 
        return criar_node(valor);
    }

    // Percorre buscando a posição de inserção recursivamente
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
        // Incrementa o tamanho apenas se algo foi inserido
        tree->tam++;          
        // A raiz da árvore sempre é preta
        tree->raiz->cor = 0;  
    }

    return inserido;
}

// Recursão auxiliar para o percurso
void percurso_em_ordem_aux(NODE *no){
    if(!no) return;
    percurso_em_ordem_aux(no->esq);
    printf("%d ", no->valor);
    percurso_em_ordem_aux(no->dir);
}

// Faz um percurso em ordem e printa seus elementos
void RBT_imprimir(RBT *tree){
    if(!tree) return;
    percurso_em_ordem_aux(tree->raiz);
    printf("\n");
}

// Recursão auxiliar para busca binária na árvore Rubro-Negra
bool RBT_busca_aux(NODE *no, int dado){
    if(!no) return false;
    // Busca binária recursiva
    if(no->valor > dado) return RBT_busca_aux(no->esq, dado);
    else if(no->valor < dado) return RBT_busca_aux(no->dir, dado);
    else return true;
}

// Busca um elemento na RBT e retorna true caso tenha achado
bool RBT_busca(RBT *tree, int dado){
    if(!tree) return false; 
    return RBT_busca_aux(tree->raiz, dado);
}

// Propagação da aresta vermelha quando se está atravessando a árvore pela esquerda
NODE *move_red_left(NODE *no) {
    inverte(no);
    if (vermelho(no->dir->esq)) {
        no->dir = rotacao_direita(no->dir);
        no = rotacao_esquerda(no);
        inverte(no);
    }
    return no;
}

// Propagação da aresta vermelha quando se está atravessando a árvore pela direita
NODE *move_red_right(NODE *no) {
    inverte(no);
    if (vermelho(no->esq->esq)) {
        no = rotacao_direita(no);
        inverte(no);
    }
    return no;
}

// Essa função adequa a árvore às regras da RBT no após uma remoção
NODE *balancear(NODE *no) {
    if (vermelho(no->dir)) no = rotacao_esquerda(no);
    if (vermelho(no->esq) && vermelho(no->esq->esq)) no = rotacao_direita(no);
    if (vermelho(no->esq) && vermelho(no->dir)) inverte(no);
    return no;
}

// Retorna o menor elemento de uma subárvore
NODE *encontrar_min(NODE *no) {
    while (no->esq) no = no->esq;
    return no;
}

// Remove o menor elemento da subárvore, para auxiliar na remoção em RBT
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

// Função de remoção recursiva via nós
NODE *RBT_remover_aux(NODE *no, int chave, bool *removido){
    if(!no) return NULL;

    // Busca da subarvore correta
    if(chave < no->valor){
        if(no->esq && !vermelho(no->esq) && !vermelho(no->esq->esq)) {
            // Para garantir a propriedade das cores
            no = move_red_left(no);
        }
        no->esq = RBT_remover_aux(no->esq, chave, removido);
    }
    else {
        if (vermelho(no->esq)) {
            no = rotacao_direita(no);
        }
        // Encontrou o item
        if (chave == no->valor) {
            *removido = true; 
            // Caso em que é folha
            if (!no->dir) { 
                free(no);
                return NULL;
            }
            // Caso contrário, substituir pelo menor da direita
            NODE *min = encontrar_min(no->dir);
            no->valor = min->valor;
            no->dir = remover_min(no->dir);
        } else {
            // Garantindo a propriedade rubro-negra
            if (no->dir && !vermelho(no->dir) && !vermelho(no->dir->esq)) {
                no = move_red_right(no); 
            }
            no->dir = RBT_remover_aux(no->dir, chave, removido);
        }
    }

    // A volta da recursão vai balanceando a árvore
    return balancear(no);
}

// Retorna true caso consiga remover o elemento da árvore
bool RBT_remover(RBT *tree, int chave) {
    if (!tree || !tree->raiz) return false;

    bool removido = false;

    // Chamada da recursao
    tree->raiz = RBT_remover_aux(tree->raiz, chave, &removido);

    if (tree->raiz) {
        // A raiz sempre é da cor preta
        tree->raiz->cor = 0; 
    }

    return removido;
}

// Percorre recursivamente a árvore para adicionar todos os nós na nova árvore
void RBT_uniao_aux(NODE *no, RBT *nova_arvore) {
    if (!no) return;

    // Inserindo o nó atual na nova árvore
    RBT_inserir(nova_arvore, no->valor);

    RBT_uniao_aux(no->esq, nova_arvore);
    RBT_uniao_aux(no->dir, nova_arvore);
}

// Função que efetua a união entre os conteúdos de duas dadas RBT
RBT *RBT_uniao(RBT *A, RBT *B) {
    // Árvores nulas
    if (!A && !B) return NULL; 

    //  Criamos uma nova RBT para armazenar a união
    RBT *nova_arvore = RBT_criar();
    if(!nova_arvore) return NULL;

    //  Percorremos as duas árvores e inserimos os elementos
    if (A && A->raiz) {
        RBT_uniao_aux(A->raiz, nova_arvore);
    }
    if (B && B->raiz) {
        RBT_uniao_aux(B->raiz, nova_arvore);
    }

    return nova_arvore;
}

// Função auxiliar que percorre a árvore em ordem adicionando à nova árvore
void RBT_intersec_aux(NODE *no, RBT *B, RBT *nova_arvore) {
    if (!no) return;

    //Percurso em ordem pela arvore
    RBT_intersec_aux(no->esq, B, nova_arvore);

    // Verificamos se o elemento está presente na árvore B para inserir na nova arvore
    if (RBT_busca(B, no->valor)) {
        RBT_inserir(nova_arvore, no->valor); 
    }

    RBT_intersec_aux(no->dir, B, nova_arvore);
}

// Retorna a intersecção entre os elementos de 2 árvores
RBT *RBT_intersecao(RBT *A, RBT *B) {
    // Se uma das árvores é nula, a interseção é nula
    if (!A || !B) return NULL; 

    // Criamos uma nova RBT para armazenar a intersecção
    RBT *nova_arvore = RBT_criar();
    if(!nova_arvore) return NULL;

    // Percorremos a árvore A e verificamos se os elementos estão em B
    RBT_intersec_aux(A->raiz, B, nova_arvore);

    return nova_arvore;
}
