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

/**
 * @brief Compacta a memória, movendo todos os processos para o início.
 *
 * Blocos livres (0) são empurrados para o final do vetor.
 * Após a operação, todos os blocos ocupados ficam agrupados no início.
 */
void compactar_memoria() {
    int nova_memoria[TAM_MEMORIA];
    int k = 0;

    // Copia apenas blocos ocupados para o início do novo vetor
    for (int i = 0; i < TAM_MEMORIA; i++) {
        if (memoria[i] != 0) {
            nova_memoria[k++] = memoria[i];
        }
    }

    // Preenche o restante com 0 (livre)
    while (k < TAM_MEMORIA) {
        nova_memoria[k++] = 0;
    }

    // Atualiza a memória original
    for (int i = 0; i < TAM_MEMORIA; i++) {
        memoria[i] = nova_memoria[i];
    }
}

/**
 * @brief Exibe estatísticas sobre fragmentação externa na memória.
 *
 * Analisa quantas regiões livres existem, seu tamanho, e detecta
 * se a memória está fragmentada (vários espaços livres pequenos).
 */
void exibir_fragmentacao() {
    int total_livres = 0;
    int num_regioes = 0;
    int em_regiao = 0;
    int tam_regiao_atual = 0;
    int maior_regiao = 0;
    int menor_regiao = TAM_MEMORIA + 1;

    for (int i = 0; i < TAM_MEMORIA; i++) {
        if (memoria[i] == 0) {
            total_livres++;
            tam_regiao_atual++;
            if (!em_regiao) {
                em_regiao = 1;
                num_regioes++;
            }
        } else {
            if (em_regiao) {
                if (tam_regiao_atual > maior_regiao) maior_regiao = tam_regiao_atual;
                if (tam_regiao_atual < menor_regiao) menor_regiao = tam_regiao_atual;
                tam_regiao_atual = 0;
                em_regiao = 0;
            }
        }
    }

    // Se terminou em uma região livre, contabilizar a última
    if (em_regiao) {
        if (tam_regiao_atual > maior_regiao) maior_regiao = tam_regiao_atual;
        if (tam_regiao_atual < menor_regiao) menor_regiao = tam_regiao_atual;
    }

    printf("\n=== Fragmentação Externa ===\n");
    printf("Blocos livres totais: %d\n", total_livres);
    printf("Número de regiões livres: %d\n", num_regioes);
    if (num_regioes > 0) {
        printf("Maior região livre: %d blocos\n", maior_regiao);
        printf("Menor região livre: %d blocos\n", menor_regiao);
    }

    if (num_regioes > 1) {
        printf("Status: HÁ fragmentação externa.\n");
    } else {
        printf("Status: NÃO há fragmentação externa.\n");
    }
    printf("============================\n");
}

/**
 * @brief Carrega o estado da memória a partir de um arquivo texto.
 *
 * Cada linha (ou valor) no arquivo representa um bloco de memória:
 * - 0 = bloco livre
 * - >0 = PID do processo que ocupa o bloco
 *
 * Se o arquivo não existir, a memória permanece inalterada.
 *
 * @param arquivo Caminho para o arquivo contendo o estado salvo da memória.
 */
void carregar_memoria(const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (!f) return;

    for (int i = 0; i < TAM_MEMORIA && !feof(f); i++) {
        fscanf(f, "%d", &memoria[i]);
    }

    fclose(f);
}
/**
 * @brief Verifica se o PID já está presente na memória.
 * 
 * @param pid Identificador do processo.
 * @return int Retorna 1 se já existe, 0 se não.
 */
int pid_existe(int pid) {
    for (int i = 0; i < TAM_MEMORIA; i++) {
        if (memoria[i] == pid)
            return 1;
    }
    return 0;
}
