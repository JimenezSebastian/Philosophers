# Philosophers

 Esta historia es una **analogía clásica** en informática conocida como el **problema de los filósofos comensales**, usada para enseñar conceptos de **concurrencia**, **acceso a recursos compartidos**, y **evitación del deadlock**. 

---

### 🧠 **1. Filósofo = Hilo (Thread)**

Cada filósofo es un proceso/hilo independiente.
🔁 Representa la ejecución concurrente.

---

### 🍴 **2. Tenedores = Recursos compartidos (como mutex o semáforos)**

Hay un tenedor entre cada par de filósofos, o sea uno a la izquierda y otro a la derecha.
🛠️ Necesitan **acceder a dos recursos** simultáneamente para realizar una acción crítica (comer).

---

### 💤🍝🤔 **3. Dormir / Comer / Pensar = Estados del hilo**

Estas son las tareas del ciclo de vida de un hilo:

* **Comer**: sección crítica (accede a recursos compartidos: tenedores).
* **Pensar**: no accede a recursos.
* **Dormir**: simula inactividad o espera (a menudo con `usleep`).

---

### ☠️ **4. Morir = Timeout por inanición (starvation)**

Un filósofo muere si **pasa demasiado tiempo sin poder comer**.
📆 Esto se implementa con un **temporizador o timestamp** para cada filósofo, y se monitorea cuánto tiempo ha pasado desde su última comida.

---

### ⛔ **5. No hablar / no saber si otro muere = Sin comunicación ni conocimiento global**

Cada hilo **no tiene información directa sobre otros hilos**. Todo debe coordinarse mediante los recursos compartidos.

---

### 🧠 **Resumen de analogía (en forma de tabla):**

| Historia                  | Programación                          |
| ------------------------- | ------------------------------------- |
| Filósofo                  | Hilo (thread)                         |
| Tenedor                   | Recurso compartido (mutex/semáforo)   |
| Comer                     | Sección crítica                       |
| Pensar / Dormir           | Actividad no crítica / `usleep`       |
| Morir de hambre           | Timeout por no acceder a recursos     |
| No hablar / no saber      | No comunicación entre hilos           |
| Simulación que se detiene | Algoritmo detecta condición de muerte |

---

### 📂 FUNCIONES COMUNES (libc / sistema estándar)

Estas las puedes usar en cualquier proyecto de C sin hilos:

| Función        | Descripción breve                                  |
| -------------- | -------------------------------------------------- |
| `memset`       | Rellena un bloque de memoria con un valor          |
| `printf`       | Imprime texto en la salida estándar                |
| `malloc`       | Reserva memoria dinámica                           |
| `free`         | Libera memoria reservada con `malloc`              |
| `write`        | Escribe bytes en un descriptor de archivo          |
| `usleep`       | Pausa la ejecución por microsegundos               |
| `gettimeofday` | Obtiene el tiempo actual (útil para medir tiempos) |

---

### 🔄 FUNCIONES ESPECÍFICAS DE `pthread` (manejo de hilos y mutexes)

Estas son las herramientas que controlan los hilos y la sincronización:

| Función                 | Descripción breve                                          |
| ----------------------- | ---------------------------------------------------------- |
| `pthread_create`        | Crea un nuevo hilo                                         |
| `pthread_detach`        | Separa un hilo del "join", permitiendo limpieza automática |
| `pthread_join`          | Espera a que un hilo termine                               |
| `pthread_mutex_init`    | Inicializa un mutex                                        |
| `pthread_mutex_destroy` | Libera recursos de un mutex                                |
| `pthread_mutex_lock`    | Bloquea (cierra) el mutex para exclusión mutua             |
| `pthread_mutex_unlock`  | Desbloquea (abre) el mutex                                 |

---


