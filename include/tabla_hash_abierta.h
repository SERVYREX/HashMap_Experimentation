#include <iostream>



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
    
  
  //Creamos el arreglo y llenamos sus espacios con referencias nulas

public:
  TablaHashAbierta(Largo largo){
    largoTabla = largo;
   
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

    //En caso de no encontrar la misma clave, creamos un nuevo nodo con la informacion a insertar y lo insertamos al inicio para asegurar tiempo constante en insercion 
    Nodo<TipoClave, TipoValor>* nuevo = new Nodo<TipoClave,TipoValor>(clave,valor);
    nuevo->siguiente = tabla[indice];
    tabla[indice] = nuevo;
    return true;
  }

  bool buscar(const TipoClave& clave){
    //Calculamos el indice en el cual deberia estar nuestra clave
    Largo indice = calcularIndice(clave);

    
    //Recorremos todos los nodos del indice encontrado y comparamos 
    Nodo<TipoClave,TipoValor>* actual = tabla[indice];
    while(actual!= nullptr){
      if(actual-> clave == clave){
	return true;
      }
      actual = actual->siguiente;
    }
    return false;
  }
    
};
