import numpy as np
import matplotlib.pyplot as plt

# Archivos de latencias
mutex_data = np.loadtxt("latencia_mutex_no_bloq.txt")
sem_data = np.loadtxt("latencia_semaforo_no_bloq.txt")

# Recorte para evitar outliers
limite = np.percentile(np.concatenate([mutex_data, sem_data]), 99)
mutex_data = mutex_data[mutex_data < limite]
sem_data = sem_data[sem_data < limite]

# Calcular estadísticas
def stats(data, label):
    print(f"--- {label} ---")
    print(f"Min: {np.min(data):.0f} ns")
    print(f"Max: {np.max(data):.0f} ns")
    print(f"Promedio: {np.mean(data):.2f} ns")
    print(f"Desv. estándar: {np.std(data):.2f} ns\n")

stats(mutex_data, "Mutex")
stats(sem_data, "Semáforo")

# Histograma
plt.figure(figsize=(8,6))
bins = 40

plt.hist(mutex_data, bins=bins, alpha=0.6, label="Mutex", color='steelblue')
plt.hist(sem_data, bins=bins, alpha=0.6, label="Semáforo", color='orange')

plt.title("Comparación de latencias - Caso no bloqueante")
plt.xlabel("Latencia (nanosegundos)")
plt.ylabel("Frecuencia")
plt.legend()
plt.grid(True, linestyle='--', alpha=0.5)
plt.tight_layout()
plt.show()
