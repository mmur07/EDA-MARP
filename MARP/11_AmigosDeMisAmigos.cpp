
// Miguel Mur
// MARP41

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
private:
    int _V;  // número de vértices
    int _A;  // número de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

    /**
     * Crea un grafo con V vértices.
     */
    Grafo(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo a partir de los datos en el flujo de entrada.
     */
    Grafo(std::istream& flujo) : _A(0) {
        flujo >> _V;
        _ady.resize(_V);
        int E, v, w;
        flujo >> E;
        while (E--) {
            flujo >> v >> w;
            ponArista(v, w);
        }
    }

    /**
     * Devuelve el número de vértices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el número de aristas del grafo.
     */
    int A() const { return _A; }

    /**
     * Añade la arista v-w al grafo.
     * @throws domain_error si algún vértice no existe
     */
    void ponArista(int v, int w) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].push_back(w);
        _ady[w].push_back(v);
    }

    /**
     * Devuelve la lista de adyacencia de v.
     * @throws domain_error si v no existe
     */
    Adys const& ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::domain_error("Vertice inexistente");
        return _ady[v];
    }

    /**
     * Muestra el grafo en el stream de salida o (para depurar)
     */
    void print(std::ostream& o = std::cout) const {
        o << _V << " vértices, " << _A << " aristas\n";
        for (int v = 0; v < _V; ++v) {
            o << v << ": ";
            for (int w : _ady[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }
};

/**
 * Para mostrar grafos por la salida estándar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo const& g) {
    g.print(o);
    return o;
}

#endif /* GRAFO_H_ */

class MaximaCompConexa {
private:
    int maxima_ = 0;
    std::vector<bool> visited;
    int dfs(const Grafo& g, int v) {
        visited[v] = true;
        int tam = 1;
        for (int k : g.ady(v)) {
            if (!visited[k]) {
                tam += dfs(g, k);
            }
        }
        return tam;
    }

public:
    MaximaCompConexa(const Grafo& g) : visited(std::vector<bool>(g.V(), false)){
        for (int k = 0; k < g.V(); k++) {
            if (!visited[k]) {
                int tam = dfs(g, k);
                maxima_ = std::max(maxima_, tam);
            }
        }
    }
    int devuelveMaxima() { return maxima_; }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(const Grafo& g) {
    MaximaCompConexa max = MaximaCompConexa(g);
    return max.devuelveMaxima();
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    // leer los datos de la entrada
    int nPersonas, nConexiones;

    std::cin >> nPersonas >> nConexiones;

    Grafo g = Grafo(nPersonas);

    for (int k = 0; k < nConexiones; k++) {
        int aux1, aux2;
        std::cin >> aux1 >> aux2;
        g.ponArista(aux1 - 1, aux2 - 1);
    }

    std::cout << resolver(g) << "\n";

    // escribir solución
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
