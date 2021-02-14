// Miguel Mur
// VJ41

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

int resolverAux(const std::vector<int>& vec, int ini, int fin) {
    if (ini == fin) return vec[ini] + 1;

    else {
        int mid = (ini + fin - 1) / 2;

        if (vec[mid] == vec[ini] + (mid - ini) && vec[mid + 1] != vec[mid] + 1) return vec[mid] + 1;

        else if (vec[mid] - vec[ini] > mid - ini) return resolverAux(vec, ini, mid + 1);
        else return resolverAux(vec, mid + 1, fin);
    }
}

// función que resuelve el problema
int resolver(const std::vector<int>& vec) {
    return resolverAux(vec, 0, vec.size() - 1);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int sizeVec = 0;
    std::cin >> sizeVec;
    std::vector<int> vec;
    for (int k = 0; k < sizeVec; k++) {
        int aux = 0;
        std::cin >> aux;
        vec.push_back(aux);
    }
    std::cout << resolver(vec) << std::endl;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}