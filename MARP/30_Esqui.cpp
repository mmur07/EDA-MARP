
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(std::priority_queue<int, std::vector<int>, std::greater<int>> qAlturas, std::priority_queue<int, std::vector<int>, std::greater<int>> qEsquies) {
    int diffAlturas = 0;
    int currAlt, currEsq;
    while (!qAlturas.empty()) {
        currAlt = qAlturas.top();
        currEsq = qEsquies.top();
        qAlturas.pop();
        qEsquies.pop();
        diffAlturas += (abs(currAlt - currEsq));
    }

    return diffAlturas;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int nPersonas;
    std::cin >> nPersonas;

    if (nPersonas == 0)
        return false;

    std::priority_queue<int, std::vector<int>, std::greater<int>> qAlturas, qEsquies;
    int aux;

    for (int k = 0; k < nPersonas; k++) {
        std::cin >> aux;
        qAlturas.push(aux);
    }

    for (int k = 0; k < nPersonas; k++) {
        std::cin >> aux;
        qEsquies.push(aux);
    }

    std::cout << resolver(qAlturas, qEsquies) << "\n";

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
