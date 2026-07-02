#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "../include/lectura_csv.h"

using namespace std;

int main() {
    TablaHashCerrada<unsigned long long, int, unsigned long long, 5> tablaIds;

    // El tercer parámetro en 'false' indica que NO use screen_name (usará user_id)
    cargarUsuariosDesdeCSV<unsigned long long>("../Data/auspol2019.csv", tablaIds, false);

    // Buscar un ID de prueba (ej: PIPELINEPETE del primer tweet)
    cout << "Tweets del ID 92484856: " << tablaIds.obtener(92484856ULL) << endl;

    TablaHashCerrada<string, int, unsigned long long, 8> tablaNames;

    // El tercer parámetro en 'true' indica que SÍ use screen_name
    cargarUsuariosDesdeCSV<string>("../Data/auspol2019.csv", tablaNames, true);

    // Buscar un nombre de usuario de prueba (ej: jocksjig)
    cout << "Tweets de @jocksjig: " << tablaNames.obtener("jocksjig") << endl;

    return 0;
}
