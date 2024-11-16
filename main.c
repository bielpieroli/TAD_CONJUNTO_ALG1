#include <stdio.h>
#include <stdlib.h>
#include "arvoreAVL.h"
#include "lista.h"
#include "set.h"


int main() {
    // Vamos supor que o usuário escolhe a implementação com lista
    int escolha = 0;  

    // Criação do conjunto
    SET *conjunto = criar_set(escolha);
    if (conjunto == NULL) {
        printf("Erro ao criar o conjunto\n");
        return 1;
    }

    // Inserir elementos no conjunto
    inserir_set(conjunto, 10);
    inserir_set(conjunto, 20);
    inserir_set(conjunto, 30);

    // Verificar se um elemento pertence ao conjunto
    if (pertence_set(conjunto, 20)) {
        printf("20 pertence ao conjunto\n");
    } else {
        printf("20 não pertence ao conjunto\n");
    }

    // Remover um elemento do conjunto
    remover_set(conjunto, 10);

    // Imprimir elementos do conjunto
    imprimir_set(conjunto);

    // Apagar o conjunto e liberar memória
    destruir_set(conjunto);

    return 0;
}