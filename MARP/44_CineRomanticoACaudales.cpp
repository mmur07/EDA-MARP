
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
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

struct Pelicula {
    int inicio;
    int fin;
    int duracion;
    bool operator< (const Pelicula &other) {
        return inicio < other.inicio;
    }
    Pelicula(int ini, int dur) {
        inicio = ini;
        duracion = dur;
        fin = ini + dur + 10;
    }
};

void printVec(std::vector<int> v) {
    for (int k = 0; k < v.size(); k++) {
        std::cout << v[k] << " ";
    }
    std::cout << "\n";
}

int maximoHoras(std::vector<Pelicula> &peliculas, std::vector<int> &sol, int peliActual) {
    int nPelis = peliculas.size();

    if (peliActual >= nPelis) return 0;

    else if (sol[peliActual] == -1) {
        int sig = peliActual+ 1;
        while (sig < nPelis && peliculas[peliActual].fin > peliculas[sig].inicio) sig++;
        if (sig < nPelis) {
            sol[peliActual] = max(peliculas[peliActual].duracion + maximoHoras(peliculas, sol, sig), maximoHoras(peliculas, sol, peliActual + 1));
            printVec(sol);
        }
        else {
            sol[peliActual] = max(peliculas[peliActual].duracion, maximoHoras(peliculas, sol, peliActual + 1));
            printVec(sol);
        }
    }

    return sol[peliActual];
}

bool resuelveCaso() {
    int nPeliculas;
    std::cin >> nPeliculas;
    // leer los datos de la entrada

    if (nPeliculas == 0)
        return false;

    int hInicio, mInicio, duracion;
    char aux;
    std::vector<Pelicula> peliculas;
    for (int k = 0; k < nPeliculas; k++) {
        std::cin >> hInicio >> aux >> mInicio >> duracion;
        Pelicula newPeli = Pelicula(hInicio * 60 + mInicio, duracion);
        peliculas.push_back(newPeli);
    }

    std::sort(peliculas.begin(), peliculas.end());
    std::vector<int> soluciones(nPeliculas, -1);

    std::cout << maximoHoras(peliculas, soluciones, 0) << "\n";

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
