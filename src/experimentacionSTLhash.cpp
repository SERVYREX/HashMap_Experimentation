#include <iostream>
#include "../include/lectura_csv.h"
#include <unordered_map>

using namespace std;

int main(){

  //Ruta del dataSet
  string data = "../Data/auspol2019.csv";

  //Instancia mapa de STL

  unordered_map<unsigned long long, int> tweetsCountID;
  unordered_map<string,int> tweetsCountUserName;
  
  //Llenamos la tabla hash con los datos
  cargarUsuariosDesdeCSV(data, tweetsCountID, false, "unorderedMapSTL_ID");
  cargarUsuariosDesdeCSV(data, tweetsCountUserName, true,"unorderedMapSTL_userName");
    
 
}
