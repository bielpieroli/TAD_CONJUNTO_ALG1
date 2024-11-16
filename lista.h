#ifndef LISTA_H
    #define LISTA_H
    #define TAM_MAX 12
    #define ERRO -1
    #define INF 100000010
    #include <stdbool.h>

    /* ESTE É O TAD LISTA */

    /* TYPEDEF utilizado para representar o tipo 'struct lista_' apenas por 'LISTA' */
    typedef struct lista_ LISTA;

    /* A função "lista_criar", cujo retorno tem tipo LISTA *, tem o papel de criar a estrutura de uma lista, alocando a sua memória dinamicamente e
    inicializando os campos 'tamanho', 'inicio' e 'fim'como 0, além de definir conforme o parâmetro recebido 'ordenada', se ela será ou não ordenada */
    LISTA *lista_criar(bool ordenada);

    /* A função "lista_inserir", cujo retorno é do tipo booleano, é responsável por, a partir dos parâmetros recebidos (LISTA *lista: A LISTA
    EM QUE OCORRERÁ A INSERÇÃO, int *int: O int QUE SE DESEJA INSERIR), efetuar a inserção de um int.*/
    bool lista_inserir(LISTA *lista, int chave);

    /* A função "lista_remover", cujo retorno é do tipo int *, é responsável por, a partir dos parâmetros recebidos (LISTA 
    *lista: A LISTA EM QUE OCORRERÁ A REMOÇÃO, int pos: A POSIÇÃO DE QUE SE DESEJA REMOVER), efetuar, dada uma posição, 
    a remoção do int ali localizado. */
    int lista_remover(LISTA *lista, int pos);

    /* A função "lista_int", cujo retorno é do tipo int *, tem a função de retornar ao usuário o int da lista com uma
    determinada chave, recebida como parâmetro da função. */
    int lista_int(LISTA *lista, int pos);
    
    /* A função "lista_tamanho", cujo o retorno é do tipo inteiro, é responsável por retornar o tamanho (a quantidade de elementos) dentro da lista em 
    questão.*/
    int lista_tamanho(LISTA *lista);

    /* A função "lista_cheia", cujo o retorno é do tipo booleano, é responsável por retornar se é VERDADE OU FALSO que o tamanho da lista, armazenado no 
    campo da struct LISTA, é o mesmo valor ou maior que TAM_MAX. */
    bool lista_cheia(LISTA *lista);

    /* A função "lista_apagar", cujo retorno é do tipo void, a partir do duplo ponteiro que é recebido como parâmetro, tem o papel de liberar a memória
    alocada de cada int do vetor de itens, e somente depois, liberar o espaço alocado para a estrutura da lista.*/
    bool lista_vazia(LISTA *lista);

    /* A função "lista_apagar", cujo retorno é do tipo void, a partir do duplo ponteiro que é recebido como parâmetro, tem o papel de liberar a memória
    alocada de cada int do vetor de itens, e somente depois, liberar o espaço alocado para a estrutura da lista.*/
	void lista_apagar(LISTA **lista);

    /* A função "lista_imprimir", cujo retorno é do tipo void e cujo parâmetro recebido é o própria lista, tem o objetivo de printar o conteúdo guardado
    em cada int da estrutura. */
    void lista_imprimir(LISTA *lista);

#endif