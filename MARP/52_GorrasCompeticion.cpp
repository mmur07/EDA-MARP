
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

bool resuelveCaso() {

    int nGrupos;
    std::cin >> nGrupos;
    if (nGrupos == 0)
        return false;
    priority_queue<int, vector<int>, greater<int>> cola;
    int aux;
    for (int k = 0; k < nGrupos; k++) {
        std::cin >> aux;
        cola.push(aux);
    }
    
    int gorrasNecesarias = 0;

    while (cola.size() > 1) {
        int equipo1 = cola.top();
        cola.pop();

        int equipo2 = cola.top();
        cola.pop();

        cola.push(equipo1 + equipo2);
        gorrasNecesarias += equipo1 + equipo2;
    }
    std::cout << gorrasNecesarias << "\n";
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
