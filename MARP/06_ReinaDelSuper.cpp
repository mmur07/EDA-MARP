
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <queue>
//
//  IndexPQ.h
//
//  Implementación de colas con prioridad mediante montículos.
//  Los elementos son enteros de 0 a N-1 que tienen asociada una prioridad
//  dentro de la cola. La prioridad de un elemento puede ser modificada
//  con coste en O(log N).
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

struct par {
    int id;
    int time;
    par(int i, int t) : id(i), time(t) {};

    bool operator < (const par& b) const{
        return (time > b.time || (time == b.time && id > b.id));
    }

    bool operator > (const par& b) const{
        return (time < b.time || (time == b.time && id < b.id));
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(std::priority_queue<par> &queueCajas, std::queue<int> &clientes) {
    while (!clientes.empty()) {
        par p = queueCajas.top();
        p.time += clientes.front();
        queueCajas.pop();
        clientes.pop();
        queueCajas.push(p);
    }
    return queueCajas.top().id;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int nCajas, nClientes;
    std::cin >> nCajas;

    if (!std::cin || nCajas == 0)  // fin de la entrada
        return false;

    std::cin >> nClientes;

    std::queue<int> clientes;
    for (int k = 0; k < nClientes; k++) {
        int aux;
        std::cin >> aux;
        clientes.push(aux);
    }
    std::priority_queue<par> cajas;
    for (int k = 0; k < nCajas; k++) cajas.push(par(k + 1, 0));

    std::cout << resolver(cajas, clientes) << "\n";

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
