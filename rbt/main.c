#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LLRBT.h"

int main() {
    
    RBT *tree = RBT_criar();
    RBT_inserir(tree, 6);
    RBT_inserir(tree, 1);
    RBT_inserir(tree, -9);
    RBT_inserir(tree, 4);
    RBT_inserir(tree, 8);
    RBT_inserir(tree, 2);

    percurso_em_ordem(tree);

    printf("%d ", RBT_remover(tree, 1));
    printf("%d ", RBT_remover(tree, 0));
    printf("%d ", RBT_remover(tree, 4));
    printf("%d ", RBT_remover(tree, 8));



    RBT_inserir(tree, 30);
    RBT_remover(tree, 1);
    RBT_inserir(tree, -11);
    RBT_remover(tree, 4);
    RBT_inserir(tree, 20);
    RBT_remover(tree, 6);

    percurso_em_ordem(tree);

    return 0;

}