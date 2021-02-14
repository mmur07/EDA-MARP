// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

// función que resuelve el problema
bool resolver(std::vector<int> vec1, std::vector<int> vec2) {
    if (vec1.empty() || vec2.empty()) return true;

    int maxVec1 = vec1[0], minVec2 = vec2[0];

    for (int k = 1; k < vec1.size(); k++) {
        if (vec1[k] > maxVec1) maxVec1 = vec1[k];
    }

    for (int k = 1; k < vec2.size(); k++) {
        if (vec2[k] < minVec2) minVec2 = vec2[k];
    }

    if (maxVec1 >= minVec2) return false;
    return true;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    int sizeVec = 0, dividingPos = 0;
    std::cin >> sizeVec >> dividingPos;

    int aux = 0;
    std::vector<int> vec1;
    for (int k = 0; k <= dividingPos; k++) {
        std::cin >> aux;
        vec1.push_back(aux);
    }

    std::vector<int> vec2;
    for (int k = dividingPos + 1; k < sizeVec; k++) {
        std::cin >> aux;
        vec2.push_back(aux);
    }

    // escribir sol
    if (resolver(vec1, vec2)) std::cout << "SI\n";
    else std::cout << "NO\n";

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