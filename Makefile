# Caminho do executável
BIN=build/main

# Fontes e headers
SRC=src/main.c src/memoria.c src/alocacao.c src/log.c
INCLUDES=-Iinclude

# Regra principal
all: $(BIN)

# Compilação
$(BIN): $(SRC)
	mkdir -p build
	gcc $(SRC) -o $(BIN) $(INCLUDES)

# Executa o simulador
run: $(BIN)
	./$(BIN)

# Limpa arquivos gerados
clean:
	rm -rf build log.txt estado.txt
