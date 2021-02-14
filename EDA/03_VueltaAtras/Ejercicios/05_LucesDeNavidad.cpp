// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

bool esSolucion(int n, const int& longitudLinea) {
    return (n >= longitudLinea);
}

bool esPrometedor(int n, std::vector<int>&bombillasUsadas, std::vector<int> &solucionActual, int &consumoActual, const int& consumoMax) {
    if (consumoActual > consumoMax) return false;

    if (n > 1 && solucionActual[n] == solucionActual[n - 1] && solucionActual[n] == solucionActual[n - 2]) return false;

    int restoBombillas = 0;

    for (int k = 0; k < bombillasUsadas.size(); k++) {
        if (k != solucionActual[n]) restoBombillas += bombillasUsadas[k];
    }

    if (bombillasUsadas[solucionActual[n]] > restoBombillas + 1) return false;

    return true;
}

void resolver_aux(int n, int& consumoActual, std::vector<int>& solucionActual, std::vector<int> &bombillasUsadas, const int& longitudLinea, const int& nColores, const int& consumoMax, const std::vector<int> consumoColores, int& nCombinaciones) {
    if (esSolucion(n, longitudLinea)) {
        nCombinaciones++;
        /*for (int k = 0; k < solucionActual.size(); k++) {
            std::cout << solucionActual[k] << " ";
        }
        std::cout << "\n";*/
    }

    else {
        for (int k = 0; k < nColores; k++) {
            solucionActual[n] = k;
            consumoActual += consumoColores[k];
            bombillasUsadas[k]++;
            if (esPrometedor(n, bombillasUsadas, solucionActual, consumoActual, consumoMax)) {
                resolver_aux(n + 1, consumoActual, solucionActual, bombillasUsadas, longitudLinea, nColores, consumoMax, consumoColores, nCombinaciones);
            }
            bombillasUsadas[k]--;
            consumoActual -= consumoColores[k];
            solucionActual[n] = -1;
        }
    }
}

// función que resuelve el problema
int resolver(const int& longitudLinea, const int& nColores, const int& consumoMax, const std::vector<int> consumoColores) {
    int nCombinaciones = 0;
    int consumoActual = 0;
    std::vector<int>solucionActual(longitudLinea, -1);
    std::vector<int>bombillasUsadas(nColores, 0);
    resolver_aux(0, consumoActual, solucionActual, bombillasUsadas, longitudLinea, nColores, consumoMax, consumoColores, nCombinaciones);
    return nCombinaciones;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int longitudLinea, nColores, consumoMax, aux;

    std::cin >> longitudLinea;
    if (longitudLinea == 0)
        return false;
    std::cin >> nColores >> consumoMax;

    std::vector<int> consumoColores;
    for (int k = 0; k < nColores; k++) {
        std::cin >> aux;
        consumoColores.push_back(aux);
    }

    int sol = resolver(longitudLinea, nColores, consumoMax, consumoColores);
    std::cout << sol << "\n";

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
