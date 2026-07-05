#include <iostream>
#include "../include/lectura_csv.h"
#include <unordered_map>

using namespace std;

int main(){

  //Ruta del dataSet
  string data = "../Data/auspol2019.csv";

  //Instancia mapa de STL

  unordered_map<unsigned long long, int> tweetsCount;

  //Llenamos la tabla hash con los datos
  cargarUsuariosDesdeCSV(data, tweetsCount, false, "unorderedMapSTL");

}
