
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

class MinRolls {
private:
    std::vector<bool> visited;
    std::vector<int> distancia;
    bool finished = false;
    void dfs(int pos, std::vector<int> tablero, int nFaces) {
        visited[pos] = true;
        std::queue<int> q;
        q.push(pos);
        while (!q.empty() && !finished) {
            int currPos = q.front();
            q.pop();
            for (int k = 1; k <= nFaces; k++) {
                int newPos = currPos + k;
                if (newPos < tablero.size()) {
                    if (tablero[newPos] != -1) newPos = tablero[newPos];

                    if (!visited[newPos]) {
                        distancia[newPos] = distancia[currPos] + 1;
                        if (newPos == tablero.size() - 1) {
                            finished = true;
                            minPasos = distancia[newPos];
                        }
                        else {
                            visited[newPos] = true;
                            q.push(newPos);
                        }
                    }
                }
            }
        }
    }
    int minPasos;
public:
    MinRolls(std::vector<int> tablero, int nFaces) {
        visited = std::vector<bool>(tablero.size(), false);
        distancia = std::vector<int>(tablero.size(), 0);
        minPasos = tablero.size();

        dfs(0, tablero, nFaces);
    }
    int getMinPasos() { return minPasos; }
};
 
// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(std::vector<int> tablero, int nFaces) {
    MinRolls minRolls = MinRolls(tablero, nFaces);

    return minRolls.getMinPasos();
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int tableroSize, nFaces, nSerpientes, nEscaleras;

    std::cin >> tableroSize >> nFaces >> nSerpientes >> nEscaleras;

    if (tableroSize == 0 && nFaces == 0 && nSerpientes == 0 && nEscaleras == 0)
        return false;

    std::vector<int> tablero(tableroSize * tableroSize, -1);

    for (int k = 0; k < nSerpientes + nEscaleras; k++) {
        int pos1, pos2;

        std::cin >> pos1 >> pos2;

        tablero[pos1 - 1] = pos2 - 1;
    }

    std::cout << resolver(tablero, nFaces) << "\n";

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
