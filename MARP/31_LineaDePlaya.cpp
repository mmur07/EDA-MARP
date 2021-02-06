
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

struct Edificio {
    int inicio;
    int final;
    bool operator< (const Edificio& other) const{
        return final< other.final;
    }
    bool operator> (const Edificio& other) const {
        return final> other.final;
    }
};

int numConexiones(std::priority_queue<Edificio, std::vector<Edificio>, std::greater<Edificio>> &cola) {
    int nConexiones = 0;

    while (!cola.empty()) {
        nConexiones++;
        Edificio edificioInicial = cola.top();
        cola.pop();
        while (!cola.empty() && cola.top().inicio < edificioInicial.final) {
            cola.pop();
        }
    }

    return nConexiones;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int nEdificios;
    std::cin >> nEdificios;
    if (nEdificios == 0)  // fin de la entrada
        return false;
    std::priority_queue<Edificio, std::vector<Edificio>, std::greater<Edificio>> cola;
    Edificio nEdi;
    int ini, fin;
    for (int k = 0; k < nEdificios; k++) {
        std::cin >> ini >> fin;
        nEdi.inicio = ini;
        nEdi.final = fin;
        cola.push(nEdi);
    }
    
    std::cout << numConexiones(cola) << "\n";

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
