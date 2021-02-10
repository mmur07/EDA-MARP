
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
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

void imprimir_mat(std::vector<std::vector<int>>& vec) {
    for (int k = 0; k < vec.size(); k++) {
        for (int l = 0; l < vec.size(); l++) {
            if (vec[k][l] == -1) std::cout << "0 ";
            else std::cout << vec[k][l] << " ";
        }
        std::cout << "\n";
    }
}

int maximo_Comida(const std::vector<int>& cubos, int i, int j, std::vector<std::vector<int>>& solucion) {
    if (i > j) return 0;
    if (i == j) {
        solucion[i][j] = cubos[i];
    }
    if (solucion[i][j] == -1) {
        //Solucion si elegimos el cubo de la izquierda.
        int solucionIzquierda;
        int cuboParaDevoradora = max(cubos[i + 1], cubos[j]);
        if (cuboParaDevoradora == cubos[i + 1]) solucionIzquierda = cubos[i] + maximo_Comida(cubos, i + 2, j, solucion);
        else solucionIzquierda = cubos[i] + maximo_Comida(cubos, i + 1, j - 1, solucion);

        //Solucion si elegimos el cubo de la derecha.
        int solucionDerecha;
        cuboParaDevoradora = max(cubos[i], cubos[j - 1]);
        if (cuboParaDevoradora == cubos[j - 1]) solucionDerecha = cubos[j] + maximo_Comida(cubos, i, j - 2, solucion);
        else solucionDerecha = cubos[j] + maximo_Comida(cubos, i + 1, j - 1, solucion);

        solucion[i][j] = max(solucionDerecha, solucionIzquierda);
    }
    return solucion[i][j];
}

bool resuelveCaso() {

    int nCubos;
    std::cin >> nCubos;

    if (nCubos == 0)
        return false;

    std::vector<int> cubos;
    int newCubo;
    for (int k = 0; k < nCubos; k++) {
        std::cin >> newCubo;
        cubos.push_back(newCubo);
    }
    
    std::vector<std::vector<int>> solucion(nCubos, std::vector<int>(nCubos, -1));

    std::cout << maximo_Comida(cubos, 0, nCubos - 1, solucion) << "\n";
    imprimir_mat(solucion);
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
