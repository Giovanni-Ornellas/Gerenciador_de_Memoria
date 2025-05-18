/**
 * @file memoria.h
 * @brief Declarações das funções e variáveis para simular a memória de um sistema operacional.
 *
 * Este módulo define a estrutura e operações básicas para um simulador
 * de gerenciamento de memória, incluindo inicialização, liberação,
 * visualização e salvamento do estado da memória.
 */

#ifndef MEMORIA_H
#define MEMORIA_H

/// Tamanho total da memória simulada (em unidades)
#define TAM_MEMORIA 100

/**
 * @brief Vetor que representa a memória principal do sistema.
 *
 * Cada posição do vetor representa um bloco de memória:
 * - 0: bloco livre
 * - >0: bloco ocupado por um processo identificado pelo seu PID.
 */
extern int memoria[TAM_MEMORIA];

/**
 * @brief Inicializa a memória, marcando todos os blocos como livres.
 */
void inicializar_memoria();

/**
 * @brief Libera todos os blocos de memória ocupados por um processo.
 * @param pid Identificador do processo cuja memória será liberada.
 */
void liberar_memoria(int pid);

/**
 * @brief Imprime o estado atual da memória no terminal.
 *
 * Útil para fins de depuração e visualização textual da memória.
 */
void imprimir_memoria();

/**
 * @brief Salva o estado atual da memória em um arquivo texto.
 *
 * O formato é uma sequência de inteiros separados por espaço, representando cada bloco.
 *
 * @param arquivo Nome do arquivo onde o estado será salvo.
 */
void salvar_memoria(const char *arquivo);

/**
 * @brief Compacta a memória movendo todos os blocos ocupados para o início.
 *
 * Esta função reorganiza a memória simulada de forma que todos os blocos usados
 * por processos sejam deslocados para o início do vetor de memória, enquanto os 
 * blocos livres (representados por 0) são deslocados para o final.
 *
 * Seu principal objetivo é reduzir a fragmentação externa, criando um bloco 
 * contíguo maior de memória livre para facilitar futuras alocações.
 *
 * @note Esta operação não preserva a posição original dos processos na memória.
 */
void compactar_memoria();

#endif // MEMORIA_H
