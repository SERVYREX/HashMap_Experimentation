import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

#Configuramos el entorno visual
sns.set_theme(style = "darkgrid")

#================================#
#========= Hash abierto =========#
#================================#

#Cargamos los datos 
df_abierto = pd.read_csv("../Resultados Experimentales/resultadosHashAbierto.csv", sep = ";")

#Filtramos los datos
df_abierto_modulo = df_abierto[df_abierto['tipo_hash'].str.contains('modulo', case=False)]
df_abierto_aurea = df_abierto[df_abierto['tipo_hash'].str.contains('aurea', case=False)]

plt.figure(figsize = (10,6))
sns.lineplot(data = df_abierto_modulo, x = 'cantidad_consultas', y = 'tiempo_ejecucion', hue = 'tipo_hash', marker = 'o', errorbar = 'sd')
plt.ylim(0.01, 0.5)
plt.title("Comparativa Tiempo Ejecucion HashMap Abierto (Modulo)")
plt.xlabel("Cantidad de Consultas", fontsize = 12)
plt.ylabel("Tiempo Ejecucion (segundos)", fontsize = 12)
plt.legend(title = "Tipo de Hash", loc = 'upper left')
plt.tight_layout()
plt.savefig("../Resultados Experimentales/Graficos/graficoTiempoEjecucionHashAbierto_Modulo.png")

plt.figure(figsize = (10,6))
sns.lineplot(data = df_abierto_aurea, x = 'cantidad_consultas', y = 'tiempo_ejecucion', hue = 'tipo_hash', marker = 'o', errorbar = 'sd')
plt.ylim(0.01, 0.5)
plt.title("Comparativa Tiempo Ejecucion HashMap Abierto (Aurea)")
plt.xlabel("Cantidad de Consultas", fontsize = 12)
plt.ylabel("Tiempo Ejecucion (segundos)", fontsize = 12)
plt.legend(title = "Tipo de Hash", loc = 'upper left')
plt.tight_layout()
plt.savefig("../Resultados Experimentales/Graficos/graficoTiempoEjecucionHashAbierto_Aurea.png")

#================================#
#========= Hash cerrado =========#
#================================#

#Cargamos los datos 
df_cerrado = pd.read_csv("../Resultados Experimentales/resultadosHashCerrado.csv", sep = ";")

#Filtramos los datos
df_cerrado_modulo = df_cerrado[df_cerrado['tipo_hash'].str.contains('modulo', case=False)]
df_cerrado_aurea = df_cerrado[df_cerrado['tipo_hash'].str.contains('aurea', case=False)]
df_cerrado_linear = df_cerrado[df_cerrado['tipo_hash'].str.contains('linear', case=False)]
df_cerrado_quadratic = df_cerrado[df_cerrado['tipo_hash'].str.contains('quadratic', case=False)]

plt.figure(figsize = (10,6))
sns.lineplot(data = df_cerrado_modulo, x = 'cantidad_consultas', y = 'tiempo_ejecucion', hue = 'tipo_hash', marker = 'o', errorbar = 'sd')
plt.ylim(0.01, 0.5)
plt.title("Comparativa Tiempo Ejecucion HashMap Cerrado (Doble Hash con Modulo)")
plt.xlabel("Cantidad de Consultas", fontsize = 12)
plt.ylabel("Tiempo Ejecucion (segundos)", fontsize = 12)
plt.legend(title = "Tipo de Hash", loc = 'upper left')
plt.tight_layout()
plt.savefig("../Resultados Experimentales/Graficos/graficoTiempoEjecucionHashCerrado_Modulo.png")

plt.figure(figsize = (10,6))
sns.lineplot(data = df_cerrado_aurea, x = 'cantidad_consultas', y = 'tiempo_ejecucion', hue = 'tipo_hash', marker = 'o', errorbar = 'sd')
plt.ylim(0.01, 0.5)
plt.title("Comparativa Tiempo Ejecucion HashMap Cerrado (Doble Hash con Aurea)")
plt.xlabel("Cantidad de Consultas", fontsize = 12)
plt.ylabel("Tiempo Ejecucion (segundos)", fontsize = 12)
plt.legend(title = "Tipo de Hash", loc = 'upper left')
plt.tight_layout()
plt.savefig("../Resultados Experimentales/Graficos/graficoTiempoEjecucionHashCerrado_Aurea.png")

plt.figure(figsize = (10,6))
sns.lineplot(data = df_cerrado_linear, x = 'cantidad_consultas', y = 'tiempo_ejecucion', hue = 'tipo_hash', marker = 'o', errorbar = 'sd')
plt.ylim(0.01, 0.5)
plt.title("Comparativa Tiempo Ejecucion HashMap Cerrado (Linear Probing)")
plt.xlabel("Cantidad de Consultas", fontsize = 12)
plt.ylabel("Tiempo Ejecucion (segundos)", fontsize = 12)
plt.legend(title = "Tipo de Hash", loc = 'upper left')
plt.tight_layout()
plt.savefig("../Resultados Experimentales/Graficos/graficoTiempoEjecucionHashCerrado_Linear.png")

