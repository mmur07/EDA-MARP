
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>
struct Operacion {
    int ini;
    int fin;
    bool operator> (const Operacion& other) const{
        return ini > other.ini;
    }
};

int minOperacionesNecesarias(const int &C, const int &F, std::priority_queue<Operacion, std::vector<Operacion>, std::greater<Operacion>>& cola) {
    int operacionesNecesarias = 0;
    int endIni = -1;
    bool endReached = false;

    //Encontramos la primera posicion.
    while (!cola.empty() && cola.top().ini <= C) {
        if (cola.top().fin > endIni) endIni = cola.top().fin;
        cola.pop();
    }
    operacionesNecesarias++;
    if (endIni == -1) return -1; //no se ha encontrado inicio valido.
    if (endIni >= F) return operacionesNecesarias;
    int currentEnd = endIni, nextEnd = -1;
    while (!cola.empty() && !endReached) {
        operacionesNecesarias++;

        while (!cola.empty() && cola.top().ini <= currentEnd) {
            if (cola.top().fin > nextEnd) nextEnd = cola.top().fin;
            cola.pop();
        }
        if (nextEnd == -1) return -1;
        currentEnd = nextEnd;
        nextEnd = -1;
        if (currentEnd >= F) endReached = true;
    }
    if (!endReached) return -1;
    return operacionesNecesarias;
}

bool resuelveCaso() {

    int C, F, numOp;
    std::cin >> C >> F >> numOp;
    if (C == 0 && F == 0 && numOp == 0)  // fin de la entrada
        return false;
    std::priority_queue<Operacion, std::vector<Operacion>, std::greater<Operacion>> cola;

    int ini, fin;
    Operacion newOp;
    for (int k = 0; k < numOp; k++) {
        std::cin >> ini >> fin;
        newOp.ini = ini;
        newOp.fin = fin;
        cola.push(newOp);
    }

    int num = minOperacionesNecesarias(C, F, cola);
    if (num == -1) std::cout << "Imposible\n";
    else std::cout << num << "\n";
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
