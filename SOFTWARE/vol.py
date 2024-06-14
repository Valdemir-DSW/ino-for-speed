import tkinter as tk
from tkinter import ttk
import random

# Faixas de valor para cada parâmetro
faixas_valores = {
    'MAP': (25, 35),
    'Tempo de Injeção': (10, 20),
    'Posição do TPS': (50, 70),
    'Temperatura do Refrigerante': (80, 100),
    'Lambda AFR': (0.80, 0.90),
    'Fator de Trabalho': (50, 70),
    'Tensão da Bateria': (12.0, 13.0)
}

# Valores iniciais de máximo e mínimo
valores_maximos = {parametro: -float('inf') for parametro in faixas_valores}
valores_minimos = {parametro: float('inf') for parametro in faixas_valores}

# Função para gerar valores aleatórios dentro das faixas definidas
def gerar_valores():
    valores = {}
    for parametro, faixa in faixas_valores.items():
        valor = round(random.uniform(faixa[0], faixa[1]), 2)
        valores[parametro] = valor
        # Atualizar máximo e mínimo
        valores_maximos[parametro] = max(valores_maximos[parametro], valor)
        valores_minimos[parametro] = min(valores_minimos[parametro], valor)
    return valores

# Função para atualizar o gráfico
def atualizar_grafico():
    valores = gerar_valores()

    # Atualizar os widgets existentes
    progress_bar_MAP.configure(value=valores['MAP'])
    label_valor_MAP.configure(text=str(valores['MAP']))
    label_maximo_MAP.configure(text=f'Máx: {valores_maximos["MAP"]}')
    label_minimo_MAP.configure(text=f'Mín: {valores_minimos["MAP"]}')

    progress_bar_tempo.configure(value=valores['Tempo de Injeção'])
    label_valor_tempo.configure(text=str(valores['Tempo de Injeção']))
    label_maximo_tempo.configure(text=f'Máx: {valores_maximos["Tempo de Injeção"]}')
    label_minimo_tempo.configure(text=f'Mín: {valores_minimos["Tempo de Injeção"]}')

    progress_bar_TPS.configure(value=valores['Posição do TPS'])
    label_valor_TPS.configure(text=str(valores['Posição do TPS']))
    label_maximo_TPS.configure(text=f'Máx: {valores_maximos["Posição do TPS"]}')
    label_minimo_TPS.configure(text=f'Mín: {valores_minimos["Posição do TPS"]}')

    progress_bar_temperatura.configure(value=valores['Temperatura do Refrigerante'])
    label_valor_temperatura.configure(text=str(valores['Temperatura do Refrigerante']))
    label_maximo_temperatura.configure(text=f'Máx: {valores_maximos["Temperatura do Refrigerante"]}')
    label_minimo_temperatura.configure(text=f'Mín: {valores_minimos["Temperatura do Refrigerante"]}')

    progress_bar_lambda.configure(value=valores['Lambda AFR'])
    label_valor_lambda.configure(text=str(valores['Lambda AFR']))
    label_maximo_lambda.configure(text=f'Máx: {valores_maximos["Lambda AFR"]}')
    label_minimo_lambda.configure(text=f'Mín: {valores_minimos["Lambda AFR"]}')

    progress_bar_fator.configure(value=valores['Fator de Trabalho'])
    label_valor_fator.configure(text=str(valores['Fator de Trabalho']))
    label_maximo_fator.configure(text=f'Máx: {valores_maximos["Fator de Trabalho"]}')
    label_minimo_fator.configure(text=f'Mín: {valores_minimos["Fator de Trabalho"]}')

    progress_bar_bateria.configure(value=valores['Tensão da Bateria'])
    label_valor_bateria.configure(text=str(valores['Tensão da Bateria']))
    label_maximo_bateria.configure(text=f'Máx: {valores_maximos["Tensão da Bateria"]}')
    label_minimo_bateria.configure(text=f'Mín: {valores_minimos["Tensão da Bateria"]}')

    # Atualizar a cada 1 segundo
    root.after(1000, atualizar_grafico)

# Criando a janela principal
root = tk.Tk()
root.title('Parâmetros da Injeção Eletrônica')


# Estilo para as Progressbars
s = ttk.Style()
s.configure('yellow.Horizontal.TProgressbar', foreground='yellow', background='yellow')
s.configure('red.Horizontal.TProgressbar', foreground='red', background='red')
s.configure('green.Horizontal.TProgressbar', foreground='green', background='green')

# Criando e posicionando os widgets
ttk.Label(root, text='MAP').place(x=100,y=200)
mapscale = ttk.Label(root, text='0          12,5           25        50        75        100').place(x=14,y=224)
progress_bar_MAP = ttk.Progressbar(root, orient='horizontal', length=200, mode='determinate', maximum=100)
progress_bar_MAP.place(x=14,y=244)
label_valor_MAP = ttk.Label(root, text='', width=5, anchor='e', background='white')
label_valor_MAP.place(x=224,y=244)
label_maximo_MAP = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_maximo_MAP.place(x=14,y=274)
label_minimo_MAP = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_minimo_MAP.place(x=154,y=274)

ttk.Label(root, text='Tempo de Injeção').grid(row=1, column=0, padx=10, pady=5)
progress_bar_tempo = ttk.Progressbar(root, orient='horizontal', length=200, mode='determinate', maximum=100)
progress_bar_tempo.grid(row=1, column=1, padx=10, pady=5)
label_valor_tempo = ttk.Label(root, text='', width=5, anchor='e', background='white')
label_valor_tempo.grid(row=1, column=2, padx=10, pady=5)
label_maximo_tempo = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_maximo_tempo.grid(row=1, column=3, padx=10, pady=5)
label_minimo_tempo = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_minimo_tempo.grid(row=1, column=4, padx=10, pady=5)

ttk.Label(root, text='Posição do TPS').grid(row=2, column=0, padx=10, pady=5)
progress_bar_TPS = ttk.Progressbar(root, orient='horizontal', length=200, mode='determinate', maximum=100)
progress_bar_TPS.grid(row=2, column=1, padx=10, pady=5)
label_valor_TPS = ttk.Label(root, text='', width=5, anchor='e', background='white')
label_valor_TPS.grid(row=2, column=2, padx=10, pady=5)
label_maximo_TPS = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_maximo_TPS.grid(row=2, column=3, padx=10, pady=5)
label_minimo_TPS = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_minimo_TPS.grid(row=2, column=4, padx=10, pady=5)

ttk.Label(root, text='Temperatura do Refrigerante').grid(row=3, column=0, padx=10, pady=5)
progress_bar_temperatura = ttk.Progressbar(root, orient='horizontal', length=200, mode='determinate', maximum=100)
progress_bar_temperatura.grid(row=3, column=1, padx=10, pady=5)
label_valor_temperatura = ttk.Label(root, text='', width=5, anchor='e', background='white')
label_valor_temperatura.grid(row=3, column=2, padx=10, pady=5)
label_maximo_temperatura = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_maximo_temperatura.grid(row=3, column=3, padx=10, pady=5)
label_minimo_temperatura = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_minimo_temperatura.grid(row=3, column=4, padx=10, pady=5)

ttk.Label(root, text='Lambda AFR').grid(row=4, column=0, padx=10, pady=5)
progress_bar_lambda = ttk.Progressbar(root, orient='horizontal', length=200, mode='determinate', maximum=100)
progress_bar_lambda.grid(row=4, column=1, padx=10, pady=5)
label_valor_lambda = ttk.Label(root, text='', width=5, anchor='e', background='white')
label_valor_lambda.grid(row=4, column=2, padx=10, pady=5)
label_maximo_lambda = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_maximo_lambda.grid(row=4, column=3, padx=10, pady=5)
label_minimo_lambda = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_minimo_lambda.grid(row=4, column=4, padx=10, pady=5)

ttk.Label(root, text='Fator de Trabalho').grid(row=5, column=0, padx=10, pady=5)
progress_bar_fator = ttk.Progressbar(root, orient='horizontal', length=200, mode='determinate', maximum=100)
progress_bar_fator.grid(row=5, column=1, padx=10, pady=5)
label_valor_fator = ttk.Label(root, text='', width=5, anchor='e', background='white')
label_valor_fator.grid(row=5, column=2, padx=10, pady=5)
label_maximo_fator = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_maximo_fator.grid(row=5, column=3, padx=10, pady=5)
label_minimo_fator = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_minimo_fator.grid(row=5, column=4, padx=10, pady=5)

ttk.Label(root, text='Tensão da Bateria').grid(row=6, column=0, padx=10, pady=5)
progress_bar_bateria = ttk.Progressbar(root, orient='horizontal', length=200, mode='determinate', maximum=100)
progress_bar_bateria.grid(row=6, column=1, padx=10, pady=5)
label_valor_bateria = ttk.Label(root, text='', width=5, anchor='e', background='white')
label_valor_bateria.grid(row=6, column=2, padx=10, pady=5)
label_maximo_bateria = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_maximo_bateria.grid(row=6, column=3, padx=10, pady=5)
label_minimo_bateria = ttk.Label(root, text='', width=8, anchor='e', background='white')
label_minimo_bateria.grid(row=6, column=4, padx=10, pady=5)

# Chamando a função para atualizar o gráfico
atualizar_grafico()

root.mainloop()
