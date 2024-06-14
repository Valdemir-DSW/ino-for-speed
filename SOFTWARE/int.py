import tkinter as tk
from tkinter import ttk, messagebox, filedialog
import os
import datetime
import shutil
import json
from tkinter import PhotoImage
from itertools import cycle
from PIL import Image, ImageTk



# Diretório onde os projetos serão armazenados
projetos_dir = "projetos"
fusil_filename = "config.fuzil"
verçaodoapp = 444
redistri = 0
def escrever_diretorio_projetos(diretorio):
    with open(fusil_filename, "w") as file:
        file.write(diretorio)

def verificar_nome_projeto(nome_projeto):
    projetos_existentes = carregar_projetos_existentes()
    for projeto in projetos_existentes:
        if projeto["nome"] == nome_projeto:
            return True
    return False


def show_splash_screen():
        
        
    roots = tk.Tk()
    roots.overrideredirect(True)
    roots.geometry("+154+144")  # Posição da tela de splash na tela
    image = PhotoImage(file="splach.png")
    label = tk.Label(roots, image=image)
    label.pack()
    roots.after(3000,roots.destroy )  # Fechar a tela de splash após 3 segundos
    roots.mainloop()
show_splash_screen()
# Função para validar os dados do projeto
def validar_dados(nome_projeto, num_cilindros, rpm_min, rpm_max):
    if not nome_projeto:
        messagebox.showerror("Erro de Validação", "O nome do projeto não pode estar vazio.")
        return False
    
    if not (1 <= num_cilindros <= 8):
        messagebox.showerror("Erro de Validação", "Número de cilindros deve estar entre 1 e 8.")
        return False
    
    if not (500 <= rpm_min <= 2000):
        messagebox.showerror("Erro de Validação", "RPM mínima deve estar entre 500 e 2000.")
        return False
    
    if not (2010 <= rpm_max <= 10000):
        messagebox.showerror("Erro de Validação", "RPM máxima deve estar entre 2010 e 10000.")
        return False
    
    return True

# Função para criar um novo projeto
def criar_projeto():
    def salvar_projeto():
        nome_projeto = nome_var.get().strip()
        num_cilindros = cilindros_slider.get()
        modo_injecao = injecao_var.get()
        modo_ignicao = ignicao_var.get()
        turbo = turbo_var.get()
        rpm_min = rpm_min_slider.get()
        rpm_max = rpm_max_slider.get()
        padrao_medicao = medicao_var.get()
        
        if validar_dados(nome_projeto, num_cilindros, rpm_min, rpm_max):
            if verificar_nome_projeto(nome_projeto):
                messagebox.showerror("Erro", "Já existe um projeto com esse nome.")
            else:
                projeto = {
                    "Cilindros": num_cilindros,
                    "Injeção": modo_injecao,
                    "Ignição": modo_ignicao,
                    "Turbo": turbo,
                    "RPM Mínima": rpm_min,
                    "RPM Máxima": rpm_max,
                    "Padrão de Medição": padrao_medicao
                }
                salvar_projeto_em_arquivo(nome_projeto, projeto)
                atualizar_lista_projetos()
                form_projeto.destroy()

    
    form_projeto = tk.Toplevel(root)
    form_projeto.title("Novo Projeto")
    form_projeto.iconbitmap(os.path.abspath("ico.ico"))
    form_projeto.resizable(False,False)
    tk.Label(form_projeto, text="Nome do Projeto:").grid(row=0, column=0, padx=10, pady=5)
    nome_var = tk.StringVar(value="Meu-fuca")
    tk.Entry(form_projeto, textvariable=nome_var).grid(row=0, column=1, padx=10, pady=5)
    
    tk.Label(form_projeto, text="Número de Cilindros:").grid(row=1, column=0, padx=10, pady=5)
    cilindros_slider = tk.Scale(form_projeto, from_=1, to=8, orient=tk.HORIZONTAL)
    cilindros_slider.grid(row=1, column=1, padx=10, pady=5)
    
    tk.Label(form_projeto, text="Modo de Injeção:").grid(row=2, column=0, padx=10, pady=5)
    injecao_var = tk.StringVar()
    tk.Entry(form_projeto, textvariable=injecao_var).grid(row=2, column=1, padx=10, pady=5)
    
    tk.Label(form_projeto, text="Modo de Ignição:").grid(row=3, column=0, padx=10, pady=5)
    ignicao_var = tk.StringVar()
    tk.Entry(form_projeto, textvariable=ignicao_var).grid(row=3, column=1, padx=10, pady=5)
    
    tk.Label(form_projeto, text="Turbo (Sim/Não):").grid(row=4, column=0, padx=10, pady=5)
    turbo_var = tk.StringVar()
    turbo_combobox = ttk.Combobox(form_projeto, textvariable=turbo_var, values=["Sim", "Não"])
    turbo_combobox.grid(row=4, column=1, padx=10, pady=5)
    turbo_combobox.current(0)
    
    tk.Label(form_projeto, text="RPM Mínima:").grid(row=5, column=0, padx=10, pady=5)
    rpm_min_slider = tk.Scale(form_projeto, from_=500, to=2000, orient=tk.HORIZONTAL)
    rpm_min_slider.grid(row=5, column=1, padx=10, pady=5)
    
    tk.Label(form_projeto, text="RPM Máxima:").grid(row=6, column=0, padx=10, pady=5)
    rpm_max_slider = tk.Scale(form_projeto, from_=2010, to=10000, orient=tk.HORIZONTAL)
    rpm_max_slider.grid(row=6, column=1, padx=10, pady=5)
    
    tk.Label(form_projeto, text="Padrão de Medição:").grid(row=7, column=0, padx=10, pady=5)
    medicao_var = tk.StringVar()
    medicao_combobox = ttk.Combobox(form_projeto, textvariable=medicao_var, values=["Imperial", "Métrico"])
    medicao_combobox.grid(row=7, column=1, padx=10, pady=5)
    medicao_combobox.current(0)
    
    tk.Button(form_projeto, text="Salvar", command=salvar_projeto).grid(row=8, columnspan=2, pady=10)

