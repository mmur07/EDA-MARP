
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

const int INFINITO = 1000000000;
const int MAXIMO = 10000;

class CalculadoraMin {
private:
    std::queue<int> cola;
    int adyaciente(int n, int choice) {
        switch (choice) {
        case 0:
            return (n + 1) % MAXIMO;
            break;
        case 1:
            return (n * 2) % MAXIMO;
            break;
        case 2:
            return (n / 3);
            break;
        }
    }
    int dfs(int n, int objetivo) {
        if (n == objetivo) return 0;
        std::vector<int> distancia = std::vector<int>(MAXIMO, INFINITO);
        distancia[n] = 0;
        cola.push(n);
        while (!cola.empty()) {
            int front = cola.front();
            cola.pop();
            for (int k = 0; k < 3; k++) {
                int w = adyaciente(front, k);
                if (distancia[w] == INFINITO) {
                    distancia[w] = distancia[front] + 1;
                    if (w == objetivo) return distancia[w];
                    else cola.push(w);
                }
            }
        }
    }
    int quickestPath = 0;
public:
    CalculadoraMin(int inicio, int objetivo) {
        quickestPath = dfs(inicio, objetivo);
    }
    int getQuickestPath() { return quickestPath; }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(int inicio, int objetivo) {
    CalculadoraMin calculadora = CalculadoraMin(inicio, objetivo);
    return calculadora.getQuickestPath();
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int inicio, objetivo;
    std::cin >> inicio;
    if (!std::cin)  // fin de la entrada
        return false;
    std::cin >> objetivo;


    // escribir sol
    std::cout << resolver(inicio, objetivo) << "\n";

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
