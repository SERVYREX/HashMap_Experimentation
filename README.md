# Evaluación de Rendimiento de Implementaciones de Hash Maps

## Descripción

Este proyecto implementa y evalúa diferentes estructuras de tablas hash o **Hash Maps** en C++, sometiéndolas a pruebas de estrés .
El objetivo principal es comparar la eficiencia (tiempos de ejecución y varianza) de múltiples estrategias de resolución de colisiones y funciones hash.

Las implementaciones analizadas se dividen en tres categorías principales:
1. **Hash Abierto (Chaining)**
2. **Hash Cerrado (Open Addressing)**
3. **Hash STL (`std::unordered_map`)** como baseline (referencia).

Además de la implementación en C++, el proyecto incorpora un flujo automatizado para la recolección de datos y generación de gráficos analíticos utilizando Python.

---

## Estructura del proyecto

```text
HashMap_Experimentation/
├── Data/
├── include/
├── Resultados Experimentales/
│   ├── Graficos/
└── src/
```

| Carpeta | Descripción |
|----------|-------------|
| `Data/` | Contiene el dataset utilizado en las pruebas de carga. |
| `include/` | Cabeceras del proyecto con las implementaciones de los Hash Maps y utilidades. |
| `src/` | Programas principales para la experimentación, bash scripts y análisis estadístico en Python. |
| `Resultados Experimentales/` | Contiene los archivos CSV en crudo obtenidos al correr las pruebas (Creados al momento de la ejecucion). |
| `Resultados Experimentales/Graficos/` | Contiene todas las visualizaciones finales (líneas, promedios, varianzas). |

---

## DATA

### Dataset de Tweets (auspol2019)
Consiste en registros parseados desde el archivo `auspol2019.csv`. Obtenido de: [Kaggle: Australian Election 2019 Tweets](https://www.kaggle.com/datasets/taniaj/australian-election-2019-tweets?select=auspol2019.csv). Para los experimentos, el dataset se utiliza como fuente de inserción masiva.

| Dato utilizado | Tipo | Finalidad |
|----------------|------|-----------|
| `user_id` | Numérico (`unsigned long long`) | Evaluar la eficiencia de las funciones hash con números muy grandes. |
| `user_screen_name` | Texto (`string`) | Evaluar la eficiencia de las funciones hash con cadenas de caracteres y su transformación matemática a índices. |
 
---

## include

| Archivo | Descripción |
|---------|-------------|
| `tabla_hash_abierta.h` | Implementación del TDA Hash Map con resolución de colisiones por encadenamiento (Listas enlazadas). |
| `tabla_hash_cerrada.h` | Implementación del TDA Hash Map con resolución de colisiones por direccionamiento abierto. |
| `funciones_hash.h` | Implementación de métodos hash matemáticos (Módulo y Áurea) y métodos de probing (Doble Hash, Linear, Quadratic). |
| `lectura_csv.h` | Lógica de parseo del archivo CSV para poblar las estructuras de datos. |

---

## src

| Archivo | Descripción |
|---------|-------------|
| `experimentacionAbierta.cpp` | Código de prueba para las instancias del Hash Abierto. |
| `experimentacionCerrada.cpp` | Código de prueba para las instancias del Hash Cerrado. |
| `experimentacionSTLhash.cpp`| Código de prueba evaluando la librería estándar `std::unordered_map`. |
| `experimentacion.sh` | Script bash para ejecutar cada binario de pruebas 20 veces automáticamente. |
| `exportarGraficos.py` | Script en Python que procesa los CSV resultantes y exporta gráficos de comparativa. |

---

## Dependencias

**Para la experimentación en C++:**
- Compilador compatible con C++11 o superior (e.g., `g++`).
- Entorno Bash para la automatización (`.sh`).

**Para la generación de gráficos en Python:**
- Python 3.x
- `pandas`
- `matplotlib`
- `seaborn`

*Instalación de dependencias de Python:*
```bash
pip install pandas matplotlib seaborn
```

---

## Compilación

Para compilar los binarios de experimentación, posicionarse en la carpeta `src` y ejecutar:

```bash
cd src
g++ experimentacionAbierta.cpp -o hashAbierto
g++ experimentacionCerrada.cpp -o hashCerrado
g++ experimentacionSTLhash.cpp -o hashSTL
```
Antes de la primera ejecución, asegúrate de dar permisos al script de pruebas:
```bash
chmod +x experimentacion.sh
```

---

## Configuración de experimentos

Dentro del script `experimentacion.sh` puedes ajustar el volumen o la mecánica modificando:
- El número de ejecuciones en el bucle principal (actualmente configurado a 20 iteraciones para un buen muestreo estadístico y análisis de la varianza).
- Si necesitas un cambio de ruta de salida de los `.csv`.

---

## Ejecución

1. **Lanzar Experimentos C++** (desde `src/`):
```bash
./experimentacion.sh
```
*Este proceso generará progresivamente los tres archivos CSV base en la carpeta de Resultados.*

2. **Procesamiento de Resultados (Python)** (desde `src/`):
```bash
python3.14 exportarGraficos.py
```
*(Asegúrate de ajustar el comando python a `python` o `python3` según tu entorno si no utilizas `python3.14`).*

---

## Resultados

El análisis de Python proveerá:
- **Gráficos de Tiempos** en `Resultados Experimentales/Graficos`:
   - Gráficos de líneas para observar la progresión del tiempo *vs* cantidad de consultas.
   - Gráfico de barras horizontales de **Tiempos Promedios** (Evaluado en estrés bajo carga máxima de 180,000 consultas).
   - Gráfico de barras de **Varianza** para identificar la estabilidad y predictibilidad en el rendimiento de cada algoritmo.
- **Tabla Analítica**: El archivo CSV `varianza_implementaciones.csv` con los cálculos precisos exportados.

---

## Autores

- Bryan Aguirre Fuentes
- Rodolfo Rubio Reyes
- Alfonso González Giusti

---

## Uso académico

Este proyecto fue desarrollado exclusivamente con fines académicos para el estudio de estructuras de datos, estrategias de resolución de colisiones, análisis de rendimiento algorítmico y estadística descriptiva.