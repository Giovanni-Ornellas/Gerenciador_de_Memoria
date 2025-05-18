/**
 * @file main.c
 * @brief Ponto de entrada principal do simulador de Gerenciador de Memória.
 *
 * Este programa simula o funcionamento de um gerenciador de memória baseado em alocação contígua.
 * Permite testar diferentes estratégias de alocação: First Fit, Best Fit e Worst Fit.
 * Também realiza liberação de memória, exibe o estado atual da memória, detecta fragmentação externa,
 * e salva os dados em arquivo. Registra falhas de alocação em um log.
 */

#include <stdio.h>
#include "memoria.h"
#include "alocacao.h"
#include "log.h"

/**
 * @brief Função principal do simulador de memória.
 *
 * Fluxo de execução:
 * - Inicializa toda a memória como livre.
 * - Aloca blocos para processos utilizando:
 *     - First Fit (para processos 1, 2 e 3)
 *     - Best Fit (teste com PID 1 reutilizado)
 *     - Worst Fit (para processo 6)
 * - Libera memória previamente alocada (processo 1).
 * - Exibe o estado da memória no terminal.
 * - Salva o estado da memória em um arquivo.
 * - Exibe relatório sobre fragmentação externa.
 * - Registra em log falhas de alocação.
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

    // Tenta alocar 10 blocos para o processo 4 usando Best Fit (PID 1 reutilizado para simular cenário)
    if (!best_fit(1, 10))
        log_erro(4, "Best Fit", "nenhum bloco adequado encontrado");

    // Tenta alocar 8 blocos para o processo 6 usando Worst Fit
    if (!worst_fit(6, 8))
        log_erro(6, "Worst Fit", "nenhum bloco suficientemente grande encontrado");

    // Exibe o estado atual da memória no terminal
    imprimir_memoria();

    // Salva o estado da memória em arquivo para futura análise
    salvar_memoria("estado.txt");

    // Exibe estatísticas sobre fragmentação externa
    exibir_fragmentacao();

    return 0;
}
