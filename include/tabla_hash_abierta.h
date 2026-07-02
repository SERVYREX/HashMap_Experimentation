#pragma once
#include <iostream>
#include "funciones_hash.h"
using namespace std;


//Definimos la estructura nodo
template<typename TipoClave, typename TipoValor>
struct Nodo{
  TipoClave clave;
  TipoValor valor;

 
  Nodo* siguiente;
  Nodo(const TipoClave& c, const TipoValor& v){
    clave = c;
    valor = v;
    siguiente = nullptr;
  }
};

//Clase tabla hash abierta, basada en un arreglo de punteros a nodos
template<typename TipoClave,typename TipoValor, typename Largo, int TipoHash = 1>
class TablaHashAbierta{
private:
  Nodo<TipoClave,TipoValor>** tabla;
  Largo largoTabla;
  Largo cantidadElementos;

  
  //Evaluamos las condiciones para el tipo de hashing a utilizar
  Largo calcularIndice(const TipoClave& clave){
    
    if constexpr (TipoHash == 1) {

      return modulo(clave, largoTabla);

    }
    else if constexpr (TipoHash == 2) {

      return hashMult(clave, largoTabla);

    }
    else if constexpr (TipoHash == 3) {

      return hashStringModulo(clave, largoTabla);

    }
    else if constexpr (TipoHash == 4) {

      return hashStringMult(clave, largoTabla);

    }
    else {
      cout << "Tipo de hash Invalido (Seleccione valores de 1-4)" << endl;
      return 0;
    }
  }

  
  //Implementacion de rehash cuando sea necesaria
  void rehash(){
    //Calculamos el largo nuevo y guardamos el viejo
    Largo largoViejo = largoTabla;
    Largo nuevoLargo = siguientePrimo(largoTabla * 2);
    largoTabla = nuevoLargo;
    
    //Creamos otra tabla con nuevo largo y seteamos sus referencias  a null
    
    Nodo<TipoClave,TipoValor>** nuevaTabla = new Nodo<TipoClave, TipoValor>*[nuevoLargo];
    for(Largo i = 0; i<nuevoLargo; i++)
      nuevaTabla[i] = nullptr;

    // Movemos todos los nodos de la tabla antigua a la nueva recalculando los indices con el nuevo largo 
    for(Largo i = 0; i<largoViejo; i++){
      Nodo<TipoClave,TipoValor>* actual = tabla[i];

      while(actual){
	Nodo<TipoClave,TipoValor>* siguiente = actual->siguiente;
	Largo nuevoIndice = calcularIndice(actual->clave);

	actual->siguiente = nuevaTabla[nuevoIndice];
	nuevaTabla[nuevoIndice] = actual;

	actual = siguiente;
      }
    }
    //Eliminamos la tabla vieja y asignamos la nueva
    delete[] tabla;

    tabla = nuevaTabla;
    
  }

  bool esPrimo(Largo n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (Largo i = 3; i * i <= n; i += 2) {
      if (n % i == 0)
	return false;
    }

    return true;
  }

  Largo siguientePrimo(Largo n) {
    if (n <= 2)
      return 2;

    n++;

    if (n % 2 == 0)
      n++;

    while (!esPrimo(n))
      n += 2;

    return n;
  }
    
  
  //Creamos el arreglo y llenamos sus espacios con referencias nulas

public:
  TablaHashAbierta(Largo largo){
    largoTabla = largo;
    cantidadElementos = 0;
    tabla = new Nodo<TipoClave,TipoValor>*[largoTabla];
    
    for(Largo i = 0; i<largoTabla; i++){
      tabla[i] = nullptr;
    }
  }

  //Destructor 
  ~TablaHashAbierta(){

    for(size_t i=0;i<largoTabla;i++){

      Nodo<TipoClave,TipoValor>* actual = tabla[i];

      while(actual){

	Nodo<TipoClave,TipoValor>* borrar = actual;

	actual = actual->siguiente;

	delete borrar;

      }

    }

    delete[] tabla;

  }

  bool insertar(const TipoClave & clave, const TipoValor& valor){
    Largo indice = calcularIndice(clave);

    //Creamos un nodo con la inforamcion actual del indice calculado
    Nodo<TipoClave, TipoValor>* actual = tabla[indice];

    //Recorremos las referencias del nodo y sila clave actual es igual a la clave a insertar, reemplazamos su valor, no permitimos duplicados
    while(actual != nullptr){
      if(actual-> clave == clave){
	actual-> valor = valor;
	return true;
      }
      
      actual = actual-> siguiente;
    }

    if(factorCarga() > 0.75){
      rehash();
      indice = calcularIndice(clave);
    }
 

    //En caso de no encontrar la misma clave, creamos un nuevo nodo con la informacion a insertar y lo insertamos al inicio para asegurar tiempo constante en insercion 
    Nodo<TipoClave, TipoValor>* nuevo = new Nodo<TipoClave,TipoValor>(clave,valor);
    nuevo->siguiente = tabla[indice];
    tabla[indice] = nuevo;
    cantidadElementos++;
    return true;
  }

  Nodo<TipoClave,TipoValor>* buscar(const TipoClave& clave){
    //Calculamos el indice en el cual deberia estar nuestra clave
    Largo indice = calcularIndice(clave);

    
    //Recorremos todos los nodos del indice encontrado y comparamos 
    Nodo<TipoClave,TipoValor>* actual = tabla[indice];
    while(actual!= nullptr){
      if(actual-> clave == clave){
	return actual;
      }
      actual = actual->siguiente;
    }
    return nullptr;
  }

  //Devolvemos la el valor usando la referencia dada por "obtener"
  TipoValor obtener(const TipoClave& clave){
    Nodo<TipoClave, TipoValor>* nodo = buscar(clave);
    
    if(nodo != nullptr){
      return nodo-> valor;
    }
    return TipoValor{};
  }

  
  bool eliminar(const TipoClave& clave){
    Largo indice = calcularIndice(clave);
    Nodo<TipoClave, TipoValor>* actual = tabla[indice];
    Nodo<TipoClave, TipoValor>* anterior = nullptr;

    //Recorremos la lista buscando la clave y reorganizamos los punteros para no romper la lista enlazada
    while(actual!= nullptr){
      
      if(actual->clave == clave){
	
	if(anterior == nullptr){
	  tabla[indice] = actual-> siguiente;
	}
	else{
	  anterior->siguiente = actual->siguiente;
	}
	delete actual;
	cantidadElementos--;
	return true;
      }
      anterior = actual;
      actual = actual->siguiente;
    }
    return false;
  }

  Largo size(){
    return cantidadElementos;
  }

  //Funcion que devuelve el factor de carga considerando un elemento mas para corroborar entes de la insercion
  double factorCarga(){
    return (double)(cantidadElementos + 1) / largoTabla;
  }
    
};
