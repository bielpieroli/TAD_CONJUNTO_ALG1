#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    SET *A, *B;
    int n_a, n_b, x;
    int op;
    int tipo;

    scanf("%d", &tipo); /*0 -> ED1 (AVL), 1 -> ED2 (Rubro-Negra)*/

    A = set_criar(tipo);
    B = set_criar(tipo);

    scanf("%d %d", &n_a, &n_b);

    // São inseridos os elementos em A
    for (int i = 0; i < n_a; i++)
    {
        scanf("%d", &x);
        set_inserir(A, x);
        set_imprimir(A);
    }
    // São inseridos os elementos em B
    for (int i = 0; i < n_b; i++)
    {
        scanf("%d", &x);
        set_inserir(B, x);
        set_imprimir(B);
    }

    // Escolha da operação
    scanf("%d", &op);
    switch (op) {
        case 1: // PERTERCE
        {
            set_imprimir(A);
            scanf("%d", &x);
            set_pertence(A,x) ? printf("Pertence.\n") : printf("Não pertence.\n");
            break;
        }
        case 2: // UNIÃO
        {
            set_imprimir(A);
            set_imprimir(B);
            SET *C = set_uniao(A, B);
            set_imprimir(C);
            set_apagar(&C);
            break;
        }
        case 3: // INTERSEÇÃO
        {
            set_imprimir(A);
            set_imprimir(B);
            SET *C = set_intersecao(A, B);
            set_imprimir(C);
            set_apagar(&C);
            break;
        }
        case 4: // REMOVER
        {
            set_imprimir(A);
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