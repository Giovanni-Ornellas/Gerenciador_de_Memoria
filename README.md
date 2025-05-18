## Simulador de Gerenciamento de Memória – Alocação Contígua

Este projeto é um **simulador educacional de gerenciamento de memória**, com foco em **alocação contígua sequencial**. Ele permite visualizar de forma interativa como blocos de memória são alocados e liberados por diferentes algoritmos, e como isso afeta a **fragmentação externa** do sistema.

---

### 🔍 Funcionalidades

* Interface gráfica (GUI) com **visualização em tempo real**
* Suporte a três algoritmos:

  * **First Fit**
  * **Best Fit**
  * **Worst Fit**
* Simulação da memória como uma grade de blocos
* Cálculo automático e exibição de:
  * Blocos livres
  * Regiões livres
  * Tamanho da maior e menor região
  * **Fragmentação externa**
* Prevenção de alocação duplicada para o mesmo processo (PID)
* Mensagens de erro claras diretamente na interface

---

### 💻 Tecnologias Utilizadas

| Componente       | Tecnologia         |
| ---------------- | ------------------ |
| Backend (lógica) | C (GCC)            |
| Frontend (GUI)   | Python 3 + Tkinter |
| Comunicação      | Arquivos (`.txt`)  |
| Build            | Makefile           |

---

### 🛠️ Como executar

```bash
make
```

> Isso compila o código C e abre a interface gráfica automaticamente.

---

### 📁 Estrutura

```
Gerenciador_de_Memoria/
├── build/                # Arquivos gerados (binário, estado.txt, comando.txt)
├── include/              # Headers (.h)
├── interface/            # Interface gráfica em Python
├── src/                  # Código-fonte em C
├── Makefile              # Build automatizado
└── README.md             # Este documento
```

---

### 🧪 Exemplo de uso

1. Escolha um **PID** e **tamanho**
2. Selecione o algoritmo desejado
3. Clique em **Alocar** para reservar memória
4. Clique em **Liberar** para liberar um PID existente
5. Acompanhe os efeitos diretamente no painel da memória e na fragmentação

---

### 🎓 Objetivo pedagógico

Este simulador foi desenvolvido como parte do estudo prático da disciplina de **Arquitetura de Computadores**, com foco no comportamento e nas limitações da **alocação contígua de memória**.

---

### ✍️ Autor

Giovanni Anselmo Fernandes Coelho de Ornellas

---
