
// Miguel Mur
// MARP 41

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::vector<std::pair<int, int>> dirs = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };
using Mapa = std::vector<std::string>;

class Manchas {
private:
    std::vector<std::vector<bool>> visited;
    int maxim_ = 0;
    int nManchas_ = 0;
    int alto_ = 0;
    int ancho_ = 0;
    int dfs(const Mapa& m, int posY, int posX) {
        visited[posY][posX] = true;
        int tam = 1;
        for (int k = 0; k < dirs.size(); k++) {
            int nPosY = posY + dirs[k].second;
            int nPosX = posX + dirs[k].first;
            if (correcta(nPosY, nPosX) && !visited[nPosY][nPosX] && m[nPosY][nPosX] == '#') {
                tam += dfs(m, nPosY, nPosX);
            }
        }
        return tam;
    }
    bool correcta(int posY, int posX) {
        return (posY >= 0 && posX >= 0 && posY < alto_ && posX < ancho_);
    }

public:
    Manchas(const Mapa& m) : visited(m.size(), std::vector<bool>(m[0].size(), false)), alto_(m.size()), ancho_(m[0].size()){
        for (int k = 0; k < alto_; k++) {
            for (int l = 0; l < ancho_; l++) {
                if (!visited[k][l] && m[k][l] == '#') {
                    nManchas_++;
                    int nuevoTam = dfs(m, k, l);
                    maxim_ = std::max(maxim_, nuevoTam);
                }
            }
        }
    }
    int getMaxSize() { return maxim_; }
    int getNumManchas() { return nManchas_; }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(const Mapa& m) {
    Manchas manch = Manchas(m);
    std::cout << manch.getNumManchas() << " " << manch.getMaxSize() << "\n";
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int alto, ancho;

    std::cin >> alto;

    if (!std::cin)  // fin de la entrada
        return false;

    std::cin >> ancho;
    Mapa m = Mapa(alto);

    for (int k = 0; k < alto; k++) {
        std::string aux;
        std::cin >> aux;
        m[k] = aux;
    }

    resolver(m);

    // escribir sol

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