# Função para salvar o projeto em um arquivo JSON
def salvar_projeto_em_arquivo(nome_projeto, projeto):
    projeto_path = os.path.join(projetos_dir, nome_projeto)
    if not os.path.exists(projetos_dir):
        os.makedirs(projetos_dir)
    if not os.path.exists(projeto_path):
        os.makedirs(projeto_path)
    
    with open(os.path.join(projeto_path, "projeto.json"), "w") as file:
        json.dump(projeto, file, indent=4)

# Função para carregar os projetos existentes
def carregar_projetos_existentes():
    if not os.path.exists(projetos_dir):
        return []
    projetos = []
    for nome_projeto in os.listdir(projetos_dir):
        projeto_path = os.path.join(projetos_dir, nome_projeto, "projeto.json")
        escrever_diretorio_projetos(projeto_path)
        if os.path.isfile(projeto_path):
            with open(projeto_path, "r") as file:
                projeto = json.load(file)
                projeto["nome"] = nome_projeto
                projetos.append(projeto)
    return projetos

# Função para atualizar a lista de projetos na interface
def atualizar_lista_projetos():
    lista_projetos.delete(0, tk.END)
    for projeto in carregar_projetos_existentes():
        lista_projetos.insert(tk.END, f"{projeto['nome']} - {projeto['Cilindros']} cilindros")

# Função para exportar um projeto
def exportar_projeto():
    projeto_selecionado = lista_projetos.curselection()
    if not projeto_selecionado:
        messagebox.showwarning("Atenção", "Nenhum projeto selecionado.")
        return
    index = projeto_selecionado[0]
    projeto = carregar_projetos_existentes()[index]
    projeto_path = os.path.join(projetos_dir, projeto["nome"])
    
    dir_path = filedialog.askdirectory()
    if dir_path:
        shutil.copytree(projeto_path, os.path.join(dir_path, projeto["nome"]))
        messagebox.showinfo("Sucesso", "Projeto exportado com sucesso.")
# Função para importar um projeto
def importar_projeto():
    dir_path = filedialog.askdirectory()
    if dir_path:
        nome_projeto = os.path.basename(dir_path)
        destino_path = os.path.join(projetos_dir, nome_projeto)
        if not os.path.exists(destino_path):
            shutil.copytree(dir_path, destino_path)
            atualizar_lista_projetos()
            messagebox.showinfo("Sucesso", "Projeto importado com sucesso.")
        else:
            # Obter a hora atual sem formatação para usar como sufixo
            hora_atual = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
            novo_nome_projeto = f"{nome_projeto}-{hora_atual}"
            shutil.copytree(dir_path, os.path.join(projetos_dir, novo_nome_projeto))
            atualizar_lista_projetos()
            messagebox.showinfo("Sucesso", f"Projeto importado com sucesso com nome {novo_nome_projeto}.\nPor motivos de já ter outro com nomes iguais o projeto foi renomeado.")

