// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>


// función que resuelve el problema
int resolver(const std::vector<int> &vec, int ini, int fin) {
    if (ini != fin) {
        int mid = (ini + fin) / 2;

        if (fin == ini + 1) {
            if (vec[ini] < vec[fin]) return vec[ini];
            else return vec[fin];
        }

        else if (vec[mid] < vec[fin]) { //El elemento menor está a la derecha
            return resolver(vec, mid, fin);
        }

        else if (vec[mid] > vec[ini]) { //El elemento mayor está a la izquierda
            return resolver(vec, ini, mid);
        }
        else return resolver(vec, mid, fin);
    }

    else return vec[ini];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int tamEntrada, aux;
    std::vector<int> vec;
    std::cin >> tamEntrada;
    if (!std::cin)
        return false;
    for (int k = 0; k < tamEntrada; k++) {
        std::cin >> aux;
        vec.push_back(aux);
    }

    std::cout << resolver(vec, 0, vec.size() - 1) << "\n";

    // escribir sol


    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}