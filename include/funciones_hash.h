#include <iostream>
#include <string>
using namespace std;

//Usamos un template para tratar con numeros muy grandes
template <typename TipoClave, typename Largo>

// ##====Funciones para hashear valores numericos====##

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
  int h1 = modulo(clave,largoTabla);
  int h2 = modulo_h2(clave,largoTabla);
  return (h1 + (intento*h2))% largoTabla;
}


//Funcion hash usando constante aurea
template <typename TipoClave, typename Largo>
Largo hashMult(TipoClave clave, Largo largoTabla){
  //Constante aurea para 64 bits
  unsigned long long aurea = 11400714819323198485ULL;
  unsigned long long hash = clave * aurea;
  return hash%largoTabla;
}

//Funcion hash usando constante aurea 2, necesaria en casos de double hashing
template <typename TipoClave, typename Largo>
Largo hashMult_h2(TipoClave clave, Largo saltoPrimo){
  //Mezclamos bits usando XOR para asegurar la independencia de la primera funcion, casteamos a ull para tener coherencia con el desplazamiento
  TipoClave claveMezclada = static_cast<unsigned long long>(clave) ^ 
                           (static_cast<unsigned long long>(clave) >> 32);
  return saltoPrimo - (claveMezclada % saltoPrimo);
}
template <typename TipoClave, typename Largo>
Largo doubleHashMult(TipoClave clave, int intento, Largo largoTabla, Largo saltoPrimo){
  Largo h1 = hashMult(clave, largoTabla);
  Largo h2 = hashMult(clave, saltoPrimo);
  return (h1 + (intento*h2)% largoTabla);
}

// ##====Funciones para hashear strings====##







