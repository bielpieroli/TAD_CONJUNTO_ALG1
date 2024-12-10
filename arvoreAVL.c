#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvoreAVL.h"
/*
struct NO_, pelo typedef se torna NO, é formada por 4 campos:
int chave: o valor armazenado dentro de cada nó
int alt: a altura de cada nó na árvore
NO *esq: ponteiro para o nó à esquerda na árvore
NO *dir: ponteiro para o nó à direita na árvore
*/
struct NO_{
    int chave;
    int alt;
    NO *esq;
    NO *dir;
};
/*
struct ARVORE_AVL, pelo typedef se torna AVL, é formada por 2 campos:
int profundidade: armazena a distância da raiz ao nó folha mais distante
NO *raiz: o ponteiro para a raiz da estrutura de árvore AVL
*/
struct ARVORE_AVL{
    int profundidade;
    NO *raiz;
};


/// @brief Função que cria a estrutura de árvore, alocando a sua memória dinamicamente
/// @return AVL *, isto é, a estrutura da árvore ao cliente
AVL* AVL_criar() {
    // Alocação dinâmica dastruct auxiliar AVL
    AVL* T = (AVL*)malloc(sizeof(AVL));
    // Em caso de sucesso na alocação, inicialização de seus campos
    if (T != NULL) {
        T->profundidade = -1;
        T->raiz = NULL;
    }
    return T;
}

/// @brief Função auxiliar que realiza a liberação de cada um dos nós da árvore AVL, recursivamente
/// @param raiz 
void no_liberar(NO** raiz) {
    if (*raiz != NULL) {
        // Liberação recursiva dos nós à esquerda de aum dado nó
        no_liberar(&(*raiz)->esq);
        // Liberação recursiva dos nós à direita de um dado nó
        no_liberar(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }
}
/// @brief Função que desaloca toda a memória alocada dinamicamente para a estrutura de árvore AVL
/// @param T 
void AVL_apagar(AVL** T) {
    if (*T == NULL)
        return;
    // Libera a memória alocada para os nós da árvore
    no_liberar(&((*T)->raiz));
    // Libera a memória da struct auxiliar AVL
    free(*T);
    T = NULL;
}

/// @brief Função auxiliar que lida com a altura de um dado nó
/// @param no 
/// @return int, isto é, o valor referente à altura do nó dentro da estrutura de árvore AVL
int no_altura(NO* no) {
    // Quando o nó é nulo, retorna-se -1 para efetuar as operações de balanceamento posteriores
    if (no == NULL) {
        return -1;
    }
    return no->alt;
}

/// @brief Função auxiliar que verifica qual valor é maior, retornando-o
/// @param x 
/// @param y 
/// @return x, se x > y, senão, y
int max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    } 
}

/// @brief Função auxiliar que realiza a operação do fator de balanceamento de cada nó, essecial para as rotações
/// @param no 
/// @return int, ou seja, o fator de balanceamento do nó recebido como parâmetro
int fator_de_balanceamento(NO* no) {
    // Utilizando a função auxiliar de retornar a altura de cada nó, à direita e à esquerda
    return (no_altura(no->esq) - no_altura(no->dir));
}

/*
/// @brief Função que verifica se a estrutura AVL não é vazia
/// @param avl 
/// @return true: se a estrutura AVL ou a raiz NO é nula. false: caso contrário.
bool AVL_vazia(AVL* avl) {
    if(avl == NULL || avl->raiz == NULL) {
        return true;
    }
    return false;
}

/// @brief Função auxiliar que retorna a quantidade de elementos da árvore AVL, contando os nós recursivamente
/// @param no 
/// @return int, isto é, a quantia total de nós encontrados
int AVL_total_nos(NO* no) {
    if (no == NULL) {
        return 0;
    }
    // A cada chamada recursiva, incrementa-se em 1esse valor, contabilizando a existência daquele nó
    return (AVL_total_nos(no->esq) + AVL_total_nos(no->dir) + 1);
}

/// @brief Função que retorna ao usuário quantos nós há em uma árvore recebida como parâmetro
/// @param T 
/// @return int, ou seja, o valor encontrado pela função recursiva contadora de nós, ou caso a estrutura seja nula, retorna 0
int AVL_total(AVL *T) {
    if (T != NULL) {
        return (AVL_total_nos(T->raiz));
    }
    return 0;
}
*/

