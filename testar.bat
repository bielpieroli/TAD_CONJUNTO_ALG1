@echo off
::Arquivo .bat para testar em sistemas Windows

:: Nome do executável
set EXECUTAVEL=main.exe

:: Diretório onde estão os arquivos de teste
set DIRETORIO_TESTES=Testes

:: Contadores de resultados
set PASSARAM=0
set FALHARAM=0

:: Loop por todos os arquivos de entrada
for %%f in (%DIRETORIO_TESTES%\*.in) do (
    :: Nome base do arquivo (ex: 0.in -> 0)
    set "BASE=%%~nf"
    
    :: Chama outro bloco para resolver problema de variáveis no loop
    call :processar_teste %%~nf
)

:: Mostra o resumo final
echo --------------------------------------
echo Total de testes: %PASSARAM%
echo Passaram: %PASSARAM%
echo Falharam: %FALHARAM%
pause
exit /b

:: Função para processar cada teste
:processar_teste
set BASE=%1
set ENTRADA=%DIRETORIO_TESTES%\%BASE%.in
set SAIDA_ESPERADA=%DIRETORIO_TESTES%\%BASE%.out
set SAIDA_GERADA=%DIRETORIO_TESTES%\%BASE%.gerado

:: Executa o programa com o arquivo de entrada e salva a saída gerada
%EXECUTAVEL% < %ENTRADA% > %SAIDA_GERADA%

:: Compara a saída gerada com a esperada
fc %SAIDA_GERADA% %SAIDA_ESPERADA% > nul
if errorlevel 1 (
    echo Teste %BASE%: FAILED
    set /a FALHARAM+=1
) else (
    echo Teste %BASE%: PASSED
    set /a PASSARAM+=1
)
exit /b
