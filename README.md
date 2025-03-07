# TAD Conjunto com Árvores Balanceadas (AVL e LLRBT)  
# Balanced Tree Set ADT (AVL and LLRBT)

Este projeto implementa um **Tipo Abstrato de Dados (TAD)** para manipulação de conjuntos utilizando duas estruturas de dados balanceadas: **Árvore AVL** e **Left-Leaning Red-Black Tree (LLRBT)**. O projeto foi desenvolvido como parte da disciplina de Algoritmos e Estruturas de Dados, com o objetivo de explorar operações eficientes com Conjuntos, como pertinência, união, interseção e remoção.

This project implements an **Abstract Data Type (ADT)** for set manipulation using two balanced data structures: **AVL Tree** and **Left-Leaning Red-Black Tree (LLRBT)**. It was developed as part of the Algorithms and Data Structures subject, aiming to explore efficient set operations such as membership, union, intersection, and removal.

---

## ESTRUTURA DO DIRETÓRIO / DIRECTORY STRUCTURE

O diretório do projeto está organizado da seguinte forma:  
The project directory is organized as follows:

> ```
> 📂 TAD_CONJUNTO_ALG1 
> ├── 📂 Testes/  # Casos de teste / Test cases  
> │   ├── 📄 1.in  # Entrada para o teste 1 / Input for test 1  
> │   ├── 📄 1.out  # Saída esperada para o teste 1 / Expected output for test 1  
> │   ├── 📄 2.in  # Entrada para o teste 2 / Input for test 2  
> │   ├── 📄 2.out  # Saída esperada para o teste 2 / Expected output for test 2  
> │   └── ...  
> │  
> ├── 👾 arvoreAVL.c  # Implementação da Árvore AVL / AVL Tree implementation  
> ├── 👾 arvoreAVL.h  # Cabeçalho da Árvore AVL / AVL Tree header  
> │  
> ├── 👾 LLRBT.c  # Implementação da Árvore LLRBT / LLRBT implementation  
> ├── 👾 LLRBT.h  # Cabeçalho da Árvore LLRBT / LLRBT header  
> │  
> ├── 👾 set.c  # Implementação do TAD Conjunto / Set ADT implementation  
> ├── 👾 set.h  # Cabeçalho do TAD Conjunto / Set ADT header  
> │  
> ├── 👾 main.c  # Função principal do programa / Main program function  
> │  
> ├── ⚙️ Makefile  # Automação de compilação e testes / Compilation and testing automation  
> │  
> ├── 📄 README.md  # Documentação do projeto / Project documentation  
> ├── 📄 relatorio.txt  # Relatório do projeto / Project report  
> │  
> ├── 🖥️ testar.bat  # Script de testes (Windows) / Test script (Windows)  
> └── 🖥️ testar.sh  # Script de testes com Valgrind (Linux) / Test script with Valgrind (Linux)  
> ```

---

## OPERAÇÕES DO TAD CONJUNTO / SET ADT OPERATIONS

O TAD Conjunto oferece as seguintes operações:  
The Set ADT provides the following operations:

1. **Pertinência / Membership**:
   - Verifica se um elemento pertence ao conjunto.  
     Checks if an element belongs to the set.
   - **O(log n)**.

2. **União / Union**:
   - Retorna a união de dois conjuntos.  
     Returns the union of two sets.
   - **O((n + m) log(n + m))**.

3. **Interseção / Intersection**:
   - Retorna a interseção de dois conjuntos.  
     Returns the intersection of two sets.
   - **O(m log(nm))**.

4. **Remoção / Removal**:
   - Remove um elemento do conjunto, caso ele exista.  
     Removes an element from the set if it exists.
   - **O(log n)**.

---

## ENTRADAS E SAÍDAS / INPUTS AND OUTPUTS

### Entrada do Programa / Program Input

1. Escolha da estrutura de dados:  
   Choose the data structure:
   - `0` para **Árvore AVL** / for **AVL Tree**.
   - `1` para **LLRBT** / for **LLRBT**.

2. Tamanho dos conjuntos:  
   Set sizes:
   - Dois inteiros `n` e `m`, representando o tamanho dos conjuntos `A` e `B`, respectivamente.  
     Two integers `n` and `m`, representing the sizes of sets `A` and `B`, respectively.

3. Elementos dos conjuntos:  
   Set elements:
   - `n` elementos para o conjunto `A`.  
     `n` elements for set `A`.

     
   - `m` elementos para o conjunto `B`.  
     `m` elements for set `B`.

4. Operação desejada:  
   Desired operation:
   - `1` para **Pertinência** (requer um elemento `x` para verificar) / for **Membership** (requires an element `x` to check).
   - `2` para **União** / for **Union**.
   - `3` para **Interseção** / for **Intersection**.
   - `4` para **Remoção** (requer um elemento `x` para remover) / for **Removal** (requires an element `x` to remove).

### Saída do Programa / Program Output

- **Pertinência / Membership**:
  - `"Pertence."` se o elemento estiver no conjunto.  
    `"Pertence."` if the element is in the set.


  - `"Não pertence."` caso contrário.  
    `"Não pertence."` otherwise.

