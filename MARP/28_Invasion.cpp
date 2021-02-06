
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(std::priority_queue<int, std::vector<int>, std::greater<int>> &qEnemigos, std::priority_queue<int, std::vector<int>, std::greater<int>> &qAliados) {
    int nCapturadas = 0;

    while (!qAliados.empty()) {
        if (qEnemigos.top() <= qAliados.top()) {
            qEnemigos.pop();
            nCapturadas++;
        }
        qAliados.pop();
    }

    return nCapturadas;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int nCiudades;
    std::cin >> nCiudades;
    if (!std::cin)  // fin de la entrada
        return false;

    std::priority_queue<int, std::vector<int>, std::greater<int>> qEnems, qAli;
    int aux;
    for (int k = 0; k < nCiudades; k++) {
        std::cin >> aux; 
        qEnems.push(aux);
    }

    for (int k = 0; k < nCiudades; k++) {
        std::cin >> aux;
        qAli.push(aux);
    }

    std::cout << resolver(qEnems, qAli) << "\n";

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
