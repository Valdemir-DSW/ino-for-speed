import tkinter as tk
from tkinter import ttk

class AplicativoInjecaoEletronica(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Injeção Eletrônica Programada")
        
        self.configure_gui()
        self.criar_abas()
    
    def configure_gui(self):
        self.geometry("800x600")
        self.grid_rowconfigure(0, weight=1)
        self.grid_columnconfigure(0, weight=1)
        
        self.notebook_frame = ttk.Frame(self)
        self.notebook_frame.grid(row=0, column=0, sticky="nsew")
        self.notebook_frame.grid_rowconfigure(0, weight=1)
        self.notebook_frame.grid_columnconfigure(0, weight=1)
        
        self.notebook = ttk.Notebook(self.notebook_frame)
        self.notebook.grid(row=0, column=0, sticky="nsew")
        
    def criar_abas(self):
        self.criar_aba_calibracao_tps()
        self.criar_aba_calibracao_lambda()
        self.criar_aba_calibracao_map()
        self.criar_aba_calibracao_roda_fonica()
    
    def criar_aba_calibracao_tps(self):
        aba_calibracao_tps = ttk.Frame(self.notebook)
        self.notebook.add(aba_calibracao_tps, text="Calibração TPS")
        
        label_min = tk.Label(aba_calibracao_tps, text="Valor Mínimo:")
        label_min.pack(padx=20, pady=10)
        entry_min = tk.Entry(aba_calibracao_tps)
        entry_min.pack(padx=20, pady=5)
        
        label_max = tk.Label(aba_calibracao_tps, text="Valor Máximo:")
        label_max.pack(padx=20, pady=10)
        entry_max = tk.Entry(aba_calibracao_tps)
        entry_max.pack(padx=20, pady=5)
        
        button_calibrate_tps = tk.Button(aba_calibracao_tps, text="Calibrar TPS")
        button_calibrate_tps.pack(padx=20, pady=20)
    
    def criar_aba_calibracao_lambda(self):
        aba_calibracao_lambda = ttk.Frame(self.notebook)
        self.notebook.add(aba_calibracao_lambda, text="Calibração Lambda")
        
        label_tipo_lambda = tk.Label(aba_calibracao_lambda, text="Tipo de Sonda Lambda:")
        label_tipo_lambda.pack(padx=20, pady=10)
        
        self.tipo_lambda = tk.StringVar()
        radio_banda_curta = tk.Radiobutton(aba_calibracao_lambda, text="Banda Curta", variable=self.tipo_lambda, value="curta", command=self.atualizar_opcoes_lambda)
        radio_banda_curta.pack(padx=20, pady=5)
        
        radio_banda_larga = tk.Radiobutton(aba_calibracao_lambda, text="Banda Larga", variable=self.tipo_lambda, value="larga", command=self.atualizar_opcoes_lambda)
        radio_banda_larga.pack(padx=20, pady=5)
        
        self.frame_opcoes_lambda = ttk.Frame(aba_calibracao_lambda)
        self.frame_opcoes_lambda.pack(padx=20, pady=10, fill=tk.BOTH, expand=True)
    
    def atualizar_opcoes_lambda(self):
        for widget in self.frame_opcoes_lambda.winfo_children():
            widget.destroy()
        
        if self.tipo_lambda.get() == "larga":
            label_auto_correcao = tk.Label(self.frame_opcoes_lambda, text="Correção Automática:")
            label_auto_correcao.pack(padx=20, pady=10)
            
            self.auto_correcao = tk.BooleanVar()
            check_auto_correcao = tk.Checkbutton(self.frame_opcoes_lambda, text="Habilitar Correção Automática", variable=self.auto_correcao)
            check_auto_correcao.pack(padx=20, pady=5)
            
            label_tempo_correcao = tk.Label(self.frame_opcoes_lambda, text="Tempo para Correção (ms):")
            label_tempo_correcao.pack(padx=20, pady=10)
            entry_tempo_correcao = tk.Entry(self.frame_opcoes_lambda)
            entry_tempo_correcao.pack(padx=20, pady=5)
    
    def criar_aba_calibracao_map(self):
        aba_calibracao_map = ttk.Frame(self.notebook)
        self.notebook.add(aba_calibracao_map, text="Calibração MAP")
        
        label_min = tk.Label(aba_calibracao_map, text="Valor Mínimo:")
        label_min.pack(padx=20, pady=10)
        entry_min = tk.Entry(aba_calibracao_map)
        entry_min.pack(padx=20, pady=5)
        
        label_max = tk.Label(aba_calibracao_map, text="Valor Máximo:")
        label_max.pack(padx=20, pady=10)
        entry_max = tk.Entry(aba_calibracao_map)
        entry_max.pack(padx=20, pady=5)
        
        button_calibrate_map = tk.Button(aba_calibracao_map, text="Calibrar MAP")
        button_calibrate_map.pack(padx=20, pady=20)
    
    def criar_aba_calibracao_roda_fonica(self):
        aba_calibracao_roda_fonica = ttk.Frame(self.notebook)
        self.notebook.add(aba_calibracao_roda_fonica, text="Calibração Roda Fônica")
        
        label_dentes = tk.Label(aba_calibracao_roda_fonica, text="Número de Dentes:")
        label_dentes.pack(padx=20, pady=10)
        slider_dentes = tk.Scale(aba_calibracao_roda_fonica, from_=10, to=100, orient=tk.HORIZONTAL)
        slider_dentes.pack(padx=20, pady=5)
        
        label_faltando = tk.Label(aba_calibracao_roda_fonica, text="Dentes Faltando:")
        label_faltando.pack(padx=20, pady=10)
        slider_faltando = tk.Scale(aba_calibracao_roda_fonica, from_=1, to=5, orient=tk.HORIZONTAL)
        slider_faltando.pack(padx=20, pady=5)
        
        label_graus = tk.Label(aba_calibracao_roda_fonica, text="Ponto em Graus:")
        label_graus.pack(padx=20, pady=10)
        entry_graus = tk.Entry(aba_calibracao_roda_fonica)
        entry_graus.pack(padx=20, pady=5)
        
        button_calibrate_roda_fonica = tk.Button(aba_calibracao_roda_fonica, text="Calibrar Roda Fônica")
        button_calibrate_roda_fonica.pack(padx=20, pady=20)

if __name__ == "__main__":
    app = AplicativoInjecaoEletronica()
    app.mainloop()
