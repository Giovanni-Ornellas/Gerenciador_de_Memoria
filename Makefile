# Caminhos
BIN_PROCESSADOR=build/processador
INTERFACE_GUI=interface/interface_GUI.py

# Fontes do processador
SRC_PROCESSADOR=src/processador.c src/memoria.c src/alocacao.c
INCLUDES=-Iinclude

# Regra padrão: compila e executa a interface gráfica
all: $(BIN_PROCESSADOR)
	python3 $(INTERFACE_GUI)

# Compilação do processador
$(BIN_PROCESSADOR): $(SRC_PROCESSADOR)
	mkdir -p build
	gcc $(SRC_PROCESSADOR) -o $(BIN_PROCESSADOR) $(INCLUDES)

# Executa apenas o processador (opcional)
run-processador: $(BIN_PROCESSADOR)
	./$(BIN_PROCESSADOR)

# Limpa arquivos gerados
clean:
	rm -rf build log.txt estado.txt comando.txt
