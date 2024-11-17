#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
/* 
A 'struct lista_', por meio do typedef feito no TAD "lista.h", passa a ser do tipo 'LISTA'. Uma lista permite a inserção e remoção de itens
em qualquer posição.
A estrutura possui quatro campos:
01) chaves[TAM_MAX]: Um vetor de chaves, que armazena os elementos da lista. O tamanho máximo do vetor é definido pela
constante 'TAM_MAX'.
02) inicio: um inteiro que representa o índice do primeiro elemento na lista.
03) fim: um inteiro que representa o índice (a posição) do próximo espaço disponível, após o último elemento da lista.
04) tamanho: um inteiro que indica o número de itens armazenados na lista, valor que se atualiza conforme itens são inseridos ou removidos. 
05) ordenada: um booleano que armazena se a lista será ou não ordenada
*/
struct lista_{
    int chaves[TAM_MAX];
    int inicio;
    int fim; // O PRÓXIMO ÍNDICE DISPONÍVEL
    int tamanho; // QNTD DE ELEMENTOS DO VETOR DE ITENS
    bool ordenada;
};

/* 
A função "lista_criar", cujo retorno tem tipo LISTA *, tem o papel de criar a estrutura de uma lista, alocando a sua memória dinamicamente e
inicializando os campos 'tamanho', 'inicio' e 'fim' como 0 (Já que a lista acabou de ser criada e está vazia, portanto, todos recebem 0), além
de definir, conforme o parâmetro recebido 'ordenada', se ela será ou não ordenada:
01) Em caso de erro na alocação de memória, apenas retorna NULL sem mudar os campos da struct.
02) Em caso de sucesso na alocação de memória, os campos 'tamanho', 'inicio' e 'fim' são inicializados como 0, para que se possa futuramente
operar com o vetor de chaves a partir desses valores. Assim, retorna-se um ponteiro para este lista.
Complexidade: O(1).
*/
LISTA *lista_criar(bool ordenada){
    // Alocação da memória a partir da função da <stdlib.h> malloc().
    LISTA *l = NULL;
    l = (LISTA *) malloc(sizeof(LISTA));
    // Se a memória para lista for corretamente alocada, são inicializados os campos da struct.
    if(l != NULL){
        // O índice inicial e o final da lista, ao ser criada, são a posição 0, assim como o seu tamanho tem valor 0.
        l->inicio = 0;
        l->fim = 0;
        l->tamanho = 0;
        // A lista recebe o valor booleano que indica se será ou não ordenada, ficando aqui armazenada essa informação.
        l->ordenada = ordenada;
    }
    // Possíveis retornos: NULL(Falha na alocação) ou LISTA* (Sucesso na alocação).
    return l;
}

/*
A função "lista_busca", cujo retorno é do tipo inteiro, é responsável por realizar uma busca binária em uma lista ordenada do valor 'val', 
recebido como parâmetro. Como a cada iteração do while, reduz-se o espaço de busca à metade, esse se torna um algoritmo extremamente eficaz
ao efetuar uma busca em uma lista ordenada (log n).
01) Retorna 'meio', caso ache um item com o mesmo valor
02) Retorna 'inf', o limite inferior da lista depois de realizada a busca, quando ele ultrapassar o limite superior 'sup'.
Coplexidade: O(LOG N).
*/
int lista_busca(LISTA *lista, int val){
    // Declara e inicializa a variável 'inf' e 'sup', respectivamente, como os limites iniciais inferior e superior da busca
    int inf = lista->inicio;
    int sup = lista->fim;
    // Declaração da variável auxiliar 'meio'
    int meio;
    // Inicia-se um laço while cujo critério de parada é o limite inferior ultrapassar o limite superior (O valor não existe na lista)
    while (inf < sup) {
        // A variável, a cada iteração do while, recebe o novo meio da busca, gerado pela média aritmética dos limites inferior e superior
        meio = (inf + sup) / 2;

        // Verifica-se, primeiramente, se o termo localizado no meio tem o valor que se está buscando, retornando 'meio', caso sim.
        if (lista->chaves[meio] == val) {
            return meio;
        }
        // Caso contrário, se o valor buscado é menor que o do termo central, o espaço de busca é reduzido à metade, tornando o índice do 
        // meio o novo limite superior da busca
        else if ((lista->chaves[meio]) > val) {
            sup = meio;
        }
        // Caso contrário, o valor buscado é garantidamente maior que o termo central. Então, o espaço de busca é reduzido à metade, ao
        // tornar o índice do meio+1 o novo limite inferior da busca.
        else {
            inf = meio + 1;
        }
    }
    // O limite inferior aqui retornado representa a posição em que o elemento deveria estar, mas não está (Útil para uma eventual inserção)
    return inf;
}

