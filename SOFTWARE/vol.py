import tkinter as tk
from tkinter import ttk ,Menu,messagebox
import random
from PIL import Image, ImageTk
import os
import json
#from map_ve import PlanilhaInjecaoEletronica
import serial.tools.list_ports
import serial
import threading
ser = 0
def ino_map_value(x, in_min, in_max, out_min, out_max):
    try:
     return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min
    except:
        return 50
#Variáveis de monstra
map_value = 0
injection_time = 0
tps_position = 0
coolant_temp = 0
lambda_afr = 0
duty_cycle = 0
battery_voltage = 0
conexao_status = 0
errors = 0

#mi e max
max_map_value = float('-inf')
max_injection_time = float('-inf')
max_tps_position = float('-inf')
max_coolant_temp = float('-inf')
max_lambda_afr = float('-inf')
max_duty_cycle = float('-inf')
max_battery_voltage = float('-inf')

min_map_value = float('inf')
min_injection_time = float('inf')
min_tps_position = float('inf')
min_coolant_temp = float('inf')
min_lambda_afr = float('inf')
min_duty_cycle = float('inf')
min_battery_voltage = float('inf')
#
####
def monitor_values():
    global map_value, injection_time, tps_position, coolant_temp, lambda_afr, duty_cycle, battery_voltage
    global max_map_value, max_injection_time, max_tps_position, max_coolant_temp, max_lambda_afr, max_duty_cycle, max_battery_voltage
    global min_map_value, min_injection_time, min_tps_position, min_coolant_temp, min_lambda_afr, min_duty_cycle, min_battery_voltage

    
      

        # Atualiza os valores mínimos
    min_map_value = min(min_map_value, map_value)
    min_injection_time = min(min_injection_time, injection_time)
    min_tps_position = min(min_tps_position, tps_position)
    min_coolant_temp = min(min_coolant_temp, coolant_temp)
    min_lambda_afr = min(min_lambda_afr, lambda_afr)
    min_duty_cycle = min(min_duty_cycle, duty_cycle)
    min_battery_voltage = min(min_battery_voltage, battery_voltage)
    max_map_value = max(max_map_value, map_value)
    max_injection_time = max(max_injection_time, injection_time)
    max_tps_position = max(max_tps_position, tps_position)
    max_coolant_temp = max(max_coolant_temp, coolant_temp)
    max_lambda_afr = max(max_lambda_afr, lambda_afr)
    max_duty_cycle = max(max_duty_cycle, duty_cycle)
    max_battery_voltage = max(max_battery_voltage, battery_voltage)
        
       

# Inicia o monitoramento dos valores

#Valores mínimos e máximos registro

def ler_dados_arduino():
    print("testes2s")
    global map_value, injection_time, tps_position, coolant_temp, lambda_afr, duty_cycle, battery_voltage,errors,label_error_estatus
    
    try:
       
        while True:
            if ser.in_waiting > 0:
                
                linha = ser.readline().decode('utf-8').strip()
            
                try:
                    dados = linha.split(',')
                    if len(dados) == 8:
                        map_value = float(dados[0])
                        injection_time = float(dados[1])
                        tps_position = float(dados[2])
                        coolant_temp = float(dados[3])
                        lambda_afr = float(dados[4])
                        duty_cycle = float(dados[5])
                        battery_voltage = float(dados[6])
                        errors = float(dados[7])
                       
                      
                        if errors == 1:
                            label_error_estatus.configure(text="Avaria não conhecia",bg="black",background="red")
                        else:
                            label_error_estatus.configure(text="Nenhuma falha encontrada",bg="green",background="#333333")

                except ValueError:
                    print("Erro ao converter os dados")
    except serial.SerialException:
        label_conexao_estatus.configure(text="Perda de conexão com a ECU | OFFLINE",background="#333333",bg="orange")
        global conexao_status
        conexao_status = 0
        
        #Restauração_de_conexão()

def iniciar_leitura_arduino():
    thread = threading.Thread(target=ler_dados_arduino)
    thread.daemon = True
    thread.start()






