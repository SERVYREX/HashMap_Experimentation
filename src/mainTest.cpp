#include <iostream>
#include "../include/lectura_csv.h"

using namespace std;

int main() {
    string rutaCsv = "../../Data/auspol2019.csv";

    cout << "==========================" << endl;
    cout << "=== PRUEBA CON USER ID ===" << endl;
    cout << "==========================" << endl;
    unordered_map<unsigned long long, int> mapaIds;
    
    // false = extraer user_id
    cargarUsuariosDesdeCSV(rutaCsv, mapaIds, false); 
    
    unsigned long long idPrueba = 92484856ULL;
    // Con unordered_map podemos buscar usando count() antes de acceder
    if (mapaIds.count(idPrueba) > 0) {
        cout << "El ID " << idPrueba << " tiene " << mapaIds[idPrueba] << " tweets." << endl;
    } else {
        cout << "El ID " << idPrueba << " no existe." << endl;
    }
    cout << "Total de usuarios unicos (por ID): " << mapaIds.size() << "\n\n";

    cout << "==============================" << endl;
    cout << "=== PRUEBA CON SCREEN NAME ===" << endl;
    cout << "==============================" << endl;
    unordered_map<string, int> mapaNombres;
    
    // true = extraer user_screen_name
    cargarUsuariosDesdeCSV(rutaCsv, mapaNombres, true); 
    
    string nombrePrueba = "jocksjig";
    if (mapaNombres.count(nombrePrueba) > 0) {
        cout << "El usuario @" << nombrePrueba << " tiene " << mapaNombres[nombrePrueba] << " tweets." << endl;
    } else {
        cout << "El usuario @" << nombrePrueba << " no existe." << endl;
    }
    cout << "Total de usuarios unicos (por nombre): " << mapaNombres.size() << endl;

    return 0;
}