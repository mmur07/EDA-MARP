
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

struct Tarea {
    int ini;
    int fin;
    int intervaloRep = -1;

    bool operator> (const Tarea& other)const {
        return ini > other.ini;
    }
};

bool resuelveCaso() {
    int nUnicas, nPeriodicas, tLimite;
    // leer los datos de la entrada
    std::cin >> nUnicas >> nPeriodicas >> tLimite;
    if (!std::cin)  // fin de la entrada
        return false;
    priority_queue<Tarea, std::vector<Tarea>, greater<Tarea>> cola;
    int lecIni, lecFin, lecRep;
    for (int k = 0; k < nUnicas; k++) {
        std::cin >> lecIni >> lecFin;
        cola.push({ lecIni, lecFin });
    }
    for (int k = 0; k < nPeriodicas; k++) {
        std::cin >> lecIni >> lecFin >> lecRep;
        cola.push({ lecIni, lecFin, lecRep });
    }


    int tiempoActual = 0;
    bool error = false;
    while (!cola.empty() && cola.top().ini < tLimite && !error)
    {
        if (tiempoActual <= cola.top().ini)
        {
            Tarea tareaTop = cola.top();
            cola.pop();
            tiempoActual = tareaTop.fin;
            int per = tareaTop.intervaloRep;
            if (per != -1)
            {
                cola.push({ tareaTop.ini + per, tareaTop.fin + per, per });
            }
        }
        else error = true;
    }

    if (error) cout << "SI\n";
    else cout << "NO\n";

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
