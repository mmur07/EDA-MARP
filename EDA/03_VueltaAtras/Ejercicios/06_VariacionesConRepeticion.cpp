// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

bool es_Solucion(const int& n, std::vector<int>solucionActual) {
    return solucionActual[n - 1] != -1;
}

void resolver_aux(int k, const int &n, const int &m, std::vector<int> &solucionActual) {
    if (es_Solucion(n, solucionActual)) {
        for (int k = 0; k < n; k++) {
            std::cout << (char)('a' + solucionActual[k]);
        }
        std::cout << "\n";
    }
    else {
        for (int l = 0; l < m; l++) {
            solucionActual[k] = l;
            resolver_aux(k + 1, n, m, solucionActual);
            solucionActual[k] = -1;
        }
    }
}


// función que resuelve el problema
void resolver(const int &n, const int &m) {
    //n = tamaño de la combinacion
    //m = elementos disponibles
    std::vector<int> solucionActual = std::vector<int>(n, -1);
    resolver_aux(0, n, m, solucionActual);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int n, m;
    std::cin >> m;
    if (!std::cin)
        return false;
    std::cin >> n;

    resolver(n, m);
    std::cout << "\n";

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