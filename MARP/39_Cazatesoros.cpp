
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>

struct tesoro {
    double profundidad;
    double oro;

    tesoro(double p, double o) : profundidad(p), oro(o) {};
};

template <class T>
using Matriz = std::vector<std::vector<T>>;

double max_oro_rec(const std::vector<tesoro>& tesoros, int i, int j, Matriz<double> &recolectados) {
    if (recolectados[i][j] != -1) return recolectados[i][j];
    if (i == 0 || j == 0) recolectados[i][j] = 0;
    else if (tesoros[i - 1].profundidad * 3 > j) recolectados[i][j] = max_oro_rec(tesoros, i - 1, j, recolectados);
    else recolectados[i][j] = std::max<double>(max_oro_rec(tesoros, i - 1, j, recolectados), max_oro_rec(tesoros, i - 1, j - tesoros[i - 1].profundidad * 3, recolectados) + tesoros[i - 1].oro);
    return recolectados[i][j];
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(const std::vector<tesoro> &tesoros, int oxigeno) {
    int n = tesoros.size();
    Matriz<double> recolectados (n + 1, std::vector<double>(oxigeno + 1, -1));
    double valor = max_oro_rec(tesoros, n, oxigeno, recolectados);
    
    std::vector<bool> sol = std::vector<bool>(n, false);
    int i = n, j = oxigeno, oroConseguido = 0, cofresConseguidos = 0;
    while (i > 0 && j > 0) {
        if (recolectados[i][j] != recolectados[i-1][j]) {
            sol[i - 1] = true; j = j - tesoros[i - 1].profundidad * 3; 
            oroConseguido += tesoros[i - 1].oro; cofresConseguidos++;
        }
        i--;
    }

    std::cout << oroConseguido << "\n";
    std::cout << cofresConseguidos << "\n";

    for (int k = 0; k < sol.size(); k++) {
        if (sol[k]) {
            std::cout << tesoros[k].profundidad << " " << tesoros[k].oro << "\n";
        }
    }
    std::cout << "---\n";
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    double oxigeno, nTesoros;
    std::cin >> oxigeno;
    if (!std::cin)  // fin de la entrada
        return false;
    std::cin >> nTesoros;
    std::vector<tesoro> tesoros;
    double profundidadAux, oroAux;
    for (int k = 0; k < nTesoros; k++) {
        std::cin >> profundidadAux >> oroAux;
        tesoros.push_back(tesoro(profundidadAux, oroAux));
    }

    resolver(tesoros, oxigeno);


    return true;
}

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
