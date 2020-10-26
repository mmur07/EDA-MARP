
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

//
//  Grafo.h
//
//  Implementación de grafos no dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_



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

class EsArbolLibre {
private:
    std::vector<bool> visited;
    std::vector<int> anterior;

    bool esAciclico = true;
public:
    EsArbolLibre(Grafo const& g) {
        visited = std::vector<bool>(g.V(), false);
        anterior = std::vector<int>(g.V());

        dfs(g, 0);
    }

    void dfs(Grafo const &g, int v) {
        visited[v] = true;
        for (int w : g.ady(v)) {
            if (w != anterior[v] && visited[w]) esAciclico = false;
            if (!visited[w]) {
                anterior[w] = v;
                dfs(g, w);
            }
        }
    }

    bool esLibre() {
        for (int k = 0; k < visited.size(); k++) if (!visited[k]) return false;
        return esAciclico;
    }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
bool resolver(const Grafo &g) {
    EsArbolLibre eal = EsArbolLibre(g);
    return eal.esLibre();
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int nVertices = 0;
    int nAristas = 0;
    
    std::cin >> nVertices;
    if (!std::cin)  // fin de la entrada
        return false;
    std::cin >> nAristas;

    int elem1, elem2;
    Grafo g = Grafo(nVertices);
    for (int k = 0; k < nAristas; k++) {
        std::cin >> elem1 >> elem2;
        g.ponArista(elem1, elem2);
    }

    // escribir sol
    if (resolver(g)) std::cout << "SI\n";
    else std::cout << "NO\n";

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
