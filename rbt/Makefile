# Nome do executável
EXECUTABLE = programa.exe

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -std=c99 -g

# Arquivos de origem
SOURCES = main.c LLRBT.c

# Arquivos objetos
OBJECTS = $(SOURCES:.c=.o)

# Regra padrão: compilar tudo
all: $(EXECUTABLE)

# Compilar o executável a partir dos objetos
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

# Compilar os arquivos de origem para objetos
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Executar o programa
run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Limpar os arquivos gerados
clean:
	del /f /q $(OBJECTS) $(EXECUTABLE)

# Regra auxiliar para testes
.PHONY: all run clean