/*
A função "lista_inserir_posição", cujo retorno é do tipo booleano, tem objetivo de, a partir dos parâmetros recebidos (LISTA *lista: A LISTA
EM QUE OCORRERÁ A INSERÇÃO, int pos: A POSIÇÃO IDEAL DE INSERÇÃO, itn chave: A CHAVE QUE SE DESEJA INSERIR,), efetuar a inserção de uma chave
na lista e mantê-la ordenada. Como se trata de uma lista sequencial, para mantê-la ordenada após uma inserção, é necessário fazer deslocamentos
para abrir um espaço para inserção numa dada posição. A quantidade de deslocamentos a ser realizada é descrita por lista->fim - pos.
01) Caso a lista não exista, esteja cheia ou a posição esteja fora dos limites da lista, retorna-se FALSO, indicando que não foi possível inserir.
02) Caso contrário, a lista existe, não está cheia, é retornado VERDADEIRO após fazer a inserção na posição ideal e os deslocamentos necessários.
Complexidade: 0(N)
OBS.: No pior caso, a inserção acontece na primeira posição, sendo necessário deslocar todos os elementos.
*/
bool lista_inserir_posicao(LISTA *lista, int pos, int chave){
    // Verifica se a lista existe e não está cheia e, a posição está dentro do limite da lista (0 a lista->fim são as únicas possíveis opções de inserção)
    if(!lista_cheia(lista) && pos >= 0 && pos <= lista->fim){
        // O vetor é percorrido, de trás para frente, até a posição que se deseja inserir, fazendo os deslocamentos para abrir um espaço    
        for(int i = lista->fim; i > pos; i--){                                                                                                                                                                                            
            lista->chaves[i] = lista->chaves[i-1];                                                                                                                                                                                              
        }                                                                       
        // Terminado o laço 'for', tem-se livre a posição de inserção para assim fazê-la. Em seguida, são incrementados os campos 'fim' e 'tamanho'.                                                                                                                                                  
        lista->chaves[pos] = chave;                                                                                                                                                                                                          
        lista->fim++;                                                                                                                                                                                                                    
        lista->tamanho++;                                          
        // É retornado VERDADEIRO, indicando que houve efetivamente a inserção                                                                                                                                                                           
        return true;                                                                                                                                                                                                                          
    }                                                                                                                                                                                                                                         
    // É retornado FALSO, indicando que a inserção não pôde ser bem sucedida
    return false;                                                                                                                                                                                                                             
}              

