
// Nombre y Apellidos
#include <fstream>

//
//  IndexPQ.h
//
//  Implementación de colas con prioridad mediante montículos.
//  Los elementos son enteros de 0 a N-1 que tienen asociada una prioridad
//  dentro de la cola. La prioridad de un elemento puede ser modificada
//  con coste en O(log N).
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef INDEXPQ_H_
#define INDEXPQ_H_

#include <iostream>
#include <stdexcept>
#include <vector>


// T es el tipo de las prioridades
// Comparator dice cuándo un valor de tipo T es más prioritario que otro
template <typename T = int, typename Comparator = std::less<T>>
class IndexPQ {
public:
    // registro para las parejas < elem, prioridad >
    struct Par {
        int elem;
        T prioridad;
    };

private:
    // vector que contiene los datos (pares < elem, prio >)
    std::vector<Par> array;     // primer elemento en la posición 1

    // vector que contiene las posiciones en array de los elementos
    std::vector<int> posiciones;   // un 0 indica que el elemento no está

    /* Objeto función que sabe comparar prioridades.
     antes(a,b) es cierto si a es más prioritario que b */
    Comparator antes;

public:
    IndexPQ(int N, Comparator c = Comparator()) : array(1), posiciones(N, 0), antes(c) {}

    IndexPQ(IndexPQ<T, Comparator> const&) = default;

    IndexPQ<T, Comparator>& operator=(IndexPQ<T, Comparator> const&) = default;

    ~IndexPQ() = default;

    // e debe ser uno de los posibles elementos
    void push(int e, T const& p) {
        if (posiciones.at(e) != 0)
            throw std::invalid_argument("No se pueden insertar elementos repetidos.");
        else {
            array.push_back({ e, p });
            posiciones[e] = size();
            flotar(size());
        }
    }

    void update(int e, T const& p) {
        int i = posiciones.at(e);
        if (i == 0) // el elemento e se inserta por primera vez
            push(e, p);
        else {
            array[i].prioridad = p;
            if (i != 1 && antes(array[i].prioridad, array[i / 2].prioridad))
                flotar(i);
            else // puede hacer falta hundir a e
                hundir(i);
        }
    }

    int size() const {
        return int(array.size()) - 1;
    }

    bool empty() const {
        return size() == 0;
    }

    Par const& top() const {
        if (size() == 0)
            throw std::domain_error("No se puede consultar el primero de una cola vacia");
        else return array[1];
    }

    void pop() {
        if (size() == 0) throw std::domain_error("No se puede eliminar el primero de una cola vacía.");
        else {
            posiciones[array[1].elem] = 0; // para indicar que no está
            if (size() > 1) {
                array[1] = std::move(array.back());
                posiciones[array[1].elem] = 1;
                array.pop_back();
                hundir(1);
            }
            else
                array.pop_back();
        }
    }

private:

    void flotar(int i) {
        Par parmov = std::move(array[i]);
        int hueco = i;
        while (hueco != 1 && antes(parmov.prioridad, array[hueco / 2].prioridad)) {
            array[hueco] = std::move(array[hueco / 2]); posiciones[array[hueco].elem] = hueco;
            hueco /= 2;
        }
        array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
    }

    void hundir(int i) {
        Par parmov = std::move(array[i]);
        int hueco = i;
        int hijo = 2 * hueco; // hijo izquierdo, si existe
        while (hijo <= size()) {
            // cambiar al hijo derecho de i si existe y va antes que el izquierdo
            if (hijo < size() && antes(array[hijo + 1].prioridad, array[hijo].prioridad))
                ++hijo;
            // flotar el hijo si va antes que el elemento hundiéndose
            if (antes(array[hijo].prioridad, parmov.prioridad)) {
                array[hueco] = std::move(array[hijo]); posiciones[array[hueco].elem] = hueco;
                hueco = hijo; hijo = 2 * hueco;
            }
            else break;
        }
        array[hueco] = std::move(parmov); posiciones[array[hueco].elem] = hueco;
    }

};

#endif /* INDEXPQ_H_ */

//
//  GrafoValorado.h
//
//  Implementación de grafos no dirigidos valorados
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef GRAFOVALORADO_H_
#define GRAFOVALORADO_H_

#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>


template <typename Valor>
class Arista {
public:
    Arista() : pimpl(nullptr) {}
    Arista(int v, int w, int id, Valor valor) : pimpl(std::make_shared<Arista_impl>(v, w, id, valor)) {}

    int uno() const { return pimpl->v; }
    int otro(int u) const { return (u == pimpl->v) ? pimpl->w : pimpl->v; }
    Valor valor() const { return pimpl->valor; }
    int id() const { return pimpl->id_; }

    void print(std::ostream& o = std::cout) const {
        o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
    }

    bool operator<(Arista<Valor> const& b) const {
        return valor() < b.valor();
    }
    bool operator>(Arista<Valor> const& b) const {
        return b.valor() < valor();
    }
private:
    struct Arista_impl {
        int v, w, id_;
        Valor valor;
        Arista_impl(int v, int w, int id, Valor valor) : v(v), w(w), id_(id), valor(valor) {}
    };

    std::shared_ptr<Arista_impl> pimpl; // puntero a la arista "de verdad"
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, Arista<Valor> const& ar) {
    ar.print(o);
    return o;
}


template <typename Valor>
using AdysVal = std::vector<Arista<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoValorado {
public:

    /**
     * Crea un grafo valorado con V vértices, sin aristas.
     */
    GrafoValorado(int V) : _V(V), _A(0), _ady(_V) { }

    /**
     * Crea un grafo valorado a partir de los datos en el flujo de entrada (si puede).
     * primer es el índice del primer vértice del grafo en el entrada.
     */
    GrafoValorado(std::istream& flujo, int primer = 0) : _A(0) {
        flujo >> _V;
        if (!flujo) return;
        _ady.resize(_V);
        int E, v, w;
        Valor c;
        flujo >> E;
        while (E--) {
            flujo >> v >> w >> c;
            ponArista({ v - primer, w - primer, c });
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
     * Añade una arista al grafo.
     * @throws invalid_argument si algún vértice no existe
     */
    void ponArista(Arista<Valor> arista) {
        int v = arista.uno(), w = arista.otro(v);
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::invalid_argument("Vertice inexistente");
        ++_A;
        _ady[v].push_back(arista);
        _ady[w].push_back(arista);
    }

    /**
     * Devuelve la lista de adyacentes de v.
     * @throws invalid_argument si v no existe
     */
    AdysVal<Valor> const& ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::invalid_argument("Vertice inexistente");
        return _ady[v];
    }

    /**
     * Devuelve las aristas del grafo.
     */
    std::vector<Arista<Valor>> aristas() const {
        std::vector<Arista<Valor>> ars;
        for (int v = 0; v < V(); ++v)
            for (auto arista : ady(v))
                if (v < arista.otro(v))
                    ars.push_back(arista);
        return ars;
    }

    /**
     * Muestra el grafo en el stream de salida o
     */
    void print(std::ostream& o = std::cout) const {
        o << _V << " vértices, " << _A << " aristas\n";
        for (auto v = 0; v < _V; ++v) {
            o << v << ": ";
            for (auto const& w : _ady[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }

private:
    int _V;   // número de vértices
    int _A;   // número de aristas
    std::vector<AdysVal<Valor>> _ady;   // vector de listas de adyacentes
};


/**
 * Para mostrar grafos por la salida estándar.
 */

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, GrafoValorado<Valor> const& g) {
    g.print(o);
    return o;
}

#endif /* GRAFOVALORADO_H_ */

class RecorridosMinimos {
private:
    std::vector<int> dist;
    std::vector<int> prev;
    std::vector<int> nAccesos;
    std::vector<bool> visited;
    IndexPQ<int> pq;
    int objetivo;
    int _nCaminos = 0;

    void relajar(Arista<int> a, int v) {
        int w = a.otro(v);
        if (!visited[a.id()]) {
            visited[a.id()] = true;
            if (dist[w] == dist[v] + a.valor()) {
                nAccesos[w] += nAccesos[v];
            }
            else if (dist[w] > dist[v] + a.valor()) {
                dist[w] = dist[v] + a.valor();
                prev[w] = v;
                nAccesos[w] = nAccesos[v];
                pq.update(w, dist[w]);
            }
        }
    }

public:
    RecorridosMinimos(const GrafoValorado<int> &g) : dist(g.V(), 2147483647), visited(g.A(), false), prev(g.V()), nAccesos(g.V(), 0), pq(g.V()), objetivo(g.V() - 1) {
        pq.push(0, 0);
        dist[0] = 0;
        nAccesos[0] = 1;
        if (g.V() == 1) nAccesos[0] = 0;
        while (!pq.empty()) {
            int t = pq.top().elem;
            pq.pop();
            for (auto a : g.ady(t)) {
                relajar(a, t);
            }
        }
        _nCaminos = nAccesos[objetivo];
        //int pos = objetivo;
        //if (_nCaminos != 0) {
        //    while (pos != 0) {
        //        pos = prev[pos];
        //        _nCaminos *= nAccesos[pos];
        //    }
        //}
        _nCaminos = nAccesos[objetivo];
    }

    int nCaminos() { return _nCaminos; }
};

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(const GrafoValorado<int> &g) {
    RecorridosMinimos recorridos = RecorridosMinimos(g);
    
    return (recorridos.nCaminos());
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    // leer los datos de la entrada
    int nNodos;
    std::cin >> nNodos;
    if (!std::cin)  // fin de la entrada
        return false;
    GrafoValorado<int> g(nNodos);
    int nAristas;
    std::cin >> nAristas;
    for (int k = 0; k < nAristas; k++) {
        int uno, otro, valor;
        std::cin >> uno >> otro >> valor;
        g.ponArista(Arista<int>(uno - 1, otro - 1, k, valor));
    }
    std::cout << resolver(g) << "\n";

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