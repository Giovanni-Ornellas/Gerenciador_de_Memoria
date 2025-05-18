/**
 * @file processador.c
 * @brief Processador de comandos do simulador de Gerenciador de Memória.
 *
 * Este programa lê comandos de alocação e liberação de memória a partir de um
 * arquivo texto (`comando.txt`), executa as operações com base nas estratégias
 * definidas (First Fit, Best Fit, Worst Fit) e atualiza o estado da memória em
 * um arquivo de saída (`estado.txt`).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memoria.h"
#include "alocacao.h"

/**
 * @brief Lê e interpreta o comando no arquivo especificado.
 *
 * Os comandos suportados são:
 * - `alocar <pid> <tamanho> <algoritmo>` — aloca blocos para um processo usando a estratégia definida.
 * - `liberar <pid>` — libera todos os blocos ocupados por um processo.
 *
 * Se o PID já estiver presente na memória e for solicitada uma alocação,
 * o comando é ignorado com uma mensagem de erro.
 *
 * Exemplo de conteúdo do arquivo:
 * ```
 * alocar 3 12 best
 * liberar 3
 * ```
 *
 * @param arquivo_comando Caminho do arquivo contendo o comando a ser processado.
 */
void processar_comando(const char *arquivo_comando) {
    FILE *f = fopen(arquivo_comando, "r");
    if (!f) {
        perror("Erro ao abrir comando.txt");
        return;
    }

    char comando[16], algoritmo[16];
    int pid, tamanho;

    fscanf(f, "%s", comando);
    if (strcmp(comando, "alocar") == 0) {
        fscanf(f, "%d %d %s", &pid, &tamanho, algoritmo);

        if (pid_existe(pid)) {
            printf("Erro: processo %d já está alocado.\n", pid);
            fclose(f);
            return;
        }

        int sucesso = 0;
        if (strcmp(algoritmo, "first") == 0)
            sucesso = first_fit(pid, tamanho);
        else if (strcmp(algoritmo, "best") == 0)
            sucesso = best_fit(pid, tamanho);
        else if (strcmp(algoritmo, "worst") == 0)
            sucesso = worst_fit(pid, tamanho);

        if (!sucesso) {
            printf("Erro: Falha na alocação PID %d (%s fit)\n", pid, algoritmo);
        }

    } else if (strcmp(comando, "liberar") == 0) {
        fscanf(f, "%d", &pid);
        liberar_memoria(pid);
    }

    fclose(f);
}

/**
 * @brief Função principal do processador de comandos.
 *
 * Permite que os caminhos dos arquivos `comando.txt` e `estado.txt` sejam
 * passados como argumentos na linha de comando. Se não forem informados,
 * valores padrão serão usados.
 *
 * @param argc Número de argumentos.
 * @param argv Vetor de argumentos.
 * @return int Retorna 0 em caso de execução bem-sucedida.
 */
int main(int argc, char *argv[]) {
    const char *arquivo_comando = (argc > 1) ? argv[1] : "comando.txt";
    const char *arquivo_estado  = (argc > 2) ? argv[2] : "estado.txt";

    carregar_memoria(arquivo_estado);
    processar_comando(arquivo_comando);
    salvar_memoria(arquivo_estado);

    return 0;
}