/*
A função "lista_inserir_fim", cujo retorno é do tipo booleano, é responsável por, a partir dos parâmetros recebidos (LISTA *lista: A LISTA
EM QUE OCORRERÁ A INSERÇÃO, int chave: A CHAVE QUE SE DESEJA INSERIR), efetuar a inserção de uma chave no final da lista por padrão, o que é
recompensado em desempenho, não precisa fazer deslocamentos, mas assim, não se preocupa com ordenação e impossibilita busca binária.
01) Caso a lista esteja cheia ou nem sequer exista(ambas verificações feitas na função "lista_cheia"), retorna-se FALSO, indicando que não
foi possível realizar a inserção.
02) Se isso não se aplicar, a lista existe e há espaços vagos, desse modo, insere-se e retorna-se TRUE, indicando o sucesso. 
Complexidade: 0(1)
*/
bool lista_inserir_fim (LISTA *lista, int chave) {
    // Verificação se a lista existe e não está cheia.
    if(!lista_cheia(lista)){
        // Inserção na posição final (OBS.: lista->fim é a próxima posição vaga, não o último elemento) e incrementação dos campos 'fim' e 'tamanho'.
        lista->chaves[lista->fim] = chave;
        lista->fim++;
        lista->tamanho++;
        // Retorna VERDADEIRO, indicando que a chave foi inserida no fim da lista com sucesso.
        return(true);
    }
    // Retorna FALSO, indicando que não foi possível inserir no fim, afinal, ou a lista não existe ou a lista está cheio.
    return(false);
}                                                                                                                                                                                                                               

/*
A função "lista_inserir", cujo retorno é do tipo booleano, é responsável por, a partir dos parâmetros recebidos (LISTA *lista: A LISTA
EM QUE OCORRERÁ A INSERÇÃO, int chave: A CHAVE QUE SE DESEJA INSERIR), efetuar a inserção de uma chave. Para tanto, ela chama as funções
auxiliares "lista_busca"+"lista_inserir_posicao" e "lista_inserir_fim", conforme se a lista é ordenada ou não. 
01) A lista é ordenada, logo, utiliza-se a lógica das funções "lista_busca" e "lista_inserir_posicao" combinadas para inserir adequadamente.
02) A lista não é ordenada, logo, basta inserir no fim com a função "lista_inserir_fim"
Complexidade: 
* ORDENADA: T(N) = LOG N + N --> O(N)
* NÃO ORDENADA: O(1)
*/                                                                                                                                                                                                                                  
bool lista_inserir(LISTA *lista, int chave){      
    // Verifica se se trata de uma lista ordenada ou não com base no campo da struct LISTA, lista->ordenada                                                                                                                                                                                           
    if(lista->ordenada){              
        // A variável 'x' recebe o inteiro que indica a posição ideal de inserção, obtida pela busca binária                                                                                                                                                                                                               
        int x = lista_busca(lista, chave);
        // A variável 'x' é passada como parâmetro para a inserção ocorrer na posição ideal para a chave, mantendo ordenada a lista e retorna o
        //  booleano de "lista_inserir_posicao"                                                                                                                                                                                    
        return(lista_inserir_posicao(lista, x, chave));                                                                                                                                                                                        
    }     
    // Caso a lista não seja ordenada, para manter a complexidade O(1), insere-se no fim e retorna o booleano de "lista_inserir_fim".                                                                                                                                                                                                                                            
    return(lista_inserir_fim(lista, chave));                                                                                                                                                                                                                                                                                                                                                                          
}        

/*
A função "lista_remover", cujo retorno é do tipo int, é responsável por, a partir dos parâmetros recebidos (LISTA *lista: A LISTA EM QUE
OCORRERÁ A REMOÇÃO, int chave: A CHAVE QUE SE DESEJA REMOVER), efetuar a remoção de um elemento da lista. Como se trata de uma lista sequencial,
para mantê-la organizada após uma remoção, é necessário fazer deslocamentos para completar o espaço do elemento retirado, retomando para que a
lista fique contínua. A quantidade de deslocamentos a ser realizada é descrita por lista->fim-1-pos. 
01) Caso a lista não exista ou esteja vazia (verificações de "lista_vazia"), ou se o elemento não existir na lista, é retornado FALSO
02) Caso contrário, a lista existe, há algum elemento nela com aquela chave, então, ele é retirado, os delocamentos são feitos para mantê-la
organizada. Logo, retorna VERDADEIRO, indicando uma remoção bem sucedida.
Complexidade: O(N)
OBS.:No pior caso, a remoção acontece na primeira posição, de modo que é necessário deslocar todos os elementos
*/
bool lista_remover(LISTA *lista, int chave) {
    // Verificação se a lista não existe ou está vazia
    if (lista_vazia(lista)) {
        return false;
    }
    int pos = lista->inicio;
    // Busca pela chave na lista
    while (pos < lista->fim && lista->chaves[pos] != chave) {
        pos++;
    }
    // Se a chave não foi encontrada, retorna false
    if (pos == lista->fim) {
        return false;
    }
    // Desloca os elementos após a posição 'pos' uma posição à esquerda, para arrumar a continuidade da lista
    for (int j = pos; j < lista->fim - 1; j++) {
        lista->chaves[j] = lista->chaves[j + 1];
    }
    // Decrementa 'fim' e 'tamanho' após a remoção
    lista->fim--;
    lista->tamanho--;
    // Retorna que a remoção foi bem sucedida
    return true;
}


/*
A função "lista_procura", cujo retorno é do tipo booleano, tem a função de retornar ao usuário se uma determinada chave, recebida como parâmetro da função, 
existe ou não dentro da lista
01) Caso a lista não exista ou a chave procurada não existe na lista, é retornado FALSO.
02) Caso contrário, a lista existe: 
 * ORDENADA: a partir da função "lista_busca" (Tem que ter retornado 'meio'), a posição ideal para aquela chave é encontrada. É checado se a chave está
nessa posição, se sim, retorna VERDADEIRO, senão, FALSO. 
 * NÃO ORDENADA: é feita uma busca sequencial na lista, retornando VERDADEIRO se encontrada ou FALSO, caso não seja encontrada
Complexidade: O(LOG N) para lista ordenada, O(N) para não ordenada.
*/
bool lista_procura(LISTA *lista, int chave) {
    // Verificação se a lista existe
    if(lista != NULL) {
        if(lista->ordenada) {
            // A função "lista_busca" (O(LOG N)) é chamada para encontrar a posição do item com chave dada na lista ordenada
            int i = lista_busca(lista, chave);
            // Caso de "lista_busca" retornar o fim da lista, indicativo de que o item não existe
            if(i >= lista->fim) {
                // Retorna NULL, mostrando que o item não existe
                return false;
            }
            // Verificação para ver se a posição retornada pelo "lista_busca" é de um item com a mesma chave(Retornou 'meio')
            if(chave == (lista->chaves[i]) ) {
                // Retorna NULL, mostrando que não há um item com aquela chave na lista.
                return true;
            }
            // O item com a chave almejada é retornado.
            return false;
        }
        int i;
        
        for(i = 0; i<lista->fim && (lista->chaves[i])!= chave; i++);
        
        if(i == lista->fim) {
            return false;
        } else {
            return true; 
        }   
    }
    // Retorna NULL se a lista não existe
    return false;
}

/* 
A função "lista_tamanho", cujo o retorno é do tipo inteiro, é responsável por retornar o tamanho (a quantidade de elementos) dentro da lista em questão.
01) Caso a lista não exista, retorna-se uma constante ERRO.
02) Caso ela exista, é retornado o campo da struct LISTA, lista->tamanho, indicando a quantidade de elementos dentro dela.
Complexidade: O(1).
*/
int lista_tamanho(LISTA *lista) {
    // Verificação se a lista existe.
    if(lista != NULL) {
        // Retorna o campo da da struct LISTA, lista->tamanho, indicando a quantidade de elementos existentes nela.
        return(lista->tamanho);
    }
    // Retorna um ERRO (-1), sabendo que o tamanho não pode ser negativo.
    return ERRO;
}

