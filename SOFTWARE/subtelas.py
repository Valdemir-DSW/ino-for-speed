import vol
import tkinter as tk
from tkinter import ttk

def calibretpstela():
    def update_progress(progress_bar):
       
        progress_bar["value"] = vol.tps_position
        root.after(10, update_progress)

    def maxtpsdefine():
        vol.ser.write(b"A")
        vol.ser.write(b"B")

    def mintpsdefine():
        vol.ser.write(b"A")
        vol.ser.write(b"C")

    root = tk.Tk()
    root.title("TPS calibre")
    root.resizable(False,False)

    progress = ttk.Progressbar(root, orient="horizontal", length=300, mode="determinate")
    progress.pack(pady=20)

    btn_previous = tk.Button(root, text="Definir como minimo", command=mintpsdefine)
    btn_previous.pack(side="left", padx=10)

    btn_next = tk.Button(root, text="Definir como máximo", command=maxtpsdefine)
    btn_next.pack(side="right", padx=10)

    update_progress()

    root.mainloop()
