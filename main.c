#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    SET *A, *B;
    int n_a, n_b, x;
    int op;
    int tipo;

    scanf("%d", &tipo); /*0 -> ED1, 1 -> ED2*/

    A = set_criar(tipo);
    B = set_criar(tipo);

    scanf("%d %d", &n_a, &n_b);

    for (int i = 0; i < n_a; i++)
    {
        scanf("%d", &x);
        set_inserir(A, x);
    }

    for (int i = 0; i < n_b; i++)
    {
        scanf("%d", &x);
        set_inserir(B, x);
    }

    scanf("%d", &op);
    switch (op) {
        case 1:
        {
            scanf("%d", &x);
            set_pertence(A,x) ? printf("Pertence.\n") : printf("Não pertence.\n");
            break;
        }
        case 2:
        {
            SET *C = set_uniao(A, B);
            set_imprimir(C);
            set_apagar(&C);
            break;
        }
        case 3:
        {
            SET *C = set_intersecao(A, B);
            set_imprimir(C);
            set_apagar(&C);
            break;
        }
        case 4:
        {
            scanf("%d", &x);
            set_remover(A, x);
            set_imprimir(A);
        }
    }
    set_apagar(&A);
    set_apagar(&B);
    return 0;
}