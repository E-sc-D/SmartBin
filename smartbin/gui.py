import tkinter as tk
from tkinter import messagebox
from tkinter import ttk
import serial
import threading

arduino = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=1)

def update_distance():
    """Aggiorna la distanza letta dal sonar e dal sensore"""
    try:
        while True:
            if arduino.in_waiting > 0:
                distanza = arduino.readline().decode('utf-8').strip() 
                temperatura = arduino.readline().decode('utf-8').strip()
                if distanza.isdigit():
                    distance_label.config(text=f"Livello bidone: {distanza} %")
                    temperature_label.config(text=f"Temperatura: {temperatura} °")
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

# Label per visualizzare la distanza
distance_label = tk.Label(root, text="Livello bidone: -- %", font=("Helvetica", 16))
distance_label.pack(pady=20)

# Label per visualizzare la temperatura
temperature_label = tk.Label(root, text="Temperatura: -- °", font=("Helvetica", 16))
temperature_label.pack(pady=20)

# Bottone per svuotare il bidone
empty_button = tk.Button(root, text="Empty the container", command=empty_bin, font=("Helvetica", 14))
empty_button.pack(pady=20)

# Bottone per resettare la macchina
reset_button = tk.Button(root, text="RESTORE", command=reset_bin, font=("Helvetica", 14))
reset_button.pack(pady=20)

# Thread per aggiornare la distanza in modo asincrono
thread = threading.Thread(target=update_distance, daemon=True)
thread.start()

# Avvia la GUI
root.mainloop()

# Chiudi la connessione seriale quando la GUI viene chiusa
arduino.close()