
// Nombre y Apellidos

// Comentario general sobre la soluci�n,
// explicando c�mo se resuelve el problema

#include <iostream>
#include <fstream>

//
//  Grafo.h
//
//  Implementaci�n de grafos no dirigidos
//
//  Facultad de Inform�tica
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

using Adys = std::vector<int>;  // lista de adyacentes a un v�rtice

class PropagaAmigos {
private:
    int nVisitados = 1;
    void dfs(const Grafo& g, int v) {
        visited[v] = true;
        for (int k = 0; k < g.G(); k++) {
            for (int w : g.ady(v, k)) {
                if (!visited[w]) {
                    nVisitados++;
                    dfs(g, w);
                }
            }
        }
    }
    std::vector<bool> visited;
public:
    PropagaAmigos(const Grafo& g, int origen);
};

class Grafo {
private:
    int _V;  // n�mero de v�rtices
    int _A;  // n�mero de aristas
    int _G;
    std::vector<std::vector<Adys>> _ady;
public:

    /**
     * Crea un grafo con V v�rtices.
     */
    Grafo(int V, int nGrupos) : _V(V), _A(0) , _ady (V), _G(nGrupos){
        for (int k = 0; k < V; k++) {
            _ady[k] = std::vector<Adys>(nGrupos);
        }
    }

    /**
     * Devuelve el n�mero de v�rtices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el n�mero de aristas del grafo.
     */
    int A() const { return _A; }


    int G() const { return _G; }
    /**
     * A�ade la arista v-w al grafo.
     * @throws domain_error si alg�n v�rtice no existe
     */
    void ponArista(int v, int w, int grupo) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v][grupo].push_back(w);
        _ady[w][grupo].push_back(v);
    }

    /**
     * Devuelve la lista de adyacencia de v.
     * @throws domain_error si v no existe
     */
    Adys const& ady(int v, int grupo) const {
        if (v < 0 || v >= _V)
            throw std::domain_error("Vertice inexistente");
        return _ady[v][grupo];
    }
};

#endif /* GRAFO_H_ */


// funci�n que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void resolver(const Grafo &g) {
    
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int nUsuarios, nGrupos;

    std::cin >> nUsuarios >> nGrupos;

    if (!std::cin)  // fin de la entrada
        return false;

    Grafo g = Grafo(nUsuarios, nGrupos);
    for (int k = 0; k < nGrupos; k++) {
        int sizeGrupo;
        std::cin >> sizeGrupo;
        int current, prev = -1;
        for (int l = 0; l < sizeGrupo; l++) {
            std::cin >> current;
            if (prev != -1) {
                g.ponArista(current - 1, prev - 1, k);
            }
            prev = current;
        }
    }

    resolver(g);

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