def verificar_arquivo():
    if os.path.isfile("repas.json"):
        buttonv = tk.Button(root, text="Mais Informações", command=mostrar_mais_informacoes)
        buttonv.place(x=455,y=414)
        with open("repas.json", "r") as file:
            data = json.load(file)
            
            return f"Versão não oficial de ©Valdemir modificada por {data['modificador']}"
    else:
        return f"Versão {verçaodoapp} compilação oficial - ©Valdemir - dsw injection"

def mostrar_mais_informacoes():
    with open("repas.json", "r") as file:
        data = json.load(file)
       
    messagebox.showinfo("Sobre essa versão não oficial", f"Versão não oficial de ©Valdemir modificada por {data['modificador']} \nVersão Não oficial {data['versao']}\nEu {data['modificador']} Fiz as seguintes modificações\n>>>> {data['descricao']} \n\n\n\nEssa versão não tem nenhum suporte oficial de ninguém utilize com cautela.")

# Função para carregar um projeto selecionado e exibir os detalhes
def carregar_projeto():
    projeto_selecionado = lista_projetos.curselection()
    if not projeto_selecionado:
        messagebox.showwarning("Atenção", "Nenhum projeto selecionado.")
        return
    index = projeto_selecionado[0]
    projeto = carregar_projetos_existentes()[index]
    escrever_diretorio_projetos(os.path.join(projetos_dir, projeto["nome"]))
    
    detalhes = (
        f"Nome do Projeto: {projeto['nome']}\n"
        f"Número de Cilindros: {projeto['Cilindros']}\n"
        f"Modo de Injeção: {projeto['Injeção']}\n"
        f"Modo de Ignição: {projeto['Ignição']}\n"
        f"Turbo: {projeto['Turbo']}\n"
        f"RPM Mínima: {projeto['RPM Mínima']}\n"
        f"RPM Máxima: {projeto['RPM Máxima']}\n"
        f"Padrão de Medição: {projeto['Padrão de Medição']}"
    )
    messagebox.showinfo("Detalhes do Projeto", detalhes)

# Configuração da janela principal
root = tk.Tk()
root.title("DSW - ino for speed - Painel de Controle de Injeção Eletrônica")
root.resizable(False, False)
root.geometry("604x434")
style = ttk.Style()
style.theme_use('clam')
root.configure(bg='#f0f0f0')
root.iconbitmap(os.path.abspath("ico.ico"))
tk.Button(root, text="+ Criar Novo Projeto", command=criar_projeto).place(x=10,y=14)
tk.Button(root, text="Exportar Projeto", command=exportar_projeto).place(x=444,y=0)
tk.Button(root, text="Importar Projeto", command=importar_projeto).place(x=442,y=30)
tk.Button(root, text="Carregar Projeto", command=carregar_projeto).pack(pady=10)

lista_projetos = tk.Listbox(root, width=100)
lista_projetos.pack(pady=10)

atualizar_lista_projetos()

def exibir_imagens():
    # Caminho da pasta onde estão as imagens
    pasta_imagens = "imagems_int"

    # Lista para armazenar os caminhos das imagens
    caminhos_imagens = [os.path.join(pasta_imagens, nome_arquivo) for nome_arquivo in os.listdir(pasta_imagens)]

    imagens = [Image.open(caminho) for caminho in caminhos_imagens]
    ciclo_imagens = cycle(imagens)
    canvas_imagem = tk.Canvas(root, width=500, height=174)
    canvas_imagem.pack()
    imagem_atual = next(ciclo_imagens)
    foto = ImageTk.PhotoImage(imagem_atual)

    # Centralizando a imagem no canvas
    largura_canvas = 500
    altura_canvas = 174
    x_centro = largura_canvas / 2
    y_centro = altura_canvas / 2

    canvas_imagem.create_image(x_centro, y_centro, image=foto)
    canvas_imagem.foto = foto

    def atualizar_imagem():
        nonlocal imagem_atual
        imagem_atual = next(ciclo_imagens)
        nova_foto = ImageTk.PhotoImage(imagem_atual)
        canvas_imagem.create_image(x_centro, y_centro, image=nova_foto)
        canvas_imagem.foto = nova_foto
        root.after(4000, atualizar_imagem)

    root.after(4000, atualizar_imagem)
exibir_imagens()
labelv = tk.Label(root, text=verificar_arquivo())
labelv.place(x=114,y=414)



root.after(2444,root.mainloop() )
