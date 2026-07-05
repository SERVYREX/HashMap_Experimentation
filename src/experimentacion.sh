#!/bin/bash

# Ejecutable
EXE="./hashAbierto"
EXE2="./hashCerrado"
EXE3="./hashSTL"

# Archivo de salida
SALIDA="../Resultados Experimentales/resultadosHashAbierto.csv"
SALIDA2="../Resultados Experimentales/resultadosHashCerrado.csv"
SALIDA3="../Resultados Experimentales/resultadosHashSTL.csv"
# Encabezado
echo "número_experimento;dataset;tipo_hash;cantidad_consultas;tiempo_ejecucion" > "$SALIDA"

ejecutar(){
    local exe_path=$1
    local salida=$2

    # Ejecutar 20 veces
    for ((exp=1; exp<=20; exp++)); do
	echo "Ejecutando $exe_path - experimento $exp..."

	"$exe_path" | while IFS=';' read -r estructura cantidad tiempo; do

            # Ignorar líneas de memoria o vacías
            [[ "$estructura" == Memoria* ]] && continue
            [[ -z "$estructura" ]] && continue

            # Escribir en el CSV
            echo "${exp};TweetsAuspol2019;${estructura};${cantidad};${tiempo}" >> "$SALIDA"

	done
    done
}
ejecutar "$EXE" "$SALIDA"
ejecutar "$EXE2" "$SALIDA2"
ejecutar "$EXE3" "$SALIDA3"

echo "Experimentos finalizados."
