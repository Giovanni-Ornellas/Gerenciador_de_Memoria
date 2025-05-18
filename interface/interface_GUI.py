import tkinter as tk
import tkinter.messagebox as msgbox
import os
import subprocess

# Configurações
TAM_MEMORIA = 100
COLUNAS = 20
DIR_BASE = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "build"))
ARQUIVO_ESTADO = os.path.join(DIR_BASE, "estado.txt")
ARQUIVO_COMANDO = os.path.join(DIR_BASE, "comando.txt")
BIN_PROCESSADOR = os.path.join(DIR_BASE, "processador")

# Cores por PID
CORES = [
    "#D0D0D0", "#4DA6FF", "#5CD65C", "#FFD633", "#FF6666",
    "#CC99FF", "#66CCCC", "#A0A0A0"
]

def mostrar_erro(mensagem):
    """Exibe um erro visual na interface."""
    msgbox.showerror("Erro", mensagem)

def carregar_estado():
    """Lê estado.txt e retorna vetor de memória."""
    if not os.path.exists(ARQUIVO_ESTADO):
        return [0] * TAM_MEMORIA
    with open(ARQUIVO_ESTADO) as f:
        blocos = list(map(int, f.read().split()))
    return blocos + [0] * (TAM_MEMORIA - len(blocos))

def escrever_comando(comando):
    """Escreve uma instrução no comando.txt (a ser lida pelo programa C)."""
    with open(ARQUIVO_COMANDO, "w") as f:
        f.write(comando.strip() + "\n")

def desenhar_memoria(memoria):
    """Desenha blocos proporcionalmente ao tamanho da janela."""
    canvas.delete("all")

    largura = canvas.winfo_width()
    altura = canvas.winfo_height()

    tam_bloco_x = largura / COLUNAS
    linhas = TAM_MEMORIA // COLUNAS
    tam_bloco_y = altura / linhas

    for i, bloco in enumerate(memoria):
        linha = i // COLUNAS
        coluna = i % COLUNAS
        x1 = coluna * tam_bloco_x
        y1 = linha * tam_bloco_y
        x2 = x1 + tam_bloco_x
        y2 = y1 + tam_bloco_y

        cor = CORES[bloco] if bloco < len(CORES) else "#888888"
        canvas.create_rectangle(x1, y1, x2, y2, fill=cor, outline="black")

        if bloco != 0:
            canvas.create_text((x1 + x2) / 2, (y1 + y2) / 2, text=str(bloco), font=("Arial", int(tam_bloco_y / 2)))

def calcular_fragmentacao(memoria):
    """Calcula estatísticas de fragmentação externa."""
    total_livres = memoria.count(0)
    atual = 0
    tamanhos = []

    for bloco in memoria:
        if bloco == 0:
            atual += 1
        else:
            if atual > 0:
                tamanhos.append(atual)
                atual = 0
    if atual > 0:
        tamanhos.append(atual)

    num_regioes = len(tamanhos)
    maior = max(tamanhos) if tamanhos else 0
    menor = min(tamanhos) if tamanhos else 0
    tem_fragmentacao = num_regioes > 1

    return {
        "livres": total_livres,
        "regioes": num_regioes,
        "maior": maior,
        "menor": menor,
        "fragmentado": tem_fragmentacao
    }

def atualizar():
    """Atualiza a visualização da memória e a exibição de fragmentação."""
    memoria = carregar_estado()
    desenhar_memoria(memoria)

    frag = calcular_fragmentacao(memoria)
    texto_frag = (
        f"Blocos Livres: {frag['livres']}\n"
        f"Regiões Livres: {frag['regioes']}\n"
        f"Maior Região: {frag['maior']} blocos\n"
        f"Menor Região: {frag['menor']} blocos\n"
        f"Fragmentação Externa: {'SIM' if frag['fragmentado'] else 'NÃO'}"
    )
    label_fragmentacao.config(text=texto_frag)

    root.after(1000, atualizar)

def alocar():
    """Cria um comando de alocação e executa o processador."""
    pid = entry_pid.get()
    tamanho = entry_tamanho.get()
    algoritmo = var_algoritmo.get()
    if pid.isdigit() and tamanho.isdigit():
        comando = f"alocar {pid} {tamanho} {algoritmo}"
        escrever_comando(comando)
        result = subprocess.run(
            [BIN_PROCESSADOR, ARQUIVO_COMANDO, ARQUIVO_ESTADO],
            capture_output=True, text=True
        )
        if "Erro" in result.stdout or "Erro" in result.stderr:
            mensagem = result.stdout.strip() or result.stderr.strip()
            mostrar_erro(mensagem)
    else:
        mostrar_erro("PID e Tamanho devem ser números inteiros.")

def liberar():
    """Cria um comando de liberação e executa o processador."""
    pid = entry_pid.get()
    if pid.isdigit():
        comando = f"liberar {pid}"
        escrever_comando(comando)
        subprocess.run([BIN_PROCESSADOR, ARQUIVO_COMANDO, ARQUIVO_ESTADO])
    else:
        mostrar_erro("PID inválido. Digite um número inteiro.")

# === GUI principal ===
root = tk.Tk()
root.title("Simulador de Memória - Interativo")
root.geometry("800x600")
root.minsize(600, 400)
root.columnconfigure(0, weight=1)
root.rowconfigure(1, weight=1)

# === Controles superiores ===
frame_controle = tk.Frame(root)
frame_controle.grid(row=0, column=0, pady=10)

tk.Label(frame_controle, text="PID:").grid(row=0, column=0)
entry_pid = tk.Entry(frame_controle, width=5)
entry_pid.grid(row=0, column=1, padx=(0, 10))

tk.Label(frame_controle, text="Tamanho:").grid(row=0, column=2)
entry_tamanho = tk.Entry(frame_controle, width=5)
entry_tamanho.grid(row=0, column=3, padx=(0, 20))

var_algoritmo = tk.StringVar(value="first")
tk.Radiobutton(frame_controle, text="First Fit", variable=var_algoritmo, value="first").grid(row=0, column=4)
tk.Radiobutton(frame_controle, text="Best Fit", variable=var_algoritmo, value="best").grid(row=0, column=5)
tk.Radiobutton(frame_controle, text="Worst Fit", variable=var_algoritmo, value="worst").grid(row=0, column=6)

tk.Button(frame_controle, text="Alocar", width=10, command=alocar).grid(row=0, column=7, padx=10)
tk.Button(frame_controle, text="Liberar", width=10, command=liberar).grid(row=0, column=8)

# === Visualização da memória (expansível) ===
frame_memoria = tk.Frame(root)
frame_memoria.grid(row=1, column=0, sticky="nsew", padx=10)

canvas = tk.Canvas(frame_memoria, bg="white", bd=1, relief="solid")
canvas.grid(row=0, column=0, sticky="nsew")
frame_memoria.grid_rowconfigure(0, weight=1)
frame_memoria.grid_columnconfigure(0, weight=1)

# === Fragmentação ===
frame_info = tk.Frame(root)
frame_info.grid(row=2, column=0, pady=(10, 20))
label_fragmentacao = tk.Label(frame_info, text="", font=("Arial", 10), justify="left")
label_fragmentacao.pack()

# Atualização contínua
atualizar()
root.mainloop()
