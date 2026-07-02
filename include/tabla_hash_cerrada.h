#pragma once
#include <iostream>
#include <vector> 
#include "funciones_hash.h"
using namespace std;

template<typename TipoClave, typename TipoValor>
struct NodoC{
  TipoClave clave;
  TipoValor valor;
  bool eliminado = false;

  NodoC(){
    clave = TipoClave{};
    valor = TipoValor{};
  }
};

// Clase tabla hash cerrada
template<typename TipoClave, typename TipoValor, typename Largo, int TipoHash = 1>
class TablaHashCerrada {
private:
  Largo largoTabla;
  Largo cantidadElementos;
  vector<NodoC<TipoClave, TipoValor>> tabla; 
  Largo saltoPrimo;

  // Evaluamos las condiciones para el tipo de hashing a utilizar
  Largo calcularIndice(const TipoClave& clave, const Largo intento) {
    if constexpr (TipoHash == 1) {
      return doubleHashModulo(clave, intento, largoTabla, saltoPrimo);
    }
    else if constexpr (TipoHash == 2) {
      return doubleHashMult(clave, intento, largoTabla, saltoPrimo);
    }
    else if constexpr (TipoHash == 3) {
      return doubleHashStringModulo(clave, intento, largoTabla, saltoPrimo);
    }
    else if constexpr (TipoHash == 4) {
      return doubleHashStringMult(clave, intento, largoTabla, saltoPrimo);
    }
    else if constexpr (TipoHash == 5) {
      return linearProbing(clave, intento, largoTabla);
    }
    else if constexpr (TipoHash == 6) {
      return quadraticProbing(clave, intento, largoTabla);
    }
    else if constexpr (TipoHash == 7) {
      return linearProbingString(clave, intento, largoTabla);
    }
    else if constexpr (TipoHash == 8) {
      return quadraticProbingString(clave, intento, largoTabla);
    }
    else {
      cout << "Tipo de hash Invalido (Seleccione valores de 1-4)" << endl;
      return 0;
    }
  }
  
  void rehash() {
    Largo antiguoLargo = largoTabla;
    vector<NodoC<TipoClave, TipoValor>> tablaAntigua = tabla;

    // Calculamos el nuevo tamaño de la tabla y actualizamos los primos necesarios
    largoTabla = siguientePrimo(largoTabla * 2);
    saltoPrimo = primoMenor(largoTabla);
    
    // Reiniciamos el contenedor principal vaciándolo por completo
    tabla.assign(largoTabla, NodoC<TipoClave, TipoValor>());
    cantidadElementos = 0;

    // Reinsertamos todos los elementos válidos que estaban en la vieja tabla
    for (Largo i = 0; i < antiguoLargo; i++) {
      if (tablaAntigua[i].clave != TipoClave{} && !tablaAntigua[i].eliminado) {
        insertar(tablaAntigua[i].clave, tablaAntigua[i].valor);
      }
    }
  }
  
  bool esPrimo(Largo n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    
    for (Largo i = 3; i * i <= n; i += 2) {
      if (n % i == 0) return false;
    }
    
    return true;
  }
  
  Largo siguientePrimo(Largo n) {
    if (n <= 2) return 2;
    
    n++;
    if (n % 2 == 0) n++;
    
    while (!esPrimo(n)) {
      n += 2;
    }
    
    return n;
  }

  Largo primoMenor(Largo n) {
    n--;
    if (n % 2 == 0) n--;
    while (n > 2 && !esPrimo(n)) {
        n -= 2;
    }
    return n;
  }
  
public:

  TablaHashCerrada() : largoTabla(1009), cantidadElementos(0), tabla(1009) {
    saltoPrimo = primoMenor(1009);
  }

  bool insertar(const TipoClave & clave, const TipoValor& valor){
    // Validamos factor de carga previo al cálculo de posiciones
    if(factorCarga() > 0.75){
      rehash();
    }

    Largo intento = 0;
    Largo posicionInsertar = -1; 

    while(intento < largoTabla){
      Largo indice = calcularIndice(clave, intento);

      // Celda vacía disponible
      if(tabla[indice].clave == TipoClave{} && !tabla[indice].eliminado){
        if(posicionInsertar == -1)
	  posicionInsertar = indice;
        break; 
      }

      // La clave ya existe, por lo que se actualiza su valor
      if(tabla[indice].clave == clave && !tabla[indice].eliminado){
        tabla[indice].valor = valor;
        return true;
      }

      // Celda disponible pero marcada como eliminada
      if(tabla[indice].eliminado && posicionInsertar == -1){
        posicionInsertar = indice;
      }

      intento++;
    }
    
    // Si encontramos una ranura disponible insertamos los valores del nodo
    if(posicionInsertar != -1){
      tabla[posicionInsertar].clave = clave;
      tabla[posicionInsertar].valor = valor;
      tabla[posicionInsertar].eliminado = false;
      cantidadElementos++;
      return true;
    }
    
    return false; 
  }
  
  NodoC<TipoClave,TipoValor>* buscar(const TipoClave& clave){
    Largo intento = 0;
    
    while(intento < largoTabla){
      Largo indice = calcularIndice(clave, intento);
      
      // Si la celda está vacía y nunca se ha usado, el elemento no existe
      if(tabla[indice].clave == TipoClave{} && !tabla[indice].eliminado){
        return nullptr;
      }
      
      if(tabla[indice].clave == clave && !tabla[indice].eliminado){
        return &tabla[indice]; // Retornamos el nodo que almacenada a la clave y su valor
      }
      
      intento++;
    }
    return nullptr;
  }
  
  TipoValor obtener(const TipoClave& clave){
    NodoC<TipoClave, TipoValor>* nodo = buscar(clave);
    
    if(nodo != nullptr){
      return nodo->valor;
    }
    return TipoValor{};
  }
  
  bool eliminar(const TipoClave& clave){
    Largo intento = 0;
    
    while(intento < largoTabla){
      Largo indice = calcularIndice(clave, intento);
      
      if(tabla[indice].clave == TipoClave{} && !tabla[indice].eliminado){
        return false; // No existe
      }
      
      if(tabla[indice].clave == clave && !tabla[indice].eliminado){
        tabla[indice].clave = TipoClave{};
        tabla[indice].eliminado = true;
        cantidadElementos--;
        return true;
      }
      
      intento++;
    }
    
    return false;
  }
  
  Largo size(){
    return cantidadElementos;
  }
  
  double factorCarga(){
    return (double)(cantidadElementos + 1) / largoTabla;
  }
};

