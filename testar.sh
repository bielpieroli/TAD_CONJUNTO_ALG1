#!/bin/bash
#Esse programa funciona em sistemas linux

# Caminho para o executável
EXECUTAVEL="./main.exe"

# Diretório dos testes
DIRETORIO_TESTES="./Testes"

# Contadores para os resultados
PASSARAM=0
FALHARAM=0

# Loop por todos os arquivos de entrada
for ENTRADA in "$DIRETORIO_TESTES"/*.in; do
    # Nome base do arquivo (ex: 0.in -> 0)
    BASE=$(basename "$ENTRADA" .in)
    SAIDA_ESPERADA="$DIRETORIO_TESTES/$BASE.out"
    SAIDA_GERADA="$DIRETORIO_TESTES/$BASE.gerado"

    # Executa o programa com o arquivo de entrada e salva a saída gerada
    "$EXECUTAVEL" < "$ENTRADA" > "$SAIDA_GERADA"

    # Compara a saída gerada com a esperada
    if diff -q "$SAIDA_GERADA" "$SAIDA_ESPERADA" > /dev/null; then
        echo "Teste $BASE: PASSED"
        ((PASSARAM++))
    else
        echo "Teste $BASE: FAILED"
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
