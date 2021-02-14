// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>

enum Colores { azul, rojo, verde };

bool es_Solucion(int n, std::vector<int>& piezasUsadas, const int& tamTorre) {
    return (n == tamTorre && piezasUsadas[rojo] > piezasUsadas[azul] + piezasUsadas[verde]);
}

bool es_Viable(int n, std::vector<int> &solucion, std::vector<int>& piezasUsadas, const std::vector<int> &numPiezas, const int& tamTorre) {

    if (n >= tamTorre) return false;

    if (piezasUsadas[solucion[n]] > numPiezas[solucion[n]]) return false;

    if (n == 0 && solucion[n] != rojo)return false;

    if (n > 0 && solucion[n - 1] == verde) {
        return (solucion[n] != verde);
    }

    if (piezasUsadas[verde] > piezasUsadas[azul]) return false;

    return true;
}

void resolver_rec(int n, std::vector<int> &solucionActual, const int &tamTorre, const std::vector<std::string> &colores, std::vector<int> &piezasUsadas, bool &haySolucion, const std::vector<int>& numPiezas) {
    
    if (es_Solucion(n, piezasUsadas, tamTorre)) {

        for (int k = 0; k < solucionActual.size(); k++) {
            std::cout << colores[solucionActual[k]] << " ";
        }
        std::cout << "\n";

        haySolucion = true;
    }

    for (int k = 0; k < colores.size(); k++) {

        if (n < tamTorre) {
            solucionActual[n] = k;
            piezasUsadas[k]++;
        }

        if (es_Viable(n, solucionActual, piezasUsadas, numPiezas, tamTorre)) {
            resolver_rec(n + 1, solucionActual, tamTorre, colores, piezasUsadas, haySolucion, numPiezas);
        }
        

        if (n < tamTorre) {
            piezasUsadas[k]--;
            solucionActual[n] = -1;
        }
    }
}


// función que resuelve el problema
void resolver(const int &tamTorre, const std::vector<int> &numPiezas, const std::vector<std::string>& colores) {
    bool haySolucion = false;
    std::vector<int> solucion = std::vector<int>(tamTorre, -1);
    std::vector<int> piezasUsadas = std::vector<int>(colores.size(), 0);
    resolver_rec(0, solucion, tamTorre, colores, piezasUsadas, haySolucion, numPiezas);

    if (!haySolucion) std::cout << "SIN SOLUCION\n";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::vector<std::string> colores = { "azul", "rojo", "verde" };
    std::vector<int> numPiezas;
    int tamTorre;
    std::cin >> tamTorre;
    int aux;
    for (int k = 0; k < colores.size(); k++) {
        std::cin >> aux;
        numPiezas.push_back(aux);
    }

    if (numPiezas[0] == 0 && numPiezas[0] == 0 && numPiezas[1] == 0 && numPiezas[2] == 0)
        return false;

    resolver(tamTorre, numPiezas, colores);
    std::cout << "\n";


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