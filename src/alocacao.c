#include "../include/memoria.h"

/**
 * @brief Realiza a alocação de memória utilizando a estratégia First Fit.
 *
 * Procura o primeiro bloco contíguo de memória livre que seja suficientemente
 * grande para alocar a quantidade de posições solicitadas.
 *
 * @param pid Identificador do processo que requisita a alocação.
 * @param tamanho Número de posições de memória a serem alocadas.
 *
 * @return int
 * - 1 se a alocação for bem-sucedida.
 * - 0 se não houver espaço suficiente disponível.
 *
 * A função percorre a memória linearmente e aloca o primeiro bloco contíguo 
 * de tamanho suficiente. Caso não encontre, retorna falha.
 */
int first_fit(int pid, int tamanho) {
    int livres = 0, inicio = -1;

    for (int i = 0; i < TAM_MEMORIA; i++) {
        // Verifica se o bloco está livre
        if (memoria[i] == 0) {
            if (livres == 0) inicio = i; // marca o início do bloco livre
            livres++;

            // Se o número de blocos livres atingiu o necessário
            if (livres == tamanho) {
                // Aloca o bloco para o processo
                for (int j = inicio; j < inicio + tamanho; j++)
                    memoria[j] = pid;
                return 1; // sucesso
            }
        } else {
            // Bloco ocupado, reinicia a contagem
            livres = 0;
            inicio = -1;
        }
    }

    return 0; // falha na alocação
}

/**
 * @brief Aloca memória usando a estratégia Best Fit.
 *
 * Procura o menor bloco livre contíguo que seja suficiente para o processo.
 *
 * @param pid ID do processo a ser alocado.
 * @param tamanho Tamanho necessário em blocos.
 * @return 1 se alocou com sucesso, 0 se falhou.
 */
int best_fit(int pid, int tamanho) {
    int melhor_inicio = -1;
    int melhor_tamanho = TAM_MEMORIA + 1;

    int i = 0;
    while (i < TAM_MEMORIA) {
        // Encontrar início de um bloco livre
        if (memoria[i] == 0) {
            int inicio = i;
            int livres = 0;

            // Contar tamanho do bloco livre
            while (i < TAM_MEMORIA && memoria[i] == 0) {
                livres++;
                i++;
            }

            // Se couber e for o melhor até agora
            if (livres >= tamanho && livres < melhor_tamanho) {
                melhor_inicio = inicio;
                melhor_tamanho = livres;
            }
        } else {
            i++;
        }
    }

    // Aloca no melhor bloco encontrado
    if (melhor_inicio != -1) {
        for (int j = melhor_inicio; j < melhor_inicio + tamanho; j++) {
            memoria[j] = pid;
        }
        return 1;
    }

    return 0;
}

/**
 * @brief Aloca memória usando a estratégia Worst Fit.
 *
 * Procura o maior bloco livre contíguo que seja suficiente para o processo.
 *
 * @param pid ID do processo a ser alocado.
 * @param tamanho Tamanho necessário em blocos.
 * @return 1 se alocou com sucesso, 0 se falhou.
 */
int worst_fit(int pid, int tamanho) {
    int pior_inicio = -1;
    int pior_tamanho = -1;

    int i = 0;
    while (i < TAM_MEMORIA) {
        if (memoria[i] == 0) {
            int inicio = i;
            int livres = 0;

            while (i < TAM_MEMORIA && memoria[i] == 0) {
                livres++;
                i++;
            }

            // Se for suficiente e maior que o pior atual
            if (livres >= tamanho && livres > pior_tamanho) {
                pior_inicio = inicio;
                pior_tamanho = livres;
            }
        } else {
            i++;
        }
    }

    if (pior_inicio != -1) {
        for (int j = pior_inicio; j < pior_inicio + tamanho; j++) {
            memoria[j] = pid;
        }
        return 1;
    }

    return 0;
}