/**
 * @file alocacao.h
 * @brief Declarações de funções relacionadas às estratégias de alocação de memória.
 *
 * Este arquivo define a interface para os algoritmos de alocação de memória,
 * começando com a estratégia First Fit. Outras estratégias como Best Fit e
 * Worst Fit podem ser adicionadas posteriormente.
 */

#ifndef ALOCACAO_H
#define ALOCACAO_H

/**
 * @brief Aloca memória utilizando a estratégia First Fit.
 *
 * Procura o primeiro bloco contíguo livre da memória que seja
 * grande o suficiente para armazenar o processo solicitado.
 *
 * @param pid O identificador do processo que está requisitando memória.
 * @param tamanho A quantidade de blocos (unidades) de memória a serem alocadas.
 * @return int Retorna 1 (sucesso) se a alocação for bem-sucedida, ou 0 (falha) se não houver espaço suficiente.
 */
int first_fit(int pid, int tamanho);

/**
 * @brief Aloca memória utilizando a estratégia Best Fit.
 *
 * Percorre toda a memória em busca do menor bloco livre contíguo
 * que seja suficientemente grande para acomodar o processo. Minimiza
 * o espaço desperdiçado, mas pode ser mais lento que First Fit.
 *
 * @param pid O identificador do processo que está requisitando memória.
 * @param tamanho A quantidade de blocos (unidades) de memória a serem alocadas.
 * @return int Retorna 1 (sucesso) se a alocação for bem-sucedida, ou 0 (falha) se não houver espaço suficiente.
 */
int best_fit(int pid, int tamanho);


/**
 * @brief Aloca memória utilizando a estratégia Worst Fit.
 *
 * Procura o maior bloco contíguo de memória livre que seja suficiente
 * para acomodar o processo. Se houver múltiplos blocos livres, escolhe
 * aquele com o maior tamanho possível.
 *
 * Essa estratégia busca minimizar a fragmentação externa ao deixar
 * blocos grandes de sobra para alocações futuras menores.
 *
 * @param pid O identificador do processo que será alocado.
 * @param tamanho O número de blocos de memória necessários para o processo.
 * @return int Retorna 1 se a alocação for bem-sucedida, ou 0 se não houver
 *             bloco suficientemente grande disponível.
 */
int worst_fit(int pid, int tamanho);


#endif // ALOCACAO_H
