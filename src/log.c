#include <stdio.h>
#include <time.h>
#include "../include/log.h"

/**
 * @brief Registra uma mensagem de erro de alocação em um arquivo de log.
 *
 * @param pid ID do processo que falhou.
 * @param metodo Nome do algoritmo de alocação (ex: "First Fit").
 * @param motivo Texto explicando a falha (ex: "memória insuficiente").
 */
void log_erro(int pid, const char *metodo, const char *motivo) {
    FILE *f = fopen("log.txt", "a");
    if (f == NULL) return;

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    char data[26];
    strftime(data, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(f, "[%s] ERRO: Processo %d | %s | Motivo: %s\n", data, pid, metodo, motivo);
    fclose(f);

    // Também mostra no terminal
    printf("[ERRO] Processo %d | %s | %s\n", pid, metodo, motivo);
}