/// @brief Função auxiliar que verifica a altura do nó raiz, indicando a profundidade da AVL
/// @param avl 
/// @return int, isto é, a distância entre o nó raiz ao nó-folha mais distante
int AVL_altura(AVL* avl) {
    if (avl == NULL || avl->raiz == NULL)
        return 0;
    return avl->raiz->alt;
}


/*
/// @brief Percurso dos nós da árvore em pré-ordem: 1) Visita 2) Pecorre recursivamente à esquerda 3) Percorre recursivamente à direita
/// @param no 
void no_pre_ordem(NO* no) {
    if (no == NULL)
        return;
    printf("Nó %d: Altura(%d)\n", no->chave, no->alt);
    no_pre_ordem(no->esq);
    no_pre_ordem(no->dir);
}
/// @brief A árvore AVL será percorrida em pré-ordem
/// @param avl 
void AVL_pre_ordem(AVL* avl) {
    if (avl != NULL)
        no_pre_ordem(avl->raiz);
}
*/

/// @brief Percurso dos nós da árvore em ordem: 1) Pecorre recursivamente à esquerda 2) Visita 3) Percorre recursivamente à direita
/// @param no 
void no_em_ordem(NO* no) {
    if (no == NULL)
        return;
    no_em_ordem(no->esq);
    //printf("Nó %d: Altura(%d), Fator de Balanceamento(%d)\n", no->chave, no->alt, fator_de_balanceamento(no));
    printf("%d ", no->chave);
    no_em_ordem(no->dir);
}

/// @brief A árvore AVL será percorrida em ordem
/// @param avl 
void AVL_imprimir(AVL* avl) {
    if (avl != NULL) {
        no_em_ordem(avl->raiz);
        printf("\n");
    }
}

/*
/// @brief Percurso dos nós da árvore em pós-ordem: 1) Pecorre recursivamente à esquerda 2) Percorre recursivamente à direita 3) Visita
/// @param no 
void no_pos_ordem(NO* no) {
    if (no == NULL)
        return;
    no_pos_ordem(no->esq);
    no_pos_ordem(no->dir);
    printf("%d\n", no->chave);
}

/// @brief A árvore AVL será percorrida em pós-ordem
/// @param avl 
void AVL_pos_ordem(AVL* avl) {
    if (avl != NULL)
        no_pos_ordem(avl->raiz);
}
*/

/// @brief Função que realiza a Rotação Esquerda
/// @param A 
/// @return Retorna a sub-árvore rotacionada à esquerda
NO *rotacaoL(NO* A) {
    // Para que haja rotação à esquerda, A e B(filho direito de A) não podem ser nulos
    if (A == NULL) {
        printf("Erro: A é nulo\n");
        return NULL; 
    }
    NO* B = A->dir;
    if (B == NULL) {
        printf("Erro: B é nulo\n");
        return NULL; 
    }
    // Os dois ponteiros são ajustados
    A->dir = B->esq;
    B->esq = A;
    // As alturas são recalculadas
    A->alt = max(no_altura(A->esq), no_altura(A->dir)) + 1;
    B->alt = max(no_altura(A), no_altura(B->dir)) + 1;
    // B se torna a raiz da sub-árvore pós rotação
    return B;
}

/// @brief Função que realiza a Rotação Direita
/// @param A 
/// @return Retorna a sub-árvore rotacionada à direita
NO *rotacaoR(NO* A) {
    // Para que haja rotação à direita, A e B(filho esquerdo de A) não podem ser nulos
    if (A == NULL) {
        printf("Erro: A é nulo\n");
        return NULL; 
    }
    NO* B = A->esq;
    if (B == NULL) {
        printf("Erro: B é nulo\n");
        return NULL; 
    }
    // Os dois ponteiros são ajustados
    A->esq = B->dir;
    B->dir = A;
     // As alturas são recalculadas
    A->alt = max(no_altura(A->esq), no_altura(A->dir)) + 1;
    B->alt = max(no_altura(B->esq), no_altura(A)) + 1;
    // B se torna a raiz da sub-árvore pós rotação
    return B;
}

