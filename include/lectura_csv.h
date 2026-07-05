#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "tabla_hash_abierta.h"
#include "tabla_hash_cerrada.h"
#include <chrono>
using namespace std;

// Convertimos la función en un template para que acepte cualquier TipoClave y TipoHash
template <typename TipoClave, typename TipoTabla>
void cargarUsuariosDesdeCSV(const string& rutaArchivo, TipoTabla& tabla, bool usarScreenName, const string& tipo_tabla) {
  ifstream archivo(rutaArchivo);
    
  if (!archivo.is_open()) {
    cerr << "Error: No se pudo abrir el archivo " << rutaArchivo << endl;
    return;
  }

  string linea;
  vector<string> campos;
  string campoActual = "";
  bool enComillas = false;
  int lineasProcesadas = 0;
  bool primeraFila = true;
  int columnaObjetivo;

  int checkpoint = 1;
    
  if(usarScreenName){
    columnaObjetivo = 7; // Columna para screen_name
  } else {
    columnaObjetivo = 5; // Columna para user_id
  }

  auto start = chrono::high_resolution_clock::now();


    
  while (getline(archivo, linea)) {
    for (size_t i = 0; i < linea.length(); ++i) {
      char c = linea[i];

      if (c == '"') {
	enComillas = !enComillas; 
      } else if (c == ',' && !enComillas) {
	campos.push_back(campoActual);
	campoActual = "";
      } else {
	campoActual += c;
      }
    }

    if (enComillas) {
      campoActual += "\n";
    } else {
      campos.push_back(campoActual); 

      if (primeraFila) {
	primeraFila = false;
      } else if (campos.size() > columnaObjetivo) {
	try {
	  TipoClave clave;

 
	  if constexpr (is_same_v<TipoClave, unsigned long long>) {
	    // Si la tabla espera números, convertimos el texto de la columna a entero largo
	    clave = stoull(campos[columnaObjetivo]);
	  } 
	  else if constexpr (is_same_v<TipoClave, string>) {
	    // Si la tabla espera strings, la asignación es directa
	    clave = campos[columnaObjetivo];
	  }

	  // Lógica Hash estándar
	  int frecuenciaActual = tabla.obtener(clave);
	  tabla.insertar(clave, frecuenciaActual + 1);
                    
	  lineasProcesadas++;
	} catch (const invalid_argument& e) {
	  cerr << "Error: Se intento parsear un texto no numerico en la linea " << lineasProcesadas + 2 
	       << ". Valor de columna: " << campos[columnaObjetivo] << endl;
	} catch (const out_of_range& e) {
	  cerr << "El ID numerico es demasiado grande en la linea " << lineasProcesadas + 2 << endl;
	}
      }
      campos.clear();
      campoActual = "";
    }

    if(lineasProcesadas == 10000*checkpoint){
      cout << tipo_tabla << ";" << lineasProcesadas << ";";
      auto end = chrono::high_resolution_clock::now();
	  
      double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  
      running_time *= 1e-9;
	  
      cout<< running_time << endl;
      checkpoint++;
    }
	
  }
  archivo.close();
}

    

template <typename TipoClave>
void cargarUsuariosDesdeCSV(const string& rutaArchivo, unordered_map<TipoClave, int>& mapa, bool usarScreenName, const string& tipo_tabla) {
  ifstream archivo(rutaArchivo);
    
  if (!archivo.is_open()) {
    cerr << "Error: No se pudo abrir el archivo " << rutaArchivo << endl;
    return;
  }

  string linea;
  vector<string> campos;
  string campoActual = "";
  bool enComillas = false;
  int lineasProcesadas = 0;
  bool primeraFila = true;

  int checkpoint = 1;
  // user_id = 5, user_screen_name = 7
  size_t columnaObjetivo;
  if(usarScreenName) {
    columnaObjetivo = 7; // Columna para screen_name
  } else {
    columnaObjetivo = 5; // Columna para user_id
  }

  auto start = chrono::high_resolution_clock::now();
    
  while (getline(archivo, linea)) {
    for (size_t i = 0; i < linea.length(); ++i) {
      char c = linea[i];

      if (c == '"') {
	enComillas = !enComillas; 
      } else if (c == ',' && !enComillas) {
	campos.push_back(campoActual);
	campoActual = "";
      } else {
	campoActual += c;
      }
    }

    if (enComillas) {
      campoActual += "\n";
    } else {
      campos.push_back(campoActual); 

      if (primeraFila) {
	primeraFila = false;
      } else if (campos.size() > columnaObjetivo) {
	try {
	  TipoClave clave;

	  // Evaluamos el tipo de dato que espera el unordered_map
	  if constexpr (is_same_v<TipoClave, unsigned long long>) {
	    clave = stoull(campos[columnaObjetivo]);
	  } 
	  else if constexpr (is_same_v<TipoClave, string>) {
	    clave = campos[columnaObjetivo];
	  }

	  // Si la clave no existe, la crea con valor 0 y le suma 1.
	  // Si ya existe, simplemente le suma 1 a su frecuencia actual.
	  mapa[clave]++;

	  lineasProcesadas++;
	} catch (const invalid_argument& e) {
	  cerr << "Error: Se intento parsear un texto no numerico en la linea " << lineasProcesadas + 2 
	       << ". Valor de columna: " << campos[columnaObjetivo] << endl;
	} catch (const out_of_range& e) {
	  cerr << "El ID numerico es demasiado grande en la linea " << lineasProcesadas + 2 << endl;
	}
      }
      campos.clear();
      campoActual = "";
    }
    if(lineasProcesadas == 10000*checkpoint){
      cout << tipo_tabla << ";" << lineasProcesadas << ";";
      auto end = chrono::high_resolution_clock::now();
	  
      double running_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  
      running_time *= 1e-9;
	  
      cout<< running_time << endl;
      checkpoint++;
    }
  }
  archivo.close();
   
}
