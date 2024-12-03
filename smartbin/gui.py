import tkinter as tk
from tkinter import messagebox
from tkinter import ttk
import serial
import threading

arduino = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=1)

def update_distance():
    """Aggiorna la distanza letta dal sonar e dal sensore"""
    try:
        while True:
            if arduino.in_waiting > 0:
                distanza = arduino.readline().decode('utf-8').strip()   #legge il primo numero dal monitor seriale e lo mette nella variabile distanza (è gia convertita in percentuale rispetto alla distanza massima)
                temperatura = arduino.readline().decode('utf-8').strip()    #legge il secondo numero dal monitor seriale e lo mette nella variavile temperatura
                if distanza.isdigit():
                    distance_label.config(text=f"Livello bidone: {distanza} %")         
                    temperature_label.config(text=f"Temperatura: {temperatura} °")
                    progress_var.set(distanza)
    except Exception as e:
        print(f"Errore: {e}")



def empty_bin():
    try:
        arduino.write(b'E')
    except Exception as e:
        messagebox.showerror("Errore", f"Non è stato possibile inviare il comando: {e}")

def reset_bin():
    try:
        arduino.write(b'R')
    except Exception as e:
        messagebox.showerror("Errore", f"Non è stato possibile inviare il comando: {e}")

# Crea la finestra principale
root = tk.Tk()
root.title("Smart bin")
root.geometry("400x500")
root.configure(bg='DarkOrchid2')

# Label per visualizzare la distanza
distance_label = tk.Label(root, text="Livello bidone: -- %", font=("Vivaldi", 16))
distance_label.pack(pady=20)
distance_label.configure(bg='green3')

#Label per la barra di progressone
progress_var = tk.DoubleVar()
progress_bar = ttk.Progressbar(root, variable=progress_var, maximum=100)
progress_bar.pack(padx=100, pady=20, fill="x")



# Label per visualizzare la temperatura
temperature_label = tk.Label(root, text="Temperatura: -- °", font=("Vivaldi", 16))
temperature_label.pack(padx=80,pady=20)
temperature_label.configure(bg='green3')

# Bottone per svuotare il bidone
empty_button = tk.Button(root,bg='green3', text="Empty the container", command=empty_bin, font=("Vivaldi", 14))
empty_button.pack(pady=20)

# Bottone per resettare la macchina
reset_button = tk.Button(root,bg='green3', text="RESTORE", command=reset_bin, font=("Vivaldi", 14))
reset_button.pack(pady=20)

# Thread per aggiornare la distanza in modo asincrono
thread = threading.Thread(target=update_distance, daemon=True)
thread.start()

# Avvia la GUI
root.mainloop()

# Chiudi la connessione seriale quando la GUI viene chiusa
arduino.close()