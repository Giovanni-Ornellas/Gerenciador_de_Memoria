/**
 * @file memoria.c
 * @brief Implementação das funções de gerenciamento de memória simulada.
 *
 * Este módulo implementa as operações básicas de manipulação de um vetor de memória,
 * representando blocos alocados e liberados para processos.
 */

#include <stdio.h>
#include "../include/memoria.h"

/// Vetor que representa a memória principal (0 = livre, >0 = PID do processo)
int memoria[TAM_MEMORIA];

/**
 * @brief Inicializa todos os blocos da memória como livres.
 *
 * A função define todos os valores do vetor `memoria` como 0.
 */
void inicializar_memoria() {
    for (int i = 0; i < TAM_MEMORIA; i++)
        memoria[i] = 0;
}

/**
 * @brief Libera todos os blocos ocupados por um processo específico.
 *
 * Substitui por zero todas as posições que contenham o PID fornecido.
 *
 * @param pid Identificador do processo a ser removido da memória.
 */
void liberar_memoria(int pid) {
    for (int i = 0; i < TAM_MEMORIA; i++)
        if (memoria[i] == pid)
            memoria[i] = 0;
}

/**
 * @brief Imprime o estado atual da memória no terminal.
 *
 * Mostra a memória em blocos de 20 colunas para facilitar a leitura.
 */
void imprimir_memoria() {
    for (int i = 0; i < TAM_MEMORIA; i++) {
        if (i % 20 == 0) printf("\n"); ///< Nova linha a cada 20 blocos
        printf("%2d ", memoria[i]);
    }
    printf("\n");
}

/**
 * @brief Salva o estado atual da memória em um arquivo de texto.
 *
 * Escreve os blocos da memória em uma única linha no formato:
 * `0 0 2 2 0 0 1 ...`
 *
 * @param arquivo Caminho e nome do arquivo de saída.
 */
void salvar_memoria(const char *arquivo) {
    FILE *f = fopen(arquivo, "w");
    for (int i = 0; i < TAM_MEMORIA; i++)
        fprintf(f, "%d ", memoria[i]);
    fclose(f);
}
