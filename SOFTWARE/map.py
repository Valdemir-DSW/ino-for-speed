import tkinter as tk
from tkinter import simpledialog
import serial
import time

class PlanilhaInjecaoEletronica:
    def __init__(self, root):
        self.root = root
        self.root.title("Planilha de Injeção Eletrônica")

        self.entries = {}
        self.colors = {}
        self.serial_port = '/dev/ttyUSB0'  # Substitua pelo seu porto serial do Arduino
        self.baud_rate = 9600

        # Cria a grade (tabela)
        self.create_grid()

        # Botão para enviar dados ao Arduino
        self.send_button = tk.Button(self.root, text="Enviar para Arduino", command=self.send_to_arduino)
        self.send_button.grid(row=len(range(-100, 150, 10)) + 1, columnspan=21)

        # Botão para escolher valores e piscar células
        self.choose_button = tk.Button(self.root, text="Escolher Valores e Piscar", command=self.choose_values_and_blink)
        self.choose_button.grid(row=len(range(-100, 150, 10)) + 2, columnspan=21)

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
                self.entries[(map_val, rpm)] = entry
                self.update_color(None, entry)

    def calculate_default_value(self, rpm):
        if rpm < 2000:
            return "1.0"
        elif rpm < 5000:
            return "1.5"
        else:
            return "2.0"

    def get_data(self):
        data = []
        for (map_val, rpm), entry in self.entries.items():
            value = entry.get()
            data.append(f"{map_val},{rpm},{value}")
        return data

    def send_to_arduino(self):
        data = self.get_data()
        print(entry.encode())
        with serial.Serial(self.serial_port, self.baud_rate, timeout=1) as ser:
            for entry in data:
                ser.write(entry.encode())
                ser.write(b'\n')
                time.sleep(0.1)  # Aguarde um pouco para não sobrecarregar o Arduino
                while True:
                    response = ser.readline().decode().strip()
                    if response == "OK":
                        break
                time.sleep(0.1)

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
        max_value = 2.0
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

if __name__ == "__main__":
    root = tk.Tk()
    app = PlanilhaInjecaoEletronica(root)
    root.mainloop()
