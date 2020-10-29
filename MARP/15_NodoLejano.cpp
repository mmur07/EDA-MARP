
// Nombre y Apellidos

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

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
     * Crea un grafo a partir de los datos en el flujo de entrada (si puede).
     * primer es el índice del primer vértice del grafo en el entrada.
     */
    Grafo(std::istream& flujo, int primer = 0) : _A(0) {
        flujo >> _V;
        if (!flujo) return;
        _ady.resize(_V);
        int E, v, w;
        flujo >> E;
        while (E--) {
            flujo >> v >> w;
            ponArista(v - primer, w - primer);
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
#endif /* GRAFO_H_ */


class NodoLejano {
private:
    std::vector<bool> visited;
    std::vector<int> distancia;
    
    int origen_ = 0;
    int nInalcanzables_ = 0;
    int extension_ = 0;

    void bfs(Grafo const& g) {
        std::queue<int> q;
        distancia[origen_] = 0; visited[origen_] = true;
        q.push(origen_);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            if (distancia[v] < extension_) {
                for (int n : g.ady(v)) {
                    if (!visited[n]) {
                        nInalcanzables_--;
                        distancia[n] = distancia[v] + 1;
                        visited[n] = true;
                        q.push(n);
                    }
                }
            }
        }
    }

public:
    NodoLejano(const Grafo& g, int origen, int extension) : visited(g.V(), false), distancia(g.V()), origen_(origen), extension_(extension), nInalcanzables_(g.V() - 1) {
        bfs(g);
    }

    int nInalcanzables() { return nInalcanzables_; }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(const Grafo &g, int origen, int extension) {
    NodoLejano n = NodoLejano(g, origen, extension);
    return n.nInalcanzables();
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int nNodos, nConexiones;

    std::cin >> nNodos >> nConexiones;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g = Grafo(nNodos);

    for (int k = 0; k < nConexiones; k++) {
        int aux1, aux2;
        std::cin >> aux1 >> aux2;
        g.ponArista(aux1 - 1, aux2 - 1);
    }
    
    int nConsultas;

    std::cin >> nConsultas;

    for (int k = 0; k < nConsultas; k++) {
        int origen, extension;
        std::cin >> origen >> extension;

        std::cout << resolver(g, origen - 1, extension) << "\n";
    }
    std::cout << "---\n";


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
