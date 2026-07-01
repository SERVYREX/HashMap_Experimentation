#include <iostream>
#include <string>
using namespace std;
  
// ####################################################
// ##====Funciones para hashear valores numericos====##
// ####################################################


//Usamos un template para tratar con numeros muy grandes
template <typename TipoClave, typename Largo>

//Funcion Hash clasica usando modulo
Largo modulo(TipoClave clave, Largo largoTabla){
  return clave % largoTabla;
}
//Funcion hash usando modulo 2, necesaria en casos de double hashing
template <typename TipoClave, typename Largo>
Largo modulo_h2(TipoClave clave, Largo saltoPrimo){
  return saltoPrimo - (clave % saltoPrimo);
}
//Funcion para doble hashing basada en intentos
template <typename TipoClave, typename Largo>
Largo doubleHashModulo(TipoClave clave, int intento, Largo largoTabla, Largo saltoPrimo){
  Largo h1 = modulo(clave,largoTabla);
  Largo h2 = modulo_h2(clave, saltoPrimo);
  return (h1 + (intento*h2))% largoTabla;
}


//Funcion hash usando constante aurea
template <typename TipoClave, typename Largo>
Largo hashMult(TipoClave clave, Largo largoTabla){
  //Constante aurea para 64 bits
  unsigned long long aurea = 11400714819323198485ULL;
  unsigned long long hash = static_cast<unsigned long long>(clave) * aurea;
  return hash%largoTabla;
}


//Funcion hash usando constante aurea 2, necesaria en casos de double hashing
template <typename TipoClave, typename Largo>
Largo hashMult_h2(TipoClave clave, Largo saltoPrimo){
  //Mezclamos bits usando XOR para asegurar la independencia de la primera funcion, casteamos a ull para tener coherencia con el desplazamiento
  unsigned long long claveMezclada = static_cast<unsigned long long>(clave) ^ 
                           (static_cast<unsigned long long>(clave) >> 32);
  return saltoPrimo - (claveMezclada % saltoPrimo);
}

//Funcion para doble hashing basada en intentos
template <typename TipoClave, typename Largo>
Largo doubleHashMult(TipoClave clave, int intento, Largo largoTabla, Largo saltoPrimo){
  Largo h1 = hashMult(clave, largoTabla);
  Largo h2 = hashMult_h2(clave, saltoPrimo);
  return (h1 + intento*h2)% largoTabla;
}





// ##########################################
// ##====Funciones para hashear strings====##
// ##########################################


template <typename Largo>
//Funcion para hashear strings usando modulo
Largo hashStringModulo(const string& clave, Largo largoTabla){
  //Vamos acumulando la suma en hash, y usamos una constante estandar
  unsigned long long hash = 0;
  unsigned long long base = 31;

  //Calculamos el valor del hash usando el valor ascii de cada caracter de la cadena
  for(char c : clave) {
    hash = hash * base + static_cast<unsigned long long>(c);
  }
  return hash % largoTabla;
}

//Funcion usada para el double hashing, misma logica, solo variamos la constante para asegurar independencia
template <typename Largo>
Largo hashStringModulo_h2(const string& clave, Largo saltoPrimo){
  unsigned long long hash = 0;
  unsigned long long base = 37;

  for(char c : clave){
    hash = hash * base + static_cast<unsigned long long>(c);
  }
  return saltoPrimo - (hash % saltoPrimo);
}

template<typename Largo>
Largo doubleHashStringModulo(const string& clave, Largo intento, Largo largoTabla, Largo saltoPrimo){

  Largo h1 = hashStringModulo(clave, largoTabla);
  Largo h2 = hashStringModulo_h2(clave, saltoPrimo);

  return (h1 + intento * h2)% largoTabla;
}


//Funcion para hashear Strings usando la proporcion aurea 
template <typename Largo>
Largo hashStringMult(const string& clave, Largo largoTabla) {
    unsigned long long hash = 0;

    for (char c : clave) {
        hash = hash * 31 + static_cast<unsigned long long>(c);
    }

    // Constante aurea
    unsigned long long aurea = 11400714819323198485ULL;

    hash *= aurea;

    return hash % largoTabla;
}


// Segunda funcion hash para double hashing
template <typename Largo>
Largo hashStringMult_h2(const string& clave, Largo saltoPrimo) {

    unsigned long long hash = 0;

    for (char c : clave) {
        hash = hash * 37 + static_cast<unsigned long long>(c);
    }

    return saltoPrimo - (hash % saltoPrimo);
}


// Double hashing usando multiplicacion
template <typename Largo>
Largo doubleHashStringMult(const string& clave, Largo intento, Largo largoTabla, Largo saltoPrimo) {
    Largo h1 = hashStringMult(clave, largoTabla);
    Largo h2 = hashStringMult_h2(clave, saltoPrimo);

    return (h1 + intento * h2) % largoTabla;
}







