#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"


int main() {
    int escolha;
    scanf("%d", &escolha);  

    // Criação do set
    SET *conjunto = set_criar(escolha);
    if (conjunto == NULL) {
        printf("Erro ao criar o set\n");
        return 1;
    }


    set_inserir(conjunto, 10);
    set_inserir(conjunto, 20);
    set_inserir(conjunto, 30);
    set_inserir(conjunto, 40);

    set_imprimir(conjunto);


    if (set_pertence(conjunto, 20)) {
        printf("%d pertence ao set\n", 20);
    } else {
        printf("%d não pertence ao set\n", 20);
    }

    if (set_pertence(conjunto, 60)) {
        printf("%d pertence ao set\n", 60);
    } else {
        printf("%d não pertence ao set\n", 60);
    }

    if(set_remover(conjunto, 10)) {
        printf("%d foi removido\n", 10);
    } else {
        printf("%d não está no set\n", 10);
    }

    if(set_remover(conjunto, 50)) {
        printf("%d foi removido\n", 50);
    } else {
        printf("%d não está no set\n", 50);
    }
    // Imprimir elementos do set
    set_imprimir(conjunto);

    // Apagar o set e liberar memória
    set_apagar(&conjunto);

    return 0;
}