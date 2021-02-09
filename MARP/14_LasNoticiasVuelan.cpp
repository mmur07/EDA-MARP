
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
 //
 //  Grafo.h
 //
 //  ImplementaciÃ³n de grafos no dirigidos
 //
 //  Facultad de InformÃ¡tica
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

using Adys = std::vector<int>;  // lista de adyacentes a un vÃ©rtice

class Grafo {
private:
    int _V;  // nÃºmero de vÃ©rtices
    int _A;  // nÃºmero de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

    /**
     * Crea un grafo con V vÃ©rtices.
     */
    Grafo(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo a partir de los datos en el flujo de entrada (si puede).
     * primer es el Ã­ndice del primer vÃ©rtice del grafo en el entrada.
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
     * Devuelve el nÃºmero de vÃ©rtices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el nÃºmero de aristas del grafo.
     */
    int A() const { return _A; }

    /**
     * AÃ±ade la arista v-w al grafo.
     * @throws domain_error si algÃºn vÃ©rtice no existe
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
        o << _V << " vÃ©rtices, " << _A << " aristas\n";
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
 * Para mostrar grafos por la salida estÃ¡ndar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo const& g) {
    g.print(o);
    return o;
}

#endif /* GRAFO_H_ */
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

class NoticiasVuelan {
private:
    std::vector<int> componenteNodo;
    std::vector<int> alcanceComponenteConexa;
    int componenteActual = 0;
public:
    NoticiasVuelan(const Grafo& g, int nGrupos) : componenteNodo(g.V(), -1) {
        for (int k = 0; k < g.V(); k++) {
            if (componenteNodo[k] == -1) {
                alcanceComponenteConexa.push_back(dfs(g, k));
                componenteActual++;
            }
        }
    }

    int dfs(const Grafo& g, int n) {
        int cont = 1;
        componenteNodo[n] = componenteActual;
        for (int a : g.ady(n)) {
            if (componenteNodo[a] == -1) {
                cont += dfs(g, a);
            }
        }

        return cont;
    }

    void imprime() {
        for (int k = 0; k < componenteNodo.size(); k++) {
            std::cout << alcanceComponenteConexa[componenteNodo[k]] << " ";
        }
        std::cout << "\n";
    }
};

bool resuelveCaso() {
    int nNodos, nGrupos;
    // leer los datos de la entrada
    std::cin >> nNodos >> nGrupos;
    if (!std::cin)  // fin de la entrada
        return false;
    Grafo g = Grafo(nNodos);
    for (int k = 0; k < nGrupos; k++) {
        int tamGrupo;
        std::cin >> tamGrupo;
        if (tamGrupo > 0) {
            int nodoIni;
            std::cin >> nodoIni;
            if (tamGrupo > 1) {
                int newNode;
                for (int i = 1; i < tamGrupo; i++) {
                    std::cin >> newNode;
                    g.ponArista(nodoIni - 1, newNode - 1);
                    nodoIni = newNode;
                }
            }
        }
    }

    NoticiasVuelan n(g, nGrupos);
    n.imprime();
    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución

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
