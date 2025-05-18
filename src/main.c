/**
 * @file main.c
 * @brief Ponto de entrada principal para o simulador de Gerenciador de Memória.
 *
 * Este programa simula um gerenciador de memória utilizando diferentes estratégias de
 * alocação contígua: First Fit, Best Fit e Worst Fit. Ele inicializa a memória, executa
 * alocações e liberações de blocos para processos simulados, realiza compactação da
 * memória para evitar fragmentação externa, e imprime/salva o estado atual da memória.
 * Erros de alocação são registrados em log.
 */

#include <stdio.h>
#include "memoria.h"
#include "alocacao.h"
#include "log.h"

/**
 * @brief Função principal do simulador de memória.
 *
 * Este programa realiza as seguintes ações:
 * - Inicializa toda a memória como livre.
 * - Executa alocações usando as estratégias First Fit, Best Fit e Worst Fit.
 * - Libera blocos previamente alocados.
 * - Realiza compactação da memória após a liberação.
 * - Verifica o sucesso de cada alocação e registra falhas no log.
 * - Imprime o estado atual da memória no terminal.
 * - Salva o estado da memória em um arquivo de texto.
 *
 * Estratégias testadas:
 * - First Fit: processos 1, 2 e 3
 * - Best Fit: processo 4 (PID 1 reutilizado apenas para teste)
 * - Compactação: após liberação de memória
 * - Worst Fit: processo 6
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

    // Tenta alocar 10 blocos para o processo 4 usando Best Fit
    // (Reutiliza PID 1 apenas para forçar teste de falha)
    if (!best_fit(1, 10))
        log_erro(4, "Best Fit", "nenhum bloco adequado encontrado");

    // Compacta a memória após liberações para reduzir fragmentação externa
    compactar_memoria();

    // Tenta alocar 8 blocos para o processo 6 usando Worst Fit
    if (!worst_fit(6, 8))
        log_erro(6, "Worst Fit", "nenhum bloco suficientemente grande encontrado");

    // Exibe o estado atual da memória no terminal
    imprimir_memoria();

    // Salva o estado da memória em arquivo para futura análise
    salvar_memoria("estado.txt");

    return 0;
}
