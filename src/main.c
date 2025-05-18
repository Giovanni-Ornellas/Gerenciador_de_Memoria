/**
 * @file main.c
 * @brief Ponto de entrada principal para o simulador de Gerenciador de Memória.
 *
 * Este programa simula um gerenciador de memória com políticas de alocação First Fit e Best Fit.
 * Ele inicializa a memória, aloca blocos para processos simulados, libera memória
 * e imprime/salva o estado atual da memória.
 */

#include <stdio.h>
#include "memoria.h"
#include "alocacao.h"
#include "log.h"


/**
 * @brief Função principal do simulador de memória.
 *
 * Executa uma sequência de alocações e liberações com diferentes algoritmos de alocação:
 * - First Fit: para os processos 1, 2 e 3
 * - Best Fit: para o processo 4
 * Em caso de falha de alocação, registra o erro no log.
 * Após as operações, imprime e salva o estado da memória.
 *
 * @return int Retorna 0 ao final da execução com sucesso.
 */
int main() {
    // Inicializa toda a memória como livre (0)
    inicializar_memoria();

    // Aloca 10 blocos para o processo 1 usando First Fit
    if (!first_fit(1, 10))
        log_erro(1, "First Fit", "memória insuficiente");

    // Aloca 15 blocos para o processo 2
    if (!first_fit(2, 15))
        log_erro(2, "First Fit", "memória insuficiente");

    // Libera os blocos ocupados pelo processo 1
    liberar_memoria(1);

    // Aloca 5 blocos para o processo 3
    if (!first_fit(3, 5))
        log_erro(3, "First Fit", "memória insuficiente");

    // Aloca 7 blocos para o processo 4 usando Best Fit
    if (!best_fit(1, 10))
        log_erro(4, "Best Fit", "nenhum bloco adequado encontrado");

    if (!worst_fit(6, 8))
    log_erro(6, "Worst Fit", "nenhum bloco suficientemente grande encontrado");

    // Exibe a memória no terminal
    imprimir_memoria();

    // Salva o estado da memória em arquivo
    salvar_memoria("estado.txt");

    return 0;
}
