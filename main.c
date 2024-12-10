#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    SET *A, *B;
    int n_a, n_b, x;
    int op;
    int tipo;

    scanf("%d", &tipo); /*0 -> ED1 (AVL), 1 -> ED2 (LLRBT)*/

    A = set_criar(tipo);
    B = set_criar(tipo);

    scanf("%d %d", &n_a, &n_b);

    // São inseridos os elementos em A
    for (int i = 0; i < n_a; i++)
    {
        scanf("%d", &x);
        set_inserir(A, x);
    }
    // São inseridos os elementos em B
    for (int i = 0; i < n_b; i++)
    {
        scanf("%d", &x);
        set_inserir(B, x);
    }

    // Escolha da operação
    scanf("%d", &op);
    switch (op) {
        case 1: // PERTERCE
        {
            scanf("%d", &x);
            set_pertence(A,x) ? printf("Pertence.\n") : printf("Não pertence.\n");
            break;
        }
        case 2: // UNIÃO
        {
            SET *C = set_uniao(A, B);
            set_imprimir(C);
            set_apagar(&C);
            break;
        }
        case 3: // INTERSEÇÃO
        {
            SET *C = set_intersecao(A, B);
            set_imprimir(C);
            set_apagar(&C);
            break;
        }
        case 4: // REMOVER
        {
            scanf("%d", &x);
            set_remover(A, x);
            set_imprimir(A);
        }
    }
    // Desaloca os conjuntos alocadas
    set_apagar(&A);
    set_apagar(&B);
    return 0;
}