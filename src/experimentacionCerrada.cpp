#include <iostream>
#include <chrono>
#include "../include/tabla_hash_abierta.h"
#include "../include/tabla_hash_cerrada.h"
#include "../include/lectura_csv.h"

using namespace std;


int main(){

  //Ruta del dataset a utilizar
  string data = "../Data/auspol2019.csv";

  // 8 instancias de tablas con hashing cerrado con distintas funciones para el manejo de colisiones segun cada tipo de clave
  
  //Tabla que usa user_id como clave
  TablaHashCerrada<unsigned long long, int, int, 1> hashCerrado1;
  TablaHashCerrada<unsigned long long, int, int, 2> hashCerrado2;
  TablaHashCerrada<unsigned long long, int, int, 5> hashCerrado5;
  TablaHashCerrada<unsigned long long, int, int, 6> hashCerrado6;

  //Tabla que usa user_screen_name como clave
  TablaHashCerrada<string, int, int, 3> hashCerrado3;
  TablaHashCerrada<string, int, int, 4> hashCerrado4;

  TablaHashCerrada<string, int, int, 7> hashCerrado7;
  TablaHashCerrada<string, int, int, 8> hashCerrado8;

  
  //Construccion de tablas hash cerradas
  
  
  cargarUsuariosDesdeCSV<unsigned long long>(data, hashCerrado1, false,"dobleHashModuloUserId");
 
  cargarUsuariosDesdeCSV<unsigned long long>(data, hashCerrado2, false,"dobleHashAureaUserId");

  cargarUsuariosDesdeCSV<string>(data, hashCerrado3, true,"dobleHashModuloUserName");

  cargarUsuariosDesdeCSV<string>(data, hashCerrado4, true,"dobleHashAureaUserName");

  cargarUsuariosDesdeCSV<unsigned long long>(data, hashCerrado5, false,"linearProbingUserId");

  cargarUsuariosDesdeCSV<unsigned long long>(data, hashCerrado6, false,"quadraticProbingUserId");
  
  cargarUsuariosDesdeCSV<string>(data, hashCerrado7, true,"linearProbingUserName");

  cargarUsuariosDesdeCSV<string>(data, hashCerrado8, true,"quadraticProbingUserName");

  //Memoria usada en bytes por las tablas segun el tipo de clave
  cout << "Memoria usada por hashing cerrado (User ID): " << hashCerrado1.memoriaUsada() << endl;
  cout << "Memoria usada por hashing cerrado (User Screen Name ID): " << hashCerrado8.memoriaUsada() << endl;
}