def run_vol_module():
    
    # Faixas de valor para cada parâmetro
   
    def fechar_janela(event=None):
        if messagebox.askokcancel("Confirmação", "Você realmente deseja fechar a janela?"):
            root.destroy()
            
    current_directory = os.path.dirname(os.path.abspath(__file__))
    config_file_path = os.path.join(current_directory, "config.fuzil")
    diretorioint = 0
    
    

    if os.path.exists(config_file_path):
        with open(config_file_path, 'r') as config_file:
            config_data = config_file.readline().strip()
            project_directory = os.path.dirname(config_data)
            diretorioint = project_directory
            print("Diretório do projeto:", project_directory)
    else:
        print("O arquivo de configuração não existe.")

    with open(f"{diretorioint}/projeto.json", "r") as arquivo_json:
        dados = json.load(arquivo_json)    
    porta_serial = dados["Porta Serial"]
    
        
  


    projeto_nome = os.path.basename(diretorioint)





    def conexao():
        def encontrar_porta_serial(vid, pid):
            for porta in serial.tools.list_ports.comports():
                if porta.vid == vid and porta.pid == pid:
                    return porta.device
            return None

        def atualizar_portas():
            portas_disponiveis = [porta.device for porta in serial.tools.list_ports.comports()]
            porta_serial_combobox['values'] = portas_disponiveis

        def buscar_porta_por_vid_pid():
            vid = 0x4444  # Substitua pelo seu VID
            pid = 0x4446  # Substitua pelo seu PID

            porta_encontrada = encontrar_porta_serial(vid, pid)
            if porta_encontrada:
                porta_serial_combobox.set(porta_encontrada)
                messagebox.showinfo("Sucesso", f"Firmware oficial encontrado em {porta_encontrada}")
            else:
                messagebox.showwarning("Aviso", "firmware Oficial não encontrado\nVerifique a conexão com o computador ou procure a porta manualmente\nVersões de firmware Não lançadas pela nossa equipe podem não ser encontradas automaticamente")

        def salvar_json():
            dados_json["Porta Serial"] = porta_serial_combobox.get()
            with open(f"{diretorioint}/projeto.json", "w") as arquivo_json:
                json.dump(dados_json, arquivo_json)
            messagebox.showinfo("Sucesso", "Configurações salvas com sucesso!")

        # Carregar dados do JSON
        with open(f"{diretorioint}/projeto.json", "r") as arquivo_json:
            dados_json = json.load(arquivo_json)

        # Criar janela
        janeladeconexao = tk.Tk()
        janeladeconexao.title("Editar Configurações")
        janeladeconexao.geometry("164x100+844+200")
        janeladeconexao.resizable(False,False)

        # Criar e posicionar widgets
        porta_serial_label = tk.Label(janeladeconexao, text="Porta Serial:")
        porta_serial_label.grid(row=0, column=0)

        porta_serial_combobox = ttk.Combobox(janeladeconexao, width=10)
        porta_serial_combobox.grid(row=0, column=1)

        atualizar_portas_button = tk.Button(janeladeconexao, text="Atualizar Portas", command=atualizar_portas)
        atualizar_portas_button.grid(row=1, column=0, columnspan=2)

        buscar_porta_button = tk.Button(janeladeconexao, text="Buscar por VID/PID", command=buscar_porta_por_vid_pid)
        buscar_porta_button.grid(row=2, column=0, columnspan=2)

        salvar_button = tk.Button(janeladeconexao, text="Salvar", command=salvar_json)
        salvar_button.grid(row=3, column=0, columnspan=2)

        # Atualizar lista de portas disponíveis ao iniciar
        atualizar_portas()

       
       

        # Iniciar loop da janela
        janeladeconexao.mainloop()
    # Função para atualizar o gráfico
    def atualizar_grafico():
  
        # Atualizar os widgets existentes
        progress_bar_MAP.configure(value=map_value)
        label_valor_MAP.configure(text=str(map_value))
        label_maximo_MAP.configure(text=f'Máx: {max_map_value}')
        label_minimo_MAP.configure(text=f'Mín: {min_map_value}')

        progress_bar_tempo.configure(value=injection_time)
        label_valor_tempo.configure(text=str(injection_time))
        label_maximo_tempo.configure(text=f'Máx: {max_injection_time}')
        label_minimo_tempo.configure(text=f'Mín: {min_injection_time}')

        progress_bar_TPS.configure(value=tps_position)
        label_valor_TPS.configure(text=str(tps_position))
        label_maximo_TPS.configure(text=f'Máx: {max_tps_position}')
        label_minimo_TPS.configure(text=f'Mín: {min_tps_position}')

        progress_bar_temperatura.configure(value=coolant_temp)
        label_valor_temperatura.configure(text=coolant_temp)
        label_maximo_temperatura.configure(text=f'Máx: {max_coolant_temp}')
        label_minimo_temperatura.configure(text=f'Mín: {min_coolant_temp}')

        progress_bar_lambda.configure(value=lambda_afr)
        label_valor_lambda.configure(text=str(lambda_afr))
        label_maximo_lambda.configure(text=f'Máx: {max_lambda_afr}')
        label_minimo_lambda.configure(text=f'Mín: {min_lambda_afr}')

        progress_bar_fator.configure(value=duty_cycle)
        label_valor_fator.configure(text=str(duty_cycle))
        label_maximo_fator.configure(text=f'Máx: {max_duty_cycle}')
        label_minimo_fator.configure(text=f'Mín: {min_duty_cycle}')

        progress_bar_bateria.configure(value=battery_voltage)
        label_valor_bateria.configure(text=str(battery_voltage))
        label_maximo_bateria.configure(text=f'Máx: {max_battery_voltage}')
        label_minimo_bateria.configure(text=f'Mín: {min_battery_voltage}')
        monitor_values()
        root.after(60,atualizar_grafico)

     

    # Criando a janela principal
    root = tk.Tk()
    root.title(f'DSW injection - Instrumentação -> {projeto_nome}')
    root.geometry("800x544")
    root.iconbitmap(os.path.abspath("ico.ico"))
    root.resizable(False,False)
    root.protocol("WM_DELETE_WINDOW", fechar_janela)
    imagem_fundo = Image.open(os.path.abspath("icones/backgrond.png"))
    imagem_fundo = imagem_fundo.resize((800, 600), Image.LANCZOS)
    imagem_fundo = ImageTk.PhotoImage(imagem_fundo)
    fundo_label = tk.Label(root, image=imagem_fundo)
    fundo_label.place(x=0, y=0, relwidth=1, relheight=1)

    # Estilo para as Progressbars
    s = ttk.Style()
    s.configure('yellow.Horizontal.TProgressbar', foreground='yellow', background='yellow')
    s.configure('red.Horizontal.TProgressbar', foreground='red', background='red')
    s.configure('green.Horizontal.TProgressbar', foreground='green', background='green')

    # Função para criar um frame com borda para um instrumento
    def criar_frame_instrumento(titulo, x, y):
        frame = tk.Frame(root, bd=2, relief='groove',background="#333333")
        frame.place(x=x, y=y, width=260, height=120)
        label_titulo = ttk.Label(frame, text=titulo)
        label_titulo.place(x=5, y=5)
        return frame

    # Criando e posicionando os frames dos instrumentos
    frame_MAP = criar_frame_instrumento('MAP', 10, 10)
    frame_tempo = criar_frame_instrumento('Tempo de Injeção', 300, 10)
    frame_TPS = criar_frame_instrumento('Posição do TPS', 10, 140)
    frame_temperatura = criar_frame_instrumento('Temperatura do Refrigerante', 300, 140)
    frame_lambda = criar_frame_instrumento('Lambda AFR', 10, 270)
    frame_fator = criar_frame_instrumento('Fator de Trabalho', 300, 270)
    frame_bateria = criar_frame_instrumento('Tensão da Bateria', 10, 400)

    # MAP
    ttk.Label(frame_MAP, text='0          12,5           25        50        75        100').place(x=5,y=25)
    progress_bar_MAP = ttk.Progressbar(frame_MAP, orient='horizontal', length=200, mode='determinate')
    progress_bar_MAP.place(x=5,y=45)
    label_valor_MAP = ttk.Label(frame_MAP, text='', width=5, anchor='e', background='white')
    label_valor_MAP.place(x=210,y=45)
    label_maximo_MAP = ttk.Label(frame_MAP, text='', width=8, anchor='e', background='white')
    label_maximo_MAP.place(x=5,y=75)
    label_minimo_MAP = ttk.Label(frame_MAP, text='', width=8, anchor='e', background='white')
    label_minimo_MAP.place(x=145,y=75)

    # Tempo de Injeção
    progress_bar_tempo = ttk.Progressbar(frame_tempo, orient='horizontal', length=200, mode='determinate')
    progress_bar_tempo.place(x=5,y=45)
    label_valor_tempo = ttk.Label(frame_tempo, text='', width=5, anchor='e', background='white')
    label_valor_tempo.place(x=210,y=45)
    label_maximo_tempo = ttk.Label(frame_tempo, text='', width=8, anchor='e', background='white')
    label_maximo_tempo.place(x=5,y=75)
    label_minimo_tempo = ttk.Label(frame_tempo, text='', width=8, anchor='e', background='white')
    label_minimo_tempo.place(x=145,y=75)

    # Posição do TPS
    progress_bar_TPS = ttk.Progressbar(frame_TPS, orient='horizontal', length=200, mode='determinate')
    progress_bar_TPS.place(x=5, y=45)
    label_valor_TPS = ttk.Label(frame_TPS, text='', width=5, anchor='e', background='white')
    label_valor_TPS.place(x=210, y=45)
    label_maximo_TPS = ttk.Label(frame_TPS, text='', width=8, anchor='e', background='white')
    label_maximo_TPS.place(x=5, y=75)
    label_minimo_TPS = ttk.Label(frame_TPS, text='', width=8, anchor='e', background='white')
    label_minimo_TPS.place(x=145, y=75)

    # Temperatura do Refrigerante
    progress_bar_temperatura = ttk.Progressbar(frame_temperatura, orient='horizontal', length=200, mode='determinate')
    progress_bar_temperatura.place(x=5, y=45)
    label_valor_temperatura = ttk.Label(frame_temperatura, text='', width=5, anchor='e', background='white')
    label_valor_temperatura.place(x=210, y=45)
    label_maximo_temperatura = ttk.Label(frame_temperatura, text='', width=8, anchor='e', background='white')
    label_maximo_temperatura.place(x=5, y=75)
    label_minimo_temperatura = ttk.Label(frame_temperatura, text='', width=8, anchor='e', background='white')
    label_minimo_temperatura.place(x=145, y=75)

    # Lambda AFR
    ttk.Label(frame_lambda, text='0          0,5          1,0          1,5          2,0').place(x=5, y=25)
    progress_bar_lambda = ttk.Progressbar(frame_lambda, orient='horizontal', length=200, mode='determinate')
    progress_bar_lambda.place(x=5, y=45)
    label_valor_lambda = ttk.Label(frame_lambda, text='', width=5, anchor='e', background='white')
    label_valor_lambda.place(x=210, y=45)
    label_maximo_lambda = ttk.Label(frame_lambda, text='', width=8, anchor='e', background='white')
    label_maximo_lambda.place(x=5, y=75)
    label_minimo_lambda = ttk.Label(frame_lambda, text='', width=8, anchor='e', background='white')
    label_minimo_lambda.place(x=145, y=75)

    # Fator de Trabalho
    progress_bar_fator = ttk.Progressbar(frame_fator, orient='horizontal', length=200, mode='determinate')
    progress_bar_fator.place(x=5, y=45)
    label_valor_fator = ttk.Label(frame_fator, text='', width=5, anchor='e', background='white')
    label_valor_fator.place(x=210, y=45)
    label_maximo_fator = ttk.Label(frame_fator, text='', width=8, anchor='e', background='white')
    label_maximo_fator.place(x=5, y=75)
    label_minimo_fator = ttk.Label(frame_fator, text='', width=8, anchor='e', background='white')
    label_minimo_fator.place(x=145, y=75)

    # Tensão da Bateria
    progress_bar_bateria = ttk.Progressbar(frame_bateria, orient='horizontal', length=200, mode='determinate')
    progress_bar_bateria.place(x=5, y=45)
    label_valor_bateria = ttk.Label(frame_bateria, text='', width=5, anchor='e', background='white')
    label_valor_bateria.place(x=210, y=45)
    label_maximo_bateria = ttk.Label(frame_bateria, text='', width=8, anchor='e', background='white')
    label_maximo_bateria.place(x=5, y=75)
    label_minimo_bateria = ttk.Label(frame_bateria, text='', width=8, anchor='e', background='white')
    label_minimo_bateria.place(x=145, y=75)

    global ser
    global label_conexao_estatus

    label_conexao_estatus = tk.Label(root,text="2",background="#333333")
    label_conexao_estatus.place(x=14,y=544)
    def Restauração_de_conexão():
        global conexao_status
        global ser
        if conexao_status == 0:
            print("oi")
            try:
                ser = serial.Serial(porta_serial, 115200)
                conexao_status = 1
                iniciar_leitura_arduino()
            
                label_conexao_estatus.configure(text="ECU Conectada | RX 100% TX 100% |ONLINE ",background="#333333",bg="green")
            except serial.SerialException as e:
                messagebox.showinfo("Informação","ECU não encontrado | Verifique a conexão com o computador e tente novamente\ncaso tenha trocado a porta vá no menu (basic) > Conexão > e troque a porta para a correta")
    try:
        ser = serial.Serial(porta_serial, 115200)
        conexao_status = 1
        iniciar_leitura_arduino()
    
        label_conexao_estatus.configure(text="ECU Conectada | RX 100% TX 100% |ONLINE ",background="#333333",bg="green")
    except serial.SerialException as e:
        conexao_status = 0
    
        label_conexao_estatus.configure(text="ECU não encontrado | caso tenha trocado a porta vá no menu (basic) > Conexão > e troque a porta para a correta",bg="red")
    global label_error_estatus
    label_error_estatus = tk.Label(root,text="Nenhuma falha encontrada",background="#333333",bg="green")
    label_error_estatus.place(x=300,y=400)
    
    
            
    
    
# menu
#icones de menu 
    def tpscalibre():
       
        ser.write(b"A")
        ser.write(b"B")

    def iniciar_planilha():
        root = tk.Tk()
        #app = PlanilhaInjecaoEletronica(root)
        root.mainloop()
        
    basic_icon_path = os.path.abspath("icones/eng.png")  # Coloque o caminho correto para o ícone de edição
    basic_icon = Image.open(basic_icon_path)
    basic_icon = ImageTk.PhotoImage(basic_icon)

    engine_icon_path = os.path.abspath("icones/engine.png")  # Coloque o caminho correto para o ícone de edição
    engine_icon = Image.open(engine_icon_path)
    engine_icon = ImageTk.PhotoImage(engine_icon)

    tune_icon_path = os.path.abspath("icones/tune.png")  # Coloque o caminho correto para o ícone de edição
    tune_icon = Image.open(tune_icon_path)
    tune_icon = ImageTk.PhotoImage(tune_icon)

    ig_icon_path = os.path.abspath("icones/ig.png")  # Coloque o caminho correto para o ícone de edição
    ig_icon = Image.open(ig_icon_path)
    ig_icon = ImageTk.PhotoImage(ig_icon)

    barra_de_menu = Menu(root)
    root.config(menu=barra_de_menu)

    menubutton = tk.Menubutton(root, text="", image=basic_icon, compound=tk.LEFT)
    menubutton.place(x=644,y=44)

    menubutton2 = tk.Menubutton(root, text="", image=engine_icon, compound=tk.LEFT)
    menubutton2.place(x=644,y=84)

    menubutton3 = tk.Menubutton(root, text="", image=tune_icon, compound=tk.LEFT)
    menubutton3.place(x=644,y=124)

    menubutton4 = tk.Menubutton(root, text="", image=ig_icon, compound=tk.LEFT)
    menubutton4.place(x=644,y=164)

    # Menu Arquivo
    menu_basic = tk.Menu(menubutton, tearoff=0)
    menu_basic.add_command(label="conexão",command=conexao)
    menu_basic.add_command(label="software set",command= iniciar_planilha)
    menu_basic.add_command(label="Procurar pela ECU",command=Restauração_de_conexão)
    menu_basic.add_separator()
    menu_basic.add_command(label="calibrar TPS", command=tpscalibre)

    # Configurando o menu do Menubutton
    menubutton.configure(menu=menu_basic)

    menu_engine = tk.Menu(menubutton2, tearoff=0)
    menu_engine.add_command(label="conexão",command=conexao)
    menu_engine.add_command(label="software set",command= iniciar_planilha)
    menu_engine.add_command(label="Procurar pela ECU",command=Restauração_de_conexão)
    

    # Configurando o menu do Menubutton
    menubutton2.configure(menu=menu_engine)

    menu_tune = tk.Menu(menubutton3, tearoff=0)
    menu_tune.add_command(label="VE table map",command=conexao)
    menu_tune.add_command(label="software set",command= iniciar_planilha)
    menu_tune.add_command(label="Procurar pela ECU",command=Restauração_de_conexão)
    

    # Configurando o menu do Menubutton
    menubutton3.configure(menu=menu_tune)

    menu_ig = tk.Menu(menubutton4, tearoff=0)
    menu_ig.add_command(label="ignition table map",command=conexao)
    menu_ig.add_command(label="dwell time",command= iniciar_planilha)
    menu_ig.add_command(label="pre corte (3 step 2 step)",command=Restauração_de_conexão)
    

    # Configurando o menu do Menubutton
    menubutton4.configure(menu=menu_ig)
#/////////////////////////////////
    # Chamando a função para atualizar o gráfico
    thread2 = threading.Thread(target=atualizar_grafico)
    thread2.daemon = True
    thread2.start()

   

    root.mainloop()
    

if __name__ == "__main__":
    run_vol_module()
    
