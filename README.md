# Simulador de Gerenciador de Memória

## 📍 Descrição do Projeto

Este projeto simula um **gerenciador de memória contígua**, como é ensinado na disciplina de Arquitetura e Organização de Computadores. A ideia é mostrar, de forma prática, como diferentes estratégias de alocação de memória funcionam — com foco especial em **fragmentação**, **alocação** e **registro de falhas**.

A memória é simulada como um vetor fixo e os processos são alocados (ou não) dependendo da política de alocação utilizada.

---

## 🧩 O que é Alocação Contígua?

Na alocação contígua, cada processo precisa ser alocado em **um único bloco contínuo de memória**. Ou seja, se um processo precisa de 10 posições, ele só pode ser inserido onde houver **10 blocos livres consecutivos**.

### ✴️ Características:
- Simples de implementar
- Eficiência razoável em sistemas pequenos
- Pode causar **fragmentação externa**
- Necessita de estratégias para decidir **onde alocar** (caso haja vários blocos livres)

---

## ✅ O que foi implementado até agora

### 🔹 Estrutura de Memória
- Vetor de inteiros com tamanho fixo (`TAM_MEMORIA`)
- Cada posição representa um bloco de memória:
  - `0` = livre
  - `N` = ocupado por processo de PID `N`

### 🔹 Estratégias de Alocação Contígua

| Estratégia   | Descrição |
|--------------|-----------|
| **First Fit** | Aloca no primeiro espaço livre que couber |
| **Best Fit**  | Aloca no menor espaço livre suficiente |
| **Worst Fit** | Aloca no maior espaço livre disponível |

### 🔹 Funções principais
- `alocar_memoria(pid, tamanho)` com a estratégia desejada
- `liberar_memoria(pid)`
- `imprimir_memoria()` no terminal
- `salvar_memoria("estado.txt")`
- `log_erro(pid, metodo, motivo)` para registrar falhas em `log.txt`

### 🔹 Testes de falha
- Simulações com **fragmentação externa** para mostrar onde Best Fit ou Worst Fit falham mesmo com espaço total suficiente.

---

## 🧪 Exemplos de uso no `main.c`

```c
first_fit(1, 10);      // tenta alocar 10 blocos
liberar_memoria(1);    // libera blocos do processo 1
best_fit(4, 7);        // tenta alocar 7 blocos no menor espaço
worst_fit(6, 8);       // tenta alocar 8 blocos no maior espaço
