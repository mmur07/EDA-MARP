
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
long long int resolver(std::priority_queue<long long int, std::vector<long long int>, std::greater<long long int>> &q) {
    long long int esfuerzo = 0;
    while (q.size() > 1) {
        long long int elem1 = q.top();
        q.pop();
        long long int elem2 = q.top();
        q.pop();
        long long int result = elem1 + elem2;
        esfuerzo += result;
        q.push(result);
    }
    return esfuerzo;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int sizeVec = 0;
    std::cin >> sizeVec;

    if (sizeVec == 0)  // fin de la entrada
        return false;

    std::priority_queue<long long int, std::vector<long long int>, std::greater<long long int>> q;
    for (int k = 0; k < sizeVec; k++) {
        long long int aux;
        std::cin >> aux;
        q.push(aux);
    }

    std:: cout << resolver(q) << "\n";

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