- **União / Union**:
  - Exibe os elementos do conjunto resultante da união.  
    Displays the elements of the resulting union set.

- **Interseção / Intersection**:
  - Exibe os elementos do conjunto resultante da interseção.  
    Displays the elements of the resulting intersection set.

- **Remoção / Removal**:
  - Exibe os elementos do conjunto após a remoção (se o elemento existir).  
    Displays the elements of the set after removal (if the element exists).

---

## ESTRUTURAS DE DADOS UTILIZADAS / DATA STRUCTURES USED

O TAD Conjunto é implementado utilizando duas estruturas de dados balanceadas:  
The Set ADT is implemented using two balanced data structures:

1. **Árvore AVL**:
   - Garante um balanceamento estrito, mantendo a diferença de altura entre subárvores adjacentes sempre menor ou igual a 1.  
   - Ideal para operações de busca frequentes, com complexidade de busca, inserção e remoção em **O(log n)**.  
   - Ao proporcionar um maior controle sobre a altura da árvore, favorece-se a operação de busca.
  
  I)  **AVL Tree**:
   - Ensures strict balancing, keeping the height difference between adjacent subtrees always less than or equal to 1.
   - Ideal for frequent search operations, with search, insertion, and removal complexity of **O(log n)**.
   - By providing greater control over tree height, search operations are favored.
   
2. **Left-Leaning Red-Black Tree (LLRBT)**:
   - Uma variante da Red-Black Tree que simplifica a implementação, mantendo o balanceamento próximo ao ideal.  
   - Complexidade de busca, inserção e remoção permanecem **O(log n)**.  
   - Com menos rotações em comparação à AVL, favorece alguns casos de inserção e remoção.
  
  II) **Left-Leaning Red-Black Tree (LLRBT)**:
   - A variant of the Red-Black Tree that simplifies implementation while maintaining near-ideal balancing.
   - Search, insertion, and removal complexity remains **O(log n)**.
   - Fewer rotations are required, when compared to AVL, favoring some insertion and removal cases.

---

## COMPLEXIDADE ESTIMADA POR OPERAÇÃO / ESTIMATED COMPLEXITY PER OPERATION

| Operação / Operation      | Complexidade (AVL)        | Complexidade (LLRBT)     |
|---------------------------|---------------------------|--------------------------|
| Pertinência / Membership  | O(1.44 log n)             | O(2 log n)               |
| União / Union             | O(1.44 (n + m) log(n + m))| O(2 (n + m) log(n + m))  |
| Interseção / Intersection | O(1.44 m log(nm))         | O(2 m log(nm))           |
| Remoção / Removal         | O(log n)                  | O(log n)                 |

---

Ambas as estruturas garantem complexidade **O(log n)** para operações básicas, sendo eficientes para manipulação de conjuntos.  
Both structures guarantee **O(log n)** complexity for basic operations, making them efficient for set manipulation.

## COMO USAR?

1. **COMPILAÇÃO** / **COMPILATION**:

   - A partir do comando do Makefile / Using the Makefile command:
   ```bash
    make all
   ```
   
   - Manualmente / Manually:
   ```bash
    gcc set.o LLRBT.o arvoreAVL.o main.c -o main.exe -std=c99 -Wall -Werror -lm
   ```
   
   OBS.: Lembrando que são gerados arquivos-objetos (.o's) na compilação.
   
   NOTE: Object files (.o's) are generated during compilation.
   
3. **EXECUÇÃO**:

   - A partir do comando do Makefile / Using the Makefile command:
   (assumindo que o Valgrind está instalado) / (assuming Valgrind is installed)
   ```bash
    make run
   ```
   
   - Manualmente (com Valgrind) / Manually (with Valgrind):
   ```bash
    valgrind ./main.exe 
   ```
   
   - Manualmente (sem Valgrind) / Manually (without Valgrind):
   ```bash
    ./main.exe 
   ```
   
4. **TESTAGEM** / **TESTING** (com base nos casos do diretório /Testes, sob a forma 1.in/1.out):
(Based on test cases in the /Testes directory, in the form 1.in/1.out):

   - A partir do comando do Makefile (Linux) / Using the Makefile command (Linux):
   ```bash
     make teste
   ```
   
   - Manualmente (Linux) / Mannualy (Linux):
   ```bash
    ./testar.sh main.exe
   ```
   
   - Manualmente (Windows) / Mannualy (Windows):
   ```bash
    .\testar.bat 
   ```
5. **ZIPAR** / **ZIP**:
   
   - A partir do comando do Makefile / Using the Makefile command:
   ```bash
    make zip
   ```

   - Manualmente / Manually:
   ```bash
     zip -r Dante_Joao.zip *
   ```

6. **LIMPAR** / **CLEAN**:
   - A partir do comando do Makefile / Using the Makefile command:
   ```bash
     make clean
   ```

   - Manualmente / Manually:
   ```bash
     rm -f *.o main.exe Dante_Joao.zip
   ```

# AUTORES / AUTHORS

- Dante Brito Lourenço - [15447326]

- João Gabriel Pieroli da Silva - [15678578]
