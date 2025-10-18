# 🧘 Philosophers - 42

**Philosophers** es un proyecto del cursus 42 que introduce los conceptos de **concurrencia, sincronización** y **multithreading** en C.  
Su objetivo es simular el clásico *Problema de los Filósofos Comensales*, explorando la gestión de recursos compartidos, los hilos, los procesos y la prevención de **deadlocks**.

---

## 🧠 Introducción teórica

### 🍝 El problema de los filósofos
Cinco filósofos se sientan en una mesa redonda.  
Cada uno tiene un plato de espaguetis y un tenedor a su lado.  
Para comer, un filósofo necesita **dos tenedores** (uno a su izquierda y otro a su derecha).  
Cuando termina de comer, deja los tenedores, **piensa** y luego **duerme**.

El objetivo del proyecto es garantizar que:
- Ningún filósofo muera de hambre.
- No se produzcan **bloqueos mutuos (deadlocks)**.
- El acceso a los recursos sea **sincronizado y eficiente**.

---

### 🧵 Hilos y concurrencia
En la versión mandatoria, cada filósofo es un **hilo (thread)**.  
Todos los hilos comparten la misma memoria, por lo que se necesita un mecanismo que evite que accedan al mismo recurso simultáneamente.  
Ahí es donde entran los **mutex** (bloqueos de exclusión mutua).

---

### 🔒 Mutex
Un **mutex** es un tipo de variable que actúa como un "candado" sobre una sección de código o recurso.  
En este proyecto, cada tenedor se representa por un `pthread_mutex_t`.

Ejemplo:
```c
pthread_mutex_lock(&fork);
eat();
pthread_mutex_unlock(&fork);
```

De esta forma, solo un filósofo puede usar el tenedor al mismo tiempo.

---

### 💀 Deadlocks
Un **deadlock** ocurre cuando varios hilos quedan bloqueados esperando un recurso que nunca se libera.

**Ejemplo típico:**
1. Cada filósofo toma su tenedor izquierdo.
2. Todos esperan el derecho.
3. Ninguno puede avanzar.

🧩 **Soluciones comunes:**
- Alternar el orden en el que los filósofos toman los tenedores.
- Restringir el número de filósofos que comen simultáneamente.
- Usar un semáforo global de acceso a los tenedores.

---

### ⏱️ Control del tiempo
El proyecto requiere una gestión de tiempo muy precisa en milisegundos:
- `time_to_die` → tiempo máximo sin comer antes de morir.  
- `time_to_eat` → tiempo que tarda en comer.  
- `time_to_sleep` → tiempo que duerme antes de volver a pensar.

Para ello se usan funciones como `gettimeofday()` o `usleep()`.

---

## ⚙️ Compilación e instalación

### 🔧 Requisitos
- Sistema operativo: Linux o macOS  
- Compilador compatible con `pthread` (`gcc` o `clang`)  
- Utilidad `make`

### 🏗️ Compilación
```bash
make
```

Genera el ejecutable principal:
```bash
./philo
```

Versión **bonus** (procesos + semáforos):
```bash
make bonus
```

### 🧹 Limpieza
```bash
make clean
make fclean
make re
```

---

## 💡 Uso y parámetros

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_meals]
```

Ejemplo:
```bash
./philo 5 800 200 200
```

➡️ Crea 5 filósofos, cada uno:
- Muere si no come en 800 ms.  
- Come durante 200 ms.  
- Duerme durante 200 ms.

---

## 🖥️ Salida esperada

**Ejemplo de ejecución:**
```
0 1 is thinking
1 2 is thinking
2 3 is thinking
3 4 is thinking
4 5 is thinking
5 1 has taken a fork
6 1 has taken a fork
7 1 is eating
207 1 is sleeping
407 1 is thinking
...
802 3 died
```

📘 **Explicación:**
- La primera columna → tiempo en milisegundos desde el inicio.  
- La segunda → número del filósofo.  
- El texto → acción actual:
  - `is thinking` → está pensando.  
  - `has taken a fork` → ha tomado un tenedor.  
  - `is eating` → está comiendo.  
  - `is sleeping` → está durmiendo.  
  - `died` → ha muerto (fin del programa).

---

## 🧱 Estructura del proyecto

```
philo/
├── Makefile
├── philo.c
├── init.c
├── philo_eat.c
├── philo_routine.c
├── philo_monitor.c
├── utils/
│   ├── delay_utils.c
│   ├── print_utils.c
│   ├── init_utils.c
│   └── time_utils.c
└── includes/philo.h
```

Versión **bonus**:
```
philo_bonus/
├── philo_bonus.c
├── init_bonus.c
├── process_bonus.c
├── sem_utils_bonus.c
├── monitor_bonus.c
└── includes_bonus/philo_bonus.h
```

---

## 🔄 Diagrama – Flujo Mandatorio (threads + mutex)
```mermaid
flowchart TD
    A([Inicio]) --> B[init() - Inicializa estructuras y mutex]
    B --> C[create_threads() - Crea un hilo por filósofo]
    C --> D[philo_routine() - Ciclo de vida]
    D --> E[Tomar tenedores (mutex_lock)]
    E --> F[Comer (actualiza tiempo)]
    F --> G[Soltar tenedores (mutex_unlock)]
    G --> H[Dormir y pensar]
    D --> I[monitor() - Revisa muertes]
    I -->|Si alguien muere| J[Finalizar programa]
    H --> D
```

---

## 🔁 Diagrama – Flujo Bonus (processes + semáforos)
```mermaid
flowchart TD
    A([Inicio]) --> B[init_bonus() - Inicializa semáforos]
    B --> C[fork() - Crea un proceso por filósofo]
    C --> D[philo_routine_bonus() - Ciclo de vida del proceso]
    D --> E[sem_wait(forks) - Toma tenedores]
    E --> F[Comer (actualiza timestamp)]
    F --> G[sem_post(forks) - Libera tenedores]
    G --> H[Dormir y pensar]
    D --> I[monitor_bonus() - Proceso supervisor]
    I -->|Detecta muerte| J[Envía señales kill() a todos]
    H --> D
```

---

## 🧭 Diagrama – Flujo de funciones principales
```mermaid
flowchart TD
    A([main()]) --> B[parse_args()]
    B --> C[init() / init_bonus()]
    C --> D[create_threads() / create_processes()]
    D --> E[philo_routine()]
    E --> F[philo_eat()]
    F --> G[philo_sleep()]
    G --> H[philo_think()]
    D --> I[monitor() / monitor_bonus()]
    I --> J[check_death()]
    J --> K[exit_program()]
    K --> L([Fin])
```

---

## 🧩 Bonus – Procesos y semáforos (versión extendida)

En la versión bonus, cada filósofo se ejecuta en un **proceso independiente** creado con `fork()`.  
Esto implica que cada uno tiene su propio espacio de memoria y no comparte variables globales, por lo que la sincronización se realiza exclusivamente mediante **semáforos POSIX** (`sem_open`, `sem_wait`, `sem_post`, `sem_close`).

### 🧮 Funcionamiento interno
1. El proceso principal crea un **proceso hijo** por cada filósofo.
2. Se inicializan semáforos globales:
   - `forks` → controla cuántos tenedores pueden tomarse.
   - `print` → evita que se impriman mensajes simultáneos.
   - `death` → avisa al monitor cuando un filósofo muere.
3. Cada proceso ejecuta la rutina del filósofo: pensar → comer → dormir.
4. Un **proceso monitor** detecta muertes y notifica al proceso principal.
5. Si un filósofo muere, el proceso principal envía `kill()` al resto y cierra todos los semáforos.

### 🔹 Ventajas
- Aislamiento total: los procesos no comparten memoria.  
- Evita condiciones de carrera naturales de los hilos.  
- Fácil control de errores (cada filósofo es independiente).

### ⚠️ Desventajas
- Mayor uso de memoria y recursos del sistema.  
- Sincronización más compleja.  
- Dificultad para depurar y coordinar señales.

---

## ⚠️ Errores comunes y cómo evitarlos
| Problema | Causa | Solución |
|:----------|:------|:---------|
| **Deadlock** | Todos los filósofos toman un tenedor al mismo tiempo | Cambiar el orden o limitar la cantidad de filósofos que comen |
| **Race condition** | Falta de protección en `printf` o actualización de tiempos | Usar `pthread_mutex_lock()` o `sem_wait()` |
| **Tiempos inconsistentes** | `usleep()` mal calibrado o sin compensación | Usar `gettimeofday()` y ajustar diferencias |
| **Fugas de memoria** | No liberar mutex o semáforos | Usar `pthread_mutex_destroy()` / `sem_close()` / `sem_unlink()` |
| **Sincronización incorrecta (bonus)** | Semáforos mal cerrados o no creados globalmente | Inicializar todos con nombres únicos y `sem_unlink()` antes de crearlos |

---

## ⚖️ Comparativa final – Mandatory vs Bonus
| Característica | Mandatory | Bonus |
|:----------------|:-----------|:--------|
| **Ejecución** | Hilos (`pthread_create`) | Procesos (`fork`) |
| **Sincronización** | Mutex (`pthread_mutex_t`) | Semáforos (`sem_t`) |
| **Compartición de memoria** | Sí | No |
| **Monitorización** | Hilo supervisor | Proceso supervisor |
| **Gestión de impresión** | Mutex `print` | Semáforo `print` |
| **Finalización** | `pthread_join()` | Señales `kill()` |
| **Dificultad técnica** | Media | Alta |
| **Eficiencia** | Más rápida | Más estable y segura |
| **Complejidad de código** | Menor | Mayor (gestión de procesos y semáforos) |

---

## 📚 Recursos recomendados
- [Documentación de pthreads](https://man7.org/linux/man-pages/man7/pthreads.7.html)  
- [Guía de semáforos POSIX](https://man7.org/linux/man-pages/man7/sem_overview.7.html)  
- [Explicación del problema de los filósofos comensales (Wikipedia)](https://es.wikipedia.org/wiki/Problema_de_los_fil%C3%B3sofos_comensales)  
- [Deadlocks y cómo evitarlos](https://www.geeksforgeeks.org/deadlock-in-operating-system/)  

---

## 👨‍💻 Autor
**Aurodrig**  
42 Campus  
[https://github.com/aurodrig](https://github.com/aurodrig)
