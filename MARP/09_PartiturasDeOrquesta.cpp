
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>

struct grupoInstrumento {
private:
    long int nPartituras = 1;
    long double nMusicos;
public:
    long int musicosPorPart = 0;
    grupoInstrumento(long int nMus) {
        nMusicos = nMus;
        musicosPorPart = nMusicos;
    }
    void sumPartitura() {
        nPartituras++;

        musicosPorPart = ceil(nMusicos / nPartituras);
    }
    bool operator< (const grupoInstrumento& b) const {
        return (musicosPorPart < b.musicosPorPart);
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
grupoInstrumento resolver(long int partiturasSobrantes, std::priority_queue<grupoInstrumento> cola) {
    for (long int k = 0; k < partiturasSobrantes; k++) {
        grupoInstrumento top = cola.top();
        top.sumPartitura();
        cola.pop();
        cola.push(top);
    }
    return cola.top();
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    long int nPartituras = 0, nInstrumentos = 0;

    std::cin >> nPartituras;

    if (!std::cin)  // fin de la entrada
        return false;

    std::cin >> nInstrumentos;

    std::priority_queue<grupoInstrumento> cola;
    for (long int k = 0; k < nInstrumentos; k++) {
        long int nMusicos;
        std::cin >> nMusicos;
        cola.push(grupoInstrumento(nMusicos));
    }
    std::cout << resolver(nPartituras - nInstrumentos, cola).musicosPorPart << "\n";

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