/// @brief Função que realiza a Rotação Dupla para árvores pendendo à esquerda
/// @param A 
/// @return A sub-árvore rotacionada e com as alturas atualizadas
NO *rotacaoLR(NO* A) {
    // Rotaciona-se o filho esquerdo da raiz à esquerda
    A->esq = rotacaoL(A->esq);
    // Rotaciona-se a partir da raiz à direita
    return rotacaoR(A);
}

/// @brief Função que realiza a Rotação Dupla para árvores pendendo à direita
/// @param A 
/// @return A sub-árvore rotacionada e com as alturas atualizadas
NO *rotacaoRL(NO* A) {
    // Rotaciona-se o filho direita da raiz à direita
    A->dir = rotacaoR(A->dir);
    // Rotaciona-se a partir da raiz à esquerda
    return rotacaoL(A);
}

/// @brief Função auxiliar que cria um nó, alocando-o dinamicamente e inicializando os seus campos
/// @param chave 
/// @return NO *, ou seja, o nó novo criado
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

/// @brief Função que realiza a inserção, criando um nó, de uma nova chave dentro da árvore AVL, recursivamente, na sua posição devida para continuar uma ABB
/// @param raiz 
/// @param chave 
/// @return NO *, isto é, a raiz e, consequentemente, toda a AVL já feita a inserção
NO *AVL_no_inserir(NO* raiz, int chave) {
    // Percurso pela árvore AVL
    if (raiz == NULL) { 
        raiz = no_criar(chave);
    } else if (chave < raiz->chave) {
        raiz->esq = AVL_no_inserir(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = AVL_no_inserir(raiz->dir, chave);
    }
    // Na volta da recusão são feitos ajustes:
    // A altura de cada nó é atualizada
    raiz->alt = max(no_altura(raiz->esq),no_altura(raiz->dir)) + 1;
    // Para este caso do fator de balanceamento, a árvore pende à direita, necessita-se de uma rotação à esquerda
    if (fator_de_balanceamento(raiz) <= -2) {
        // Caso o fator de balanceamento do filho à direita seja de igual sinal ou nulo, faz-se rotação simples à esquerda
        if (fator_de_balanceamento(raiz->dir) <= 0)
            raiz = rotacaoL(raiz);
        // Do contrário, faz-se rotação dupla, à direita e, por fim, à esquerda
        else
            raiz = rotacaoRL(raiz);
    }
    // Para este caso do fator de balanceamento, a árvore pende à esquerda, necessita-se de uma rotação à direita
    if (fator_de_balanceamento(raiz) >= 2) {
        // Caso o fator de balanceamento do filho à esquerda seja de igual sinal ou nulo, faz-se rotação simples à direita
        if (fator_de_balanceamento(raiz->esq) >= 0)
            raiz = rotacaoR(raiz);
        else
         // Do contrário, faz-se rotação dupla, à esquerda e, por fim, à direita
            raiz = rotacaoLR(raiz);
    }
    // Feito tudo isso, recursivamente, retorna-se eventualmente a raiz com todos os ajustes feitos
    return raiz;
}

/// @brief Função que realiza a inserção de uma chave em um nó da árvore AVL
/// @param avl 
/// @param chave 
/// @return bool, ou seja, se foi possível ou não realizar a inserção daquela chave na árvore AVL
bool AVL_inserir(AVL* avl, int chave) {
    // Caso a estrutura AVL não exista, não é possível
    if (avl == NULL) {
        return false;
    }
    NO* pos_insercao = AVL_no_inserir(avl->raiz, chave);
    bool resultado = false;
    // Caso tenha sido bem sucedida, a raiz da estrutura auxiliar recebe a árvore pós inserção, atualiza a profundidade e retorna true
    if (pos_insercao != NULL) {
        avl->raiz = pos_insercao;
        avl->profundidade = AVL_altura(avl);
        resultado = true;
    }
    return resultado;
}

/// @brief Função auxiliar que realiza a troca de um nó pelo folha mais esquerda, vinda de seu filho direito.
/// @param troca 
/// @param raiz 
/// @param ant 
void AVL_troca_no_max_esq(NO* troca, NO *raiz, NO *ant) {
    // Recursivamente, encontra o nó-folha mais à esquerda do filho direito
    if(troca->dir != NULL) {
        AVL_troca_no_max_esq(troca->dir, raiz, troca);
        return;
    }
    // Faz-se ajustes nos ponteiros para 
    if (raiz == ant) {
        ant->esq = troca->esq;
    } else {
        ant->dir = troca->esq;
    }
    // Troca os valores das chaves e desaloca a memória 
    raiz->chave = troca->chave;
    free(troca);
    troca = NULL;
}

/// @brief Função auxiliar que percorre recursivamente a árvore em busca da chave que será removida
/// @param raiz 
/// @param chave 
/// @param existe 
/// @return NO *, isto é, retorna a raiz, após terminadas as chamadas recursivas e feita a remoção
NO *AVL_no_remover(NO** raiz, int chave, bool *existe) {
    // Valor não encontrado
    if (*raiz == NULL) { 
        *existe = false;
        return NULL;
    // Percorre a árvore à esquerda caso a chave seja menor que o chave do nó atual
    } else if (chave < (*raiz)->chave) {
        (*raiz)->esq = AVL_no_remover(&(*raiz)->esq, chave, existe);
    // Percorre a árvore à esquerda caso a chave seja menor que o chave do nó atual
    } else if (chave > (*raiz)->chave) {
        (*raiz)->dir = AVL_no_remover(&(*raiz)->dir, chave, existe);
    // Encontrou o nó a ser removido
    } else if (chave == (*raiz)->chave) { 
        NO *aux;
        // Nó com 1 ou nenhum filho
        if ((*raiz)->esq == NULL || (*raiz)->dir == NULL) { 
            aux = *raiz;
            if ((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
            free(aux);
            aux = NULL;
        // Nó com 2 filhos
        } else { 
            AVL_troca_no_max_esq((*raiz)->esq,(*raiz), (*raiz));
        }
    }
    // Na volta da recursão são feitos os ajustes:
    if (*raiz != NULL) {
        // A altura de cada nó é atualizada
        (*raiz)->alt = max(no_altura((*raiz)->esq), no_altura((*raiz)->dir)) + 1;
        // Para este caso do fator de balanceamento, a árvore pende à esquerda, necessita-se de uma rotação à direita
        if (fator_de_balanceamento(*raiz) >= 2) { 
            // Caso o fator de balanceamento do filho à esquerda seja de igual sinal ou nulo, faz-se rotação simples à direita
            if (fator_de_balanceamento((*raiz)->esq) >= 0)
                *raiz = rotacaoR(*raiz); 
            // Do contrário, faz-se rotação dupla, à esquerda e, por fim, à direita
            else
                *raiz = rotacaoLR(*raiz); 
        }
        // Para este caso do fator de balanceamento, a árvore pende à direita, necessita-se de uma rotação à esquerda
        if (fator_de_balanceamento(*raiz) <= -2) { 
            // Caso o fator de balanceamento do filho à direita seja de igual sinal ou nulo, faz-se rotação simples à esquerda
            if (fator_de_balanceamento((*raiz)->dir) <= 0)
                *raiz = rotacaoL(*raiz); 
             // Do contrário, faz-se rotação dupla, à direita e, por fim, à esquerda
            else
                *raiz = rotacaoRL(*raiz); 
        }
    }
    // Feito tudo isso, recursivamente, retorna-se eventualmente a raiz com a remoção e todos os ajustes feitos
    return *raiz;
}

/// @brief Função que realiza a remoção de uma chave em um nó da árvore AVL
/// @param avl 
/// @param chave 
/// @return bool, ou seja, se foi possível ou não realizar a remoção daquela chave na árvore AVL
bool AVL_remover(AVL* avl, int chave) {
    // Caso a estrutura AVL não exista, não é possível
    if (avl == NULL) {
        return false;
    }
    bool existe = true;
    NO* pos_remocao = AVL_no_remover(&(avl->raiz), chave, &existe);
    bool resultado;
    // Analisa caso a raiz retornada seja nula, indicando que a remoção não foi executada com sucesso
    if (pos_remocao == NULL || !existe) {
        resultado = false;
    // Caso tenha sido bem sucedida e o elemento existia na estrutura, a raiz antiga recebe a raiz pós inserção, atualiza a profundidade e retorna true
    } else {
        avl->raiz = pos_remocao;
        avl->profundidade = AVL_altura(avl);
        resultado = true;
    }
    return resultado;
}


/// @brief Função auxiliar que percorre os nós iterativamente em busca da chave desejada
/// @param no 
/// @param chave 
/// @return false: se a chave não existia. true: se a chave existia 
bool AVL_no_consulta(NO* no, int chave) {
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

/// @brief Função que verifica se uma dada chave existe dentro da AVL
/// @param avl 
/// @param chave 
/// @return false: se a chave não existia na estrutura. true: se a chave existia na estrutura
bool AVL_consulta(AVL* avl, int chave) {
    if (avl == NULL || avl->raiz == NULL)
        return false;
    return AVL_no_consulta(avl->raiz, chave);
}

NO* no_inserir_uniao(AVL *C, NO *elemento) {
    if(elemento != NULL) {
            if(!AVL_inserir(C, elemento->chave)) {
                printf("Erro na inserção do elemento %d", elemento->chave);
            }
        C->raiz = no_inserir_uniao(C, elemento->esq);
        C->raiz = no_inserir_uniao(C, elemento->dir);
    }
    return C->raiz;
}

/// @brief Função que constrói o conjunto união entre dois conjuntos A e B
/// @param A 
/// @param B 
/// @return AVL *, isto é, o conjunto C, fruto da união entre A e B
AVL *AVL_uniao(AVL *A, AVL *B) {
    AVL *C = AVL_criar();

    if(A != NULL && A->raiz != NULL) {
        C->raiz = no_inserir_uniao(C, A->raiz);
    }
    if(B != NULL && B->raiz != NULL) {
        C->raiz = no_inserir_uniao(C, B->raiz);
    }

    C->profundidade = AVL_altura(C);

    return C;
}

/// @brief Função auxiliar que percorre a árvore recursivamente e insere em C os elementos que pertencem tanto a A, quanto a B
/// @param C 
/// @param A 
/// @param elemento 
/// @return NO *, ou seja, retorna eventualmente a raiz 
NO* no_inserir_intersecao(AVL *C, AVL *A, NO *elemento) {
    if(elemento != NULL) {
        if(AVL_consulta(A, elemento->chave)) {
            if(!AVL_inserir(C, elemento->chave)) {
                printf("Erro na inserção do elemento %d", elemento->chave);
            }
        }
        C->raiz = no_inserir_intersecao(C, A, elemento->esq);
        C->raiz = no_inserir_intersecao(C, A, elemento->dir);
    }
    return C->raiz;
}

/// @brief Função que constrói o conjunto interseção entre dois dados conjuntos
/// @param A 
/// @param B 
/// @return AVL *, ou seja, retorna o conjunto C, interseção entre A e B
AVL *AVL_intersecao(AVL *A, AVL *B) {
    AVL *C = AVL_criar();

    if(A != NULL && A->raiz != NULL && B != NULL && B->raiz != NULL) {
        C->raiz = no_inserir_intersecao(C, A, B->raiz);
    }

    C->profundidade = AVL_altura(C);

    return C;
}

/*
/// @brief Função auxiliar que contabiliza os espaços por nível
/// @param nivel 
void print_espacos(int nivel) {
    for (int i = 0; i < nivel; i++) {
        printf("    "); 
    }
}

/// @brief Função auxiliar que printa a estrutura da árvore, com arestas e chaves.
/// @param raiz 
/// @param nivel 
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

/// @brief Função de debug para verificar como estava ficando a estrutura da árvore
/// @param T 
void print_arvore(AVL *T) {
    printf("Árvore AVL:\n");
    print_estrutura(T->raiz, 0);
}
*/