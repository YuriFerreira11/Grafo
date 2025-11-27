# Nome do compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Werror -std=c99 -g -O2

# Arquivos fonte
SRC = main.c CaminhoSimples.c MatrizAdj.c Passeio.c

# Objetos gerados
OBJ = $(SRC:.c=.o)

# Nome do executável
TARGET = main

# Regra principal
all: $(TARGET)

# Como gerar o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Como compilar cada .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	@if exist main.o del /Q main.o
	@if exist CaminhoSimples.o del /Q CaminhoSimples.o
	@if exist MatrizAdj.o del /Q MatrizAdj.o
	@if exist Passeio.o del /Q Passeio.o
	@if exist programa.exe del /Q programa.exe

