// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

template < typename T, typename Equal = std::equal_to <T > >
int find_num_repeats(int ini, int fin, T elem, const std::vector<T>& vec) {
    int nReps = 0;

    for (int k = ini; k <= fin; k++) {
        if (vec[k] == elem) nReps++;
    }
    return nReps;
}

template < typename T, typename Equal = std::equal_to <T > >
std::pair < bool, T > mayoria_rec(int ini, int fin, const std::vector<T>& vec) {
    if (ini == fin) return std::pair < bool, T >(true, vec[ini]);

    if (ini < fin) {
        int mid = (ini + fin) / 2;

        std::pair < bool, T > izquierda = mayoria_rec(ini, mid, vec);
        std::pair < bool, T > derecha = mayoria_rec(mid + 1, fin, vec);

        if (!izquierda.first && derecha.first) {
            int num_repeats = find_num_repeats(ini, fin, derecha.second, vec);

            if (num_repeats > (fin - ini + 1) / 2) return std::pair < bool, T >(true, derecha.second);
        }

        else if (!derecha.first && izquierda.first) {
            int num_repeats = find_num_repeats(ini, fin, izquierda.second, vec);

            if (num_repeats > (fin - ini + 1) / 2) return std::pair < bool, T >(true, izquierda.second);
        }

        else if (izquierda.first && derecha.first) {
            int num_repeats_izq = find_num_repeats(ini, fin, izquierda.second, vec);
            int num_repeats_der = find_num_repeats(ini, fin, derecha.second, vec);

            if (num_repeats_izq > num_repeats_der || izquierda == derecha) {
                if (num_repeats_izq > (fin - ini + 1) / 2) return std::pair < bool, T >(true, izquierda.second);
            }

            if (num_repeats_der > num_repeats_izq) {
                if (num_repeats_der > (fin - ini + 1) / 2) return std::pair < bool, T >(true, derecha.second);
            }

            return std::pair < bool, T >(false, derecha.second);
        }

        return std::pair < bool, T >(false, derecha.second);
    }

    return std::pair<bool, T>(ini, false);
}

template < typename T, typename Equal = std::equal_to <T > >
std::pair < bool, T > mayoria(const std::vector <T >& v) {
    return mayoria_rec(0, v.size() - 1, v);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int sizeVec = 0, aux = 0;
    std::cin >> sizeVec;
    if (sizeVec == -1)
        return false;
    std::vector<int> vec;
    for (int k = 0; k < sizeVec; k++) {
        std::cin >> aux;
        vec.push_back(aux);
    }
    std::pair < bool, int > resultado = mayoria(vec);

    if (!resultado.first) std::cout << "NADA\n";
    else std::cout << resultado.second << "\n";

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
