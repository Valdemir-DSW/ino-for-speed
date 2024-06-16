import tkinter as tk
from tkinter import simpledialog, messagebox
import serial
import time
import threading
import pickle
import os
import vol
class PlanilhaInjecaoEletronica:
    def __init__(self, root):
        self.root = root
        self.root.title("Planilha de Injeção Eletrônica")

        self.entries = {}
        self.selected_entries = set()
        self.colors = {}
        self.serial_port = '/dev/ttyUSB0'  # Substitua pelo seu porto serial do Arduino
        self.baud_rate = 9600
        self.multi_select_enabled = tk.BooleanVar()
        self.backup_file = "planilha_backup.pkl"
        current_directory = os.path.dirname(os.path.abspath(__file__))
       


        config_file_path = os.path.join(current_directory, "config.fuzil")
        self.diretorioint = 0

        if os.path.exists(config_file_path):
            with open(config_file_path, 'r') as config_file:
                config_data = config_file.readline().strip()
                project_directory = os.path.dirname(config_data)
                self.diretorioint = project_directory
                print("Diretório do projeto:", project_directory)
        else:
            print("O arquivo de configuração não existe.")

# Construa o caminho completo para o arquivo de configuração
        config_file_path = os.path.join(current_directory, "config.fuzil")

        # Cria a grade (tabela)
        self.create_grid()

        # Botões organizados horizontalmente
        self.create_buttons()

        # Carrega o backup se existir
        self.load_backup()

        # Inicia o thread de backup automático
        self.start_auto_backup()

    def create_grid(self):
        # Labels das colunas (RPM)
        tk.Label(self.root, text="MAP / RPM", borderwidth=1, relief="solid", width=7).grid(row=0, column=0)
        for j, rpm in enumerate(range(500, 10500, 500), start=1):
            tk.Label(self.root, text=str(rpm), borderwidth=1, relief="solid", width=7).grid(row=0, column=j)

        # Labels das linhas (MAP) e células de entrada com valores predefinidos
        for i, map_val in enumerate(range(10, 200, 10), start=1):
            tk.Label(self.root, text=str(map_val), borderwidth=1, relief="solid", width=7).grid(row=i, column=0)
            for j, rpm in enumerate(range(500, 10500, 500), start=1):
                default_value = self.calculate_default_value(rpm)
                entry = tk.Entry(self.root, borderwidth=1, relief="solid", width=7)
                entry.grid(row=i, column=j)
                entry.insert(0, default_value)
                entry.bind("<KeyRelease>", self.update_color)
                entry.bind("<Button-1>", self.toggle_selection)
                self.entries[(map_val, rpm)] = entry
                self.update_color(None, entry)

    def create_buttons(self):
        button_frame = tk.Frame(self.root)
        button_frame.grid(row=len(range(-100, 150, 10)) + 1, columnspan=21)

        self.send_button = tk.Button(button_frame, text="Enviar para Arduino", command=self.send_to_arduino)
        self.send_button.grid(row=0, column=0, padx=5, pady=5)

        self.choose_button = tk.Button(button_frame, text="Escolher Valores e Piscar", command=self.choose_values_and_blink)
        self.choose_button.grid(row=0, column=1, padx=5, pady=5)

        self.multi_select_checkbutton = tk.Checkbutton(button_frame, text="Habilitar Seleção Múltipla", variable=self.multi_select_enabled, command=self.on_multi_select_toggle)
        self.multi_select_checkbutton.grid(row=0, column=2, padx=5, pady=5)

        self.set_value_button = tk.Button(button_frame, text="Definir Valor Selecionado", command=self.set_selected_values)
        self.set_value_button.grid(row=0, column=3, padx=5, pady=5)

        self.interpolate_button = tk.Button(button_frame, text="Interpolar Valores", command=self.interpolate_selected_values)
        self.interpolate_button.grid(row=0, column=4, padx=5, pady=5)

    def calculate_default_value(self, rpm):
        if rpm < 2000:
            return "1.0"
        elif rpm < 5000:
            return "50"
        else:
            return "90"

    def get_data(self):
        data = []
        for (map_val, rpm), entry in self.entries.items():
            value = entry.get()
            data.append(f"{map_val},{rpm},{value}")
        return data

    def send_to_arduino(self):
        data = {k: v.get() for k, v in self.entries.items()}
        formatted_data = self.format_data_for_serial(data)
        
        try:
            with vol.ser as ser:
                ser.write("A")
                print("Dados enviados para o Arduino:", formatted_data)
        except serial.SerialException as e:
            print("Erro de comunicação serial:", e)

    def format_data_for_serial(self, data):
        formatted_data = ""
        for (map_val, rpm), value in data.items():
            formatted_data += f"{map_val},{rpm},{value};"
        return formatted_data

    def update_color(self, event, entry=None):
        if not entry:
            entry = event.widget
        try:
            value = float(entry.get())
            color = self.calculate_color(value)
            entry.config(bg=color)
            self.colors[entry] = color  # Salva a cor original
        except ValueError:
            entry.config(bg="white")

    def calculate_color(self, value):
        min_value = 1.0
        max_value = 84
        ratio = (value - min_value) / (max_value - min_value)
        ratio = min(max(ratio, 0), 1)  # Clamping ratio to [0, 1]
        red = int(255 * ratio)
        blue = int(255 * (1 - ratio))
        green = 0
        return f'#{red:02x}{green:02x}{blue:02x}'

    def choose_values_and_blink(self):
        target_map = simpledialog.askinteger("Input", "Insira o valor de MAP:")
        target_rpm = simpledialog.askinteger("Input", "Insira o valor de RPM:")
        if target_map is not None and target_rpm is not None:
            self.blink_cells(target_map, target_rpm)

    def blink_cells(self, target_map, target_rpm):
        cells_to_blink = []

        for (map_val, rpm), entry in self.entries.items():
            if map_val == target_map and rpm == target_rpm:
                cells_to_blink.append(entry)
            
            elif (map_val == target_map or map_val == target_map + 10) and (rpm == target_rpm or rpm == target_rpm + 500):
                cells_to_blink.append(entry)

        for entry in cells_to_blink:
            self.blink_cell(entry)

    def blink_cell(self, entry):
        original_color = self.colors.get(entry, "white")
        self.blink(entry, original_color)

    def blink(self, entry, original_color):
        current_color = entry.cget("bg")
        new_color = "white" if current_color == original_color else original_color
        entry.config(bg=new_color)
        self.root.after(500, self.blink, entry, original_color)  # Pisca a cada 500ms

    def toggle_selection(self, event):
        if self.multi_select_enabled.get():
            entry = event.widget
            if entry in self.selected_entries:
                entry.config(bg=self.colors.get(entry, "white"))
                self.selected_entries.remove(entry)
            else:
                entry.config(bg="yellow")
                self.selected_entries.add(entry)

    def set_selected_values(self):
        new_value = simpledialog.askfloat("Input", "Insira o novo valor:")
        if new_value is not None:
            for entry in self.selected_entries:
                entry.delete(0, tk.END)
                entry.insert(0, new_value)
                self.update_color(None, entry)

    def on_multi_select_toggle(self):
        if not self.multi_select_enabled.get():
            self.clear_selection()

    def clear_selection(self):
        for entry in self.selected_entries:
            entry.config(bg=self.colors.get(entry, "white"))
        self.selected_entries.clear()

    def interpolate_selected_values(self):
        if len(self.selected_entries) < 2:
            messagebox.showerror("Erro", "Selecione pelo menos duas células para interpolar.")
            return

        sorted_entries = sorted(self.selected_entries, key=lambda e: self.get_entry_coords(e))

        first_entry = sorted_entries[0]
        last_entry = sorted_entries[-1]

        x1, y1 = self.get_entry_coords(first_entry)
        x2, y2 = self.get_entry_coords(last_entry)

        v1 = float(first_entry.get())
        v2 = float(last_entry.get())

        for entry in sorted_entries:
            x, y = self.get_entry_coords(entry)
            if entry not in [first_entry, last_entry]:
                interpolated_value = v1 + ((v2 - v1) * (x - x1) / (x2 - x1))
                entry.delete(0, tk.END)
                entry.insert(0, round(interpolated_value, 2))
                self.update_color(None, entry)

    def get_entry_coords(self, entry):
        for (map_val, rpm), e in self.entries.items():
            if e == entry:
                return map_val, rpm
    
    
    def save_backup(self):
        file =  self.diretorioint +"/"+ self.backup_file
        print(file)
        data = {k: v.get() for k, v in self.entries.items()}
        with open(file, 'wb') as f:
            pickle.dump(data, f)

    def load_backup(self):
        file =  self.diretorioint +"/"+ self.backup_file
        if os.path.exists(file):
            with open(file, 'rb') as f:
                data = pickle.load(f)
                for (map_val, rpm), value in data.items():
                    entry = self.entries[(map_val, rpm)]
                    entry.delete(0, tk.END)
                    entry.insert(0, value)
                    self.update_color(None, entry)

    def start_auto_backup(self):
        def backup_loop():
            while True:
                self.save_backup()
                time.sleep(2)

        backup_thread = threading.Thread(target=backup_loop, daemon=True)
        backup_thread.start()

if __name__ == "__main__":
    root = tk.Tk()
    app = PlanilhaInjecaoEletronica(root)
    root.mainloop()
