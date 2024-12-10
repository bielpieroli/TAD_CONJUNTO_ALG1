#!/bin/bash
# Esse programa funciona em sistemas Linux

# Caminho para o executável
EXECUTAVEL="./main.exe"

# Diretório dos testes
DIRETORIO_TESTES="./Testes"

# Contadores para os resultados
PASSARAM=0
FALHARAM=0
MEMORY_LEAKS=0

# Loop por todos os arquivos de entrada
for ENTRADA in "$DIRETORIO_TESTES"/*.in; do
    echo "============================================="
    echo "Iniciando teste com entrada: $ENTRADA"
    echo "============================================="
    
    # Obter o nome do arquivo de saída correspondente
    SAIDA="${ENTRADA%.in}.out"
    
    # Executar o programa com Valgrind para verificar memory leaks
    valgrind_output=$(valgrind --leak-check=full --error-exitcode=1 "$EXECUTAVEL" < "$ENTRADA" 2>&1)
    
    if [ $? -ne 0 ]; then
        # Memory leak detectado
        MEMORY_LEAKS=$((MEMORY_LEAKS + 1))
        echo "🔴 Memory Leak detectado no caso: $ENTRADA"
        echo "$valgrind_output"
        FALHARAM=$((FALHARAM + 1))
    else
        # Caso sem memory leaks, comparar saída esperada e obtida
        actual_output=$("$EXECUTAVEL" < "$ENTRADA")
        expected_output=$(cat "$SAIDA")
        
        if [ "$actual_output" == "$expected_output" ]; then
            # Caso passou
            echo "✅ Caso passou com sucesso!"
            PASSARAM=$((PASSARAM + 1))
        else
            # Caso falhou, exibir diferença entre esperado e gerado
            echo "❌ Caso falhou!"
            echo -e "\nSaída esperada:"
            echo "$expected_output"
            echo -e "\nSaída obtida:"
            echo "$actual_output"
            FALHARAM=$((FALHARAM + 1))
        fi
    fi
    echo -e "\n"
done

# Exibir resumo dos resultados
echo "============================================="
echo "Resumo dos Resultados:"
echo "============================================="
echo "✅ Passaram: $PASSARAM"
echo "❌ Falharam: $FALHARAM"
echo "🔴 Memory leaks detectados: $MEMORY_LEAKS"
echo "============================================="
