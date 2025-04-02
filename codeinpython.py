import tkinter as tk
from tkinter import messagebox, simpledialog
import random

class Aluno:
    def __init__(self, nome, cpf, data_nascimento):
        self.nome = nome
        self.cpf = cpf
        self.data_nascimento = data_nascimento
        self.matricula = random.randint(100000, 999999)
        self.notas = [0.0, 0.0, 0.0]

alunos = []
usuarios = {"assistente": "assistente", "professor": "professor", "aluno": "aluno"}

# Função para login
def login():
    usuario = usuario_entry.get()
    senha = senha_entry.get()
    
    if usuario in usuarios and usuarios[usuario] == senha:
        messagebox.showinfo("Login", "Login bem-sucedido!")
        root.destroy()
        if usuario == "assistente":
            menu_admin()
        elif usuario == "professor":
            menu_professor()
        elif usuario == "aluno":
            menu_aluno()
    else:
        messagebox.showerror("Erro", "Login falhou. Tente novamente.")

# Função para matricular alunos
def matricular_aluno():
    nome = simpledialog.askstring("Matrícula", "Nome completo:")
    cpf = simpledialog.askstring("Matrícula", "CPF:")
    data_nascimento = simpledialog.askstring("Matrícula", "Data de Nascimento (DD/MM/AAAA):")
    
    if nome and cpf and data_nascimento:
        aluno = Aluno(nome, cpf, data_nascimento)
        alunos.append(aluno)
        messagebox.showinfo("Sucesso", f"Aluno matriculado! Matrícula: {aluno.matricula}")
    else:
        messagebox.showerror("Erro", "Todos os campos são obrigatórios!")

# Função para visualizar boletim
def boletim():
    matricula = simpledialog.askinteger("Boletim", "Digite o número de matrícula:")
    for aluno in alunos:
        if aluno.matricula == matricula:
            notas_str = "\n".join([f"Nota {i+1}: {nota}" for i, nota in enumerate(aluno.notas)])
            messagebox.showinfo("Boletim", f"Aluno: {aluno.nome}\n{notas_str}")
            return
    messagebox.showerror("Erro", "Aluno não encontrado!")

# Função para lançar notas
def lancar_notas():
    matricula = simpledialog.askinteger("Notas", "Digite o número de matrícula:")
    for aluno in alunos:
        if aluno.matricula == matricula:
            for i in range(3):
                aluno.notas[i] = simpledialog.askfloat("Notas", f"Digite a nota {i+1}:")
            messagebox.showinfo("Sucesso", "Notas lançadas com sucesso!")
            return
    messagebox.showerror("Erro", "Aluno não encontrado!")

# Menu do Assistente
def menu_admin():
    admin_window = tk.Tk()
    admin_window.title("Menu do Assistente")
    tk.Button(admin_window, text="Matricular Aluno", command=matricular_aluno).pack(pady=5)
    tk.Button(admin_window, text="Sair", command=admin_window.destroy).pack(pady=5)
    admin_window.mainloop()

# Menu do Professor
def menu_professor():
    prof_window = tk.Tk()
    prof_window.title("Menu do Professor")
    tk.Button(prof_window, text="Consultar Boletim", command=boletim).pack(pady=5)
    tk.Button(prof_window, text="Lançar Nota", command=lancar_notas).pack(pady=5)
    tk.Button(prof_window, text="Sair", command=prof_window.destroy).pack(pady=5)
    prof_window.mainloop()

# Menu do Aluno
def menu_aluno():
    aluno_window = tk.Tk()
    aluno_window.title("Menu do Aluno")
    tk.Button(aluno_window, text="Consultar Boletim", command=boletim).pack(pady=5)
    tk.Button(aluno_window, text="Sair", command=aluno_window.destroy).pack(pady=5)
    aluno_window.mainloop()

# Tela de login
root = tk.Tk()
root.title("Sistema Escolar")

frame = tk.Frame(root)
frame.pack(pady=20)

tk.Label(frame, text="Usuário:").grid(row=0, column=0)
usuario_entry = tk.Entry(frame)
usuario_entry.grid(row=0, column=1)

tk.Label(frame, text="Senha:").grid(row=1, column=0)
senha_entry = tk.Entry(frame, show="*")
senha_entry.grid(row=1, column=1)

tk.Button(frame, text="Login", command=login).grid(row=2, column=0, columnspan=2, pady=10)
root.mainloop()