/*
A função "lista_vazia", cujo o retorno é do tipo booleano, é responsável por retornar se é VERDADEIRO OU FALSO que o tamanho da lista, armazenado no campo
da struct LISTA, é 0.
01) Caso a lista não exista, retorna-se VERDADEIRO.
02) Caso ele exista, é retornado:
 * VERDADEIRO: se não há elementos na lista, isto é, seu tamanho é 0.
 * FALSO: se há pelo menos um elemento na lista, isto é, seu tamanho não é 0.
Complexidade: O(1).
*/
bool lista_vazia(LISTA *lista){         
    // Verificação se a lista existe.                                                                                                                                                                                                      
    if(lista != NULL) {               
        // Retorna o valor booleano da comparação de lista->tamanho com 0: VERDADEIRO, se lista->tamanho = 0, do contrário, FALSO.                                                                                                                                                                                                   
        return (lista->tamanho == 0);       
    }                                                                                                                                                                                                    
    // Retorna VERDADEIRO por padrão quando a lista não existe.                                                                                                                                                                                                                                   
    return true;                                                                                                                                                                                                                              
}                                                                                                                                                                                                                                             

/*
A função "lista_cheia", cujo o retorno é do tipo booleano, é responsável por retornar se é VERDADEIRO OU FALSO que o tamanho da lista, armazenado no campo
da struct LISTA, é o mesmo valor ou maior que TAM_MAX.
01) Caso a lista não exista, retorna-se VERDADEIRO.
02) Caso ele exista, é retornado:
 * VERDADEIRO: se o campo da struct LISTA, lista->tamanho, atingiu ou ultrapassou o limite do tamanho do vetor (TAM_MAX), configurando um lista cheio.
 * FALSO:  se o campo da struct LISTA, lista->tamanho, ainda não atingiu o limite do tamanho do vetor (TAM_MAX), configurando que ainda há posições vagas.
Complexidade: O(1).
*/                                                                                                                                                                                                                               
bool lista_cheia(LISTA *lista){    
    // Verificação se a lista existe.                                                                                                                                                                                                           
    if(lista != NULL) {                            
        // Retorna o valor booleano da comparação de lista->tamanho com TAM_MAX: VERDADEIRO, se lista->tamanho >= TAM_MAX, do contrário, FALSO.                                                                                                                                                                                             
        return (lista->tamanho >= TAM_MAX);                                                                                                                                                                                                     
    }                  
    // Retorna VERDADEIRO por padrão quando a lista não existe.                                                                                                                                                                                                           
    return true;                                                                                                                                                                                                                              
}  

/* 
A função "lista_apagar", cujo retorno é do tipo void, a partir do duplo ponteiro que é recebido como parâmetro, tem o papel de liberar da estrutura
da lista, considerando que chaves é um vetor estático.
01) Caso a lista recebida seja nulo, ou seja, não tenha ocorrido corretamente a alocação dinâmica, nenhuma operação é realizada.
02) Caso a lista não seja nula, ou seja, tenha ocorrido corretamente a alocação dinâmica, é liberada a estrutura em si.
Complexidade: O(1)
*/
void lista_apagar(LISTA **lista) {
    // Verificação se a lista é nulo/existe. Caso sim, retorna, sem fazer nenhuma operação
    if (lista == NULL || *lista == NULL) {
        return;
    }
    // A memória da estrutura pode ser liberada.
    free(*lista);
    // Como boa prática, faz-se o ponteiro para lista receber nulo, a fim de não ser possível acessar mais a região de memória liberada.
    *lista = NULL;
    return;
}

/* 
A função "lista_imprimir", cujo retorno é do tipo void e cujo parâmetro recebido é o própria lista, tem o objetivo de printar o conteúdo de cada
chave da lista.
01) Caso a lista não exista, printa a mensagem "Lista vazia" e retorna.
02) Caso a lista exista, faz-se a impressão do número da posição da chave naa lista e do conteúdo de cada uma delas
Complexidade: O(N)
*/
void lista_imprimir(LISTA *lista) {
    // Verificação se a lista existe ou se está vazia.
    if (lista == NULL || lista_vazia(lista)) {
        printf("Lista vazia.\n");
        return;
    }
    // Faz-se a impressão da posição da chave e do conteúdo de cada uma delas, da posição inicial, até a posição do último elemento, na ordem crescente
    for (int i = lista->inicio; i < lista->fim; i++) {
        printf("Chave %d: %d\n", i, (lista->chaves[i]));
    }
    // Printa-se o \n por questões estéticas
    printf("\n");
}