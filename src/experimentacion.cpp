#include <iostream>
#include "../include/tabla_hash_abierta.h"
#include "../include/lectura_csv.h"

using namespace std;

int main(){

  //Ruta del dataset a utilizar
  string data = "../Data/auspol2019.csv";

  //4 instancias de tablas con hashing abierto con 2 funciones hash distintas para cada tipo de clave 
  
  TablaHashAbierta<int, int, int> hashAbierto1(10007);
  TablaHashAbierta<int, int, int, 2> hashAbierto2(10007);
  TablaHashAbierta<string, int, int, 3> hashAbierto3(10007);
  TablaHashAbierta<string, int, int, 4> hashAbierto4(10007);

  //Construccion de la tabla hash
  
  cargarUsuariosDesdeCSV<int>(data, hashAbierto1, false);
  cargarUsuariosDesdeCSV<int>(data, hashAbierto2, false);
  cargarUsuariosDesdeCSV<string>(data, hashAbierto3, true);
  cargarUsuariosDesdeCSV<string>(data, hashAbierto4, true);

  cout<<hashAbierto1.obtener(92484856ULL) << endl;
  cout<<hashAbierto2.obtener(92484856) << endl;
  cout<<hashAbierto3.obtener("jocksjig") << endl;
  cout<<hashAbierto4.obtener("jocksjig") << endl;
 

}
