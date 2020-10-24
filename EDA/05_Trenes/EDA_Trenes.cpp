// Miguel Mur
// VJ43


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include "TiemposEntrada.h"

istream& operator>>(istream& sIn, TiemposEntrada& set)
{
    int h, m, s;
    char aux;
    for (int k = 0; k < set.size(); k++) {
        std::cin >> h >> aux >> m >> aux >> s;
        set.add(TiemposEntrada::Hora(h, m, s));
    }
    return sIn;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nTrenes = 0, nConsultas = 0;

    std::cin >> nTrenes >> nConsultas;

    if (nTrenes == 0 && nConsultas == 0)
        return false;

    TiemposEntrada salidas = TiemposEntrada(nTrenes);
    std::cin >> salidas;

    for (int k = 0; k < nConsultas; k++) {
        int h, m, s;
        char aux;
        std::cin >> h >> aux >> m >> aux >> s;
        TiemposEntrada::Hora hora = TiemposEntrada::Hora(h, m, s);
        if (hora.isIncorrect()) std::cout << "ERROR\n";
        else salidas.findClosestHour(hora);
    }
    std::cout << "---\n";
    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}