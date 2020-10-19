// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
std::vector<int> resolver(std::vector<int> vec1, std::vector<int> vec2) {
    int aux1 = 0, aux2 = 0;

    std::vector<int> result;
    while (aux1 < vec1.size() || aux2 < vec2.size()) {

        if (aux1 >= vec1.size()) {
            for (int k = aux2; k < vec2.size(); k++) {
                result.push_back(vec2[k]);
            }
            return result;
        }

        else if (aux2 >= vec2.size()) {
            for (int k = aux1; k < vec1.size(); k++) {
                result.push_back(vec1[k]);
            }
            return result;
        }

        else {
            if (vec1[aux1] < vec2[aux2]) {
                result.push_back(vec1[aux1]);
                aux1++;
            }
            else if (vec1[aux1] > vec2[aux2]) {
                result.push_back(vec2[aux2]);
                aux2++;
            }
            else {
                result.push_back(vec1[aux1]);
                aux1++;
                aux2++;
            }
        }
    }
    return result;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    int size1 = 0, size2 = 0;
    int aux = 0;

    std::cin >> size1 >> size2;

    std::vector<int> vec1;
    for (int k = 0; k < size1; k++) {
        std::cin >> aux;
        vec1.push_back(aux);
    }

    std::vector<int> vec2;
    for (int k = 0; k < size2; k++) {
        std::cin >> aux;
        vec2.push_back(aux);
    }

    std::vector<int> result = resolver(vec1, vec2);

    for (int k = 0; k < result.size(); k++) {
        std::cout << result[k] << " ";
    }
    std::cout << "\n";
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