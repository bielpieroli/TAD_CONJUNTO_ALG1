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
    # Nome base do arquivo (ex: 0.in -> 0)
    BASE=$(basename "$ENTRADA" .in)
    SAIDA_ESPERADA="$DIRETORIO_TESTES/$BASE.out"
    SAIDA_GERADA="$DIRETORIO_TESTES/$BASE.gerado"
    LOG_VALGRIND="$DIRETORIO_TESTES/$BASE.valgrind"

    # Executa o programa com o Valgrind
    valgrind --leak-check=full --error-exitcode=1 "$EXECUTAVEL" < "$ENTRADA" > "$SAIDA_GERADA" 2> "$LOG_VALGRIND"

    # Verifica se Valgrind encontrou vazamentos
    if [ $? -ne 0 ]; then
        echo "Teste $BASE: FAILED (Memory Leak)"
        echo "Relatório do Valgrind:"
        cat "$LOG_VALGRIND"
        ((MEMORY_LEAKS++))
        ((FALHARAM++))
        continue
    fi

    # Compara a saída gerada com a esperada
    if diff -q "$SAIDA_GERADA" "$SAIDA_ESPERADA" > /dev/null; then
        echo "Teste $BASE: PASSED"
        ((PASSARAM++))
    else
        echo "Teste $BASE: FAILED (Output Mismatch)"
        echo "Diferenças:"
        diff "$SAIDA_GERADA" "$SAIDA_ESPERADA"
        ((FALHARAM++))
    fi
done

# Resumo dos resultados
echo "--------------------------------------"
echo "Total de testes: $((PASSARAM + FALHARAM))"
echo "Passaram: $PASSARAM"
echo "Falharam: $FALHARAM"
echo "Memory Leaks detectados: $MEMORY_LEAKS"
