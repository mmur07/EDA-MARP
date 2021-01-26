// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <limits>

void vuelta_atras(int i, const std::vector<std::vector<int>>& trabajadores, int &puntuacionActual, int &mejor_solucion, std::vector<bool> &ocupados) {
    i++;

    if (i < trabajadores.size()) {
        for (int k = 0; k < trabajadores.size(); k++) {
            if (trabajadores[i][k] != 0 && ocupados[k] == false) { //poda
                puntuacionActual += trabajadores[i][k];
                ocupados[k] = true;
                vuelta_atras(i, trabajadores,puntuacionActual, mejor_solucion, ocupados);
                puntuacionActual -= trabajadores[i][k];
                ocupados[k] = false;
            }
        }
    }
    else {
        if (puntuacionActual < mejor_solucion) mejor_solucion = puntuacionActual;
    }
}

// función que resuelve el problema
int resolver(const std::vector<std::vector<int>> &trabajadores) {
    int costeMin = std::numeric_limits<int>().max();
    int puntuacionActual = 0;
    std::vector<bool> ocupados = std::vector<bool>(trabajadores.size(), false);
    vuelta_atras(-1, trabajadores, puntuacionActual, costeMin, ocupados);

    return costeMin;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nTrabajadores = 0;
    std::cin >> nTrabajadores;
    if (nTrabajadores == 0)
        return false;
    std::vector<std::vector<int>> trabajadores = std::vector<std::vector<int>>(nTrabajadores);
    int aux;
    for (int k = 0; k < nTrabajadores; k++) {
        for (int l = 0; l < nTrabajadores; l++) {
            std::cin >> aux;
            trabajadores[k].push_back(aux);
        }
    }

    int costeMin = resolver(trabajadores);
    if (costeMin == std::numeric_limits<int>().max()) std::cout << "FESTIVO\n";
    else std::cout << costeMin << "\n";

    // escribir sol


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