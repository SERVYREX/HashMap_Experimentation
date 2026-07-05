#include <iostream>
#include <chrono>
#include "../include/tabla_hash_abierta.h"
#include "../include/tabla_hash_cerrada.h"
#include "../include/lectura_csv.h"

using namespace std;


int main(){

  //Ruta del dataset a utilizar
  string data = "../Data/auspol2019.csv";

  //4 instancias de tablas con hashing abierto con 2 funciones hash distintas para cada tipo de clave
  
  //Tabla que usa user_id como clave
  TablaHashAbierta<unsigned long long, int, int> hashAbierto1(180000);
  TablaHashAbierta<unsigned long long, int, int, 2> hashAbierto2(180000);

  //Tabla que usa user_screen_name como clave
  TablaHashAbierta<string, int, int, 3> hashAbierto3(180000);
  TablaHashAbierta<string, int, int, 4> hashAbierto4(180000);

  //Construccion de la tabla hash abierta
  
  cargarUsuariosDesdeCSV<unsigned long long>(data, hashAbierto1, false,"moduloUserId");

  cargarUsuariosDesdeCSV<unsigned long long>(data, hashAbierto2, false,"aureaUserId");

  cargarUsuariosDesdeCSV<string>(data, hashAbierto3, true,"moduloUserName");
 
  cargarUsuariosDesdeCSV<string>(data, hashAbierto4, true,"aureaUserName");

  
  //Memoria usada en bytes por las tablas segun el tipo de clave
  cout << "Memoria usada por hashing abierto (User ID): "<< hashAbierto1.memoriaUsada() << " Bytes" << endl;
  cout << "Memoria usada por hashing abierto (User Screen Name): "<< hashAbierto4.memoriaUsada() << " Bytes" << endl;
}






