// Miguel Mur Cortes
// VJ43


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

void resolverAux(const std::vector<int>& vec, int ini, int fin, bool& found) {

    if (!found) {
        int mid = (ini + fin) / 2;
        
        if (mid == ini || mid == fin) {
            if (vec[ini] < vec[fin]) std::cout << vec[ini] << std::endl;
            else std::cout << vec[fin] << std::endl;
        }

        else if (vec[mid + 1] > vec[mid] && vec[mid - 1] > vec[mid]) {
            found = true;
            std::cout << vec[mid] << std::endl;
        }
        
        else {
            if (vec[mid + 1] < vec[mid - 1]) resolverAux(vec, mid, fin, found);
            else resolverAux(vec, ini, mid, found);
        }
    }
}

// función que resuelve el problema
void resolver(const std::vector<int>& vec) { //O(log n)
    bool found = false;
    if (vec.size() == 1) std::cout << vec[0] << std::endl;
    else resolverAux(vec, 0, vec.size() - 1, found); //O(log n)
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int sizeVec = 0;
    std::cin >> sizeVec;

    if (! std::cin)
        return false;

    std::vector<int> vec;
    for (int k = 0; k < sizeVec; k++) {
        int aux;
        std::cin >> aux;
        vec.push_back(aux);
    }

    resolver(vec);

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
