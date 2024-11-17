#ifndef LISTA_H
    #define LISTA_H
    #define TAM_MAX 200
    #define ERRO -1
    #include <stdbool.h>

    /* ESTE É O TAD LISTA */

    /* TYPEDEF utilizado para representar o tipo 'struct lista_' apenas por 'LISTA' */
    typedef struct lista_ LISTA;

    /* A função "lista_criar", cujo retorno tem tipo LISTA *, tem o papel de criar a estrutura de uma lista, alocando a sua memória dinamicamente,
    o parâmetro ordenada indica se será uma lista ordenada ou não */
    LISTA *lista_criar(bool ordenada);

    /* A função "lista_inserir", cujo retorno é do tipo booleano, é responsável por, a partir dos parâmetros recebidos (LISTA *lista: A LISTA
    EM QUE OCORRERÁ A INSERÇÃO, int *int: O int QUE SE DESEJA INSERIR), efetuar a inserção de uma chave inteira.*/
    bool lista_inserir(LISTA *lista, int chave);

    /* A função "lista_remover", cujo retorno é do tipo booleano, é responsável por, a partir dos parâmetros recebidos (LISTA  *lista: A LISTA EM
    QUE OCORRERÁ A REMOÇÃO, int chave: A CHAVE QUE SE DESEJA REMOVER), efetuar a remoção de determinada chave da lista. */
    bool lista_remover(LISTA *lista, int chave);

    /* A função "lista_procura", cujo retorno é do tipo booleano, tem a função de retornar ao usuário se determinada chave, dada como parâmetro, existe
    ou não dentro da lista. */
    bool lista_procura(LISTA *lista, int chave);
    
    /* A função "lista_tamanho", cujo o retorno é do tipo inteiro, é responsável por retornar o tamanho (a quantidade de elementos) dentro da lista. */
    int lista_tamanho(LISTA *lista);

    /* A função "lista_cheia", cujo o retorno é do tipo booleano, é responsável por retornar se é VERDADEIRO OU FALSO que a lista está cheia */
    bool lista_cheia(LISTA *lista);

    /* A função "lista_vazia", cujo o retorno é do tipo booleano, é responsável por retornar se é VERDADEIRO OU FALSO que a lista está vazia */
    bool lista_vazia(LISTA *lista);

    /* A função "lista_apagar", cujo retorno é do tipo void, a partir do endereço da lista, recebido como parâmetro, tem o papel de liberar a memória
    alocada para a lista, depois de finalizada suas operações.*/
	void lista_apagar(LISTA **lista);

    /* A função "lista_imprimir", cujo retorno é do tipo void e cujo parâmetro recebido é o própria lista, tem o objetivo de printar o conteúdo guardado
    em cada elemento da lista */
    void lista_imprimir(LISTA *lista);

#endif