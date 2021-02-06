
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(const std::vector<int> & vAgujeros, int tamParche) {
    std::vector<bool> agujerosCubiertos = std::vector<bool>(vAgujeros.size(), false);
    int currPos = 0, nParches = 0;

    while (currPos < agujerosCubiertos.size()) {
        agujerosCubiertos[currPos] = true;
        int distancia = vAgujeros[currPos];
        currPos++;
        while (currPos < agujerosCubiertos.size() && vAgujeros[currPos] - distancia <= tamParche) {
            agujerosCubiertos[currPos] = true;
            currPos++;
        }
        nParches++;
    }
    return nParches;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int nAgujeros, tamParche;
    std::cin >> nAgujeros;
    if (!std::cin)  // fin de la entrada
        return false;
    std::cin >> tamParche;

    std::vector<int> vAgujeros;
    int aux;
    for (int k = 0; k < nAgujeros; k++) {
        std::cin >> aux;
        vAgujeros.push_back(aux);
    }

    std::cout << resolver(vAgujeros, tamParche) << "\n";

    // escribir sol

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