plt.figure(figsize = (10,6))
sns.lineplot(data = df_cerrado_quadratic, x = 'cantidad_consultas', y = 'tiempo_ejecucion', hue = 'tipo_hash', marker = 'o', errorbar = 'sd')
plt.ylim(0.01, 0.5)
plt.title("Comparativa Tiempo Ejecucion HashMap Cerrado (Quadratic Probing)")
plt.xlabel("Cantidad de Consultas", fontsize = 12)
plt.ylabel("Tiempo Ejecucion (segundos)", fontsize = 12)
plt.legend(title = "Tipo de Hash", loc = 'upper left')
plt.tight_layout()
plt.savefig("../Resultados Experimentales/Graficos/graficoTiempoEjecucionHashCerrado_Quadratic.png")

#===========================#
#======== Hash STL =========#
#===========================#

#Cargamos los datos 
df_stl = pd.read_csv("../Resultados Experimentales/resultadosHashSTL.csv", sep = ";")

plt.figure(figsize = (10,6))
sns.lineplot(data = df_stl, x = 'cantidad_consultas', y = 'tiempo_ejecucion', hue = 'tipo_hash', marker = 'o', errorbar = 'sd')
plt.ylim(0.01, 0.5)
plt.title("Comparativa Tiempo Ejecucion HashMap STL")
plt.xlabel("Cantidad de Consultas", fontsize = 12)
plt.ylabel("Tiempo Ejecucion (segundos)", fontsize = 12)
plt.legend(title = "Tipo de Hash", loc = 'upper left')
plt.tight_layout()
plt.savefig("../Resultados Experimentales/Graficos/graficoTiempoEjecucionHashSTL.png")

#====================================================#
#========= Comparativa General (Promedios) ==========#
#====================================================#

df_abierto_avg = df_abierto.copy()
df_abierto_avg['tipo_hash'] = 'Abierto: ' + df_abierto_avg['tipo_hash'].astype(str)

df_cerrado_avg = df_cerrado.copy()
df_cerrado_avg['tipo_hash'] = 'Cerrado: ' + df_cerrado_avg['tipo_hash'].astype(str)

df_stl_avg = df_stl.copy()
df_stl_avg['tipo_hash'] = 'STL: ' + df_stl_avg['tipo_hash'].astype(str)

df_all = pd.concat([df_abierto_avg, df_cerrado_avg, df_stl_avg])

# Tomamos solo el escenario de maxima carga (180,000 consultas)
df_max_carga = df_all[df_all['cantidad_consultas'] == 180000]

plt.figure(figsize = (12, 8))
sns.barplot(data = df_max_carga, x = 'tiempo_ejecucion', y = 'tipo_hash', errorbar = 'sd', orient = 'h')
plt.title("Tiempo de Ejecucion por Implementacion (Carga Maxima: 180.000 consultas)")
plt.xlabel("Tiempo Promedio (segundos)", fontsize = 12)
plt.ylabel("Implementación / Tipo de Hash", fontsize = 12)
plt.tight_layout()
plt.savefig("../Resultados Experimentales/Graficos/graficoTiempoEjecucion_Promedios.png")

#====================================================#
#========= Tabla de Varianza (Carga Maxima) =========#
#====================================================#

# Calculamos la varianza agrupando por tipo de hash en la carga maxima
varianza_df = df_max_carga.groupby('tipo_hash')['tiempo_ejecucion'].var().reset_index()
varianza_df.rename(columns={'tipo_hash': 'Implementacion', 'tiempo_ejecucion': 'Varianza (s^2)'}, inplace=True)
# Ordenamos primero por el tipo (Abierto, Cerrado, STL) y luego por su varianza
varianza_df = varianza_df.sort_values(by=['Implementacion', 'Varianza (s^2)'])

# Guardamos la tabla en un archivo CSV
varianza_df.to_csv("../Resultados Experimentales/varianza_implementaciones.csv", index=False, sep=";")

print("\n--- Varianza de Tiempos de Ejecucion (180,000 consultas) ---")
print(f"{'Implementacion':<35} | {'Varianza (s^2)'}")
print("-" * 55)
for _, row in varianza_df.iterrows():
    print(f"{row['Implementacion']:<35} | {row['Varianza (s^2)']:.8e}")
print("----------------------------------------------------------\n")

plt.figure(figsize = (12, 8))
sns.barplot(data = varianza_df, x = 'Varianza (s^2)', y = 'Implementacion', orient = 'h', color='salmon')
plt.title("Varianza de Tiempos de Ejecucion por Implementacion (Carga Maxima)")
plt.xlabel("Varianza (segundos al cuadrado)", fontsize = 12)
plt.ylabel("Implementación / Tipo de Hash", fontsize = 12)
plt.tight_layout()
plt.savefig("../Resultados Experimentales/Graficos/graficoVarianzaImplementaciones.png")
