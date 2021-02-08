
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

struct Usuario {
    int id;
    int frecuencia;
    int frecOriginal;
    int vecesEncontrada = 1;
    bool operator>(const Usuario& other) const {
        if (frecuencia == other.frecuencia) return id > other.id;
        else return frecuencia > other.frecuencia;
    }
};

bool resuelveCaso() {

    int nUsuarios;
    std::cin >> nUsuarios;
    if (nUsuarios == 0)
        return false;
    int nId, nFrec;
    priority_queue<Usuario, std::vector<Usuario>, greater<Usuario>> cola;
    for (int k = 0; k < nUsuarios; k++) {
        std::cin >> nId >> nFrec;
        cola.push({ nId, nFrec, nFrec });
    }

    int nOperaciones;
    std::cin >> nOperaciones;
    for (int k = 0; k < nOperaciones; k++) {
        Usuario top = cola.top();
        std::cout << top.id << "\n";
        top.vecesEncontrada++;
        top.frecuencia = top.frecOriginal * top.vecesEncontrada;
        cola.pop();
        cola.push(top);
    }
    std::cout << "---\n";
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
