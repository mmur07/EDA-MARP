
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

//
//  Matriz.h
//
//  ImplementaciÃ³n de matrices (arrays bidimensionales)
//
//  Facultad de InformÃ¡tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef MATRIZ_H
#define MATRIZ_H

#include <vector>
#include <ostream>

template <typename Object>
class Matriz {
public:
    // crea una matriz con fils filas y cols columnas,
    // con todas sus celdas inicializadas al valor e
    Matriz(int fils = 0, int cols = 0, Object e = Object()) : datos(fils, std::vector<Object>(cols, e)) {}

    // operadores para poder utilizar notaciÃ³n M[i][j]
    std::vector<Object> const& operator[](int f) const {
        return datos[f];
    }
    std::vector<Object>& operator[](int f) {
        return datos[f];
    }

    // mÃ©todos que lanzan una excepciÃ³n si la posiciÃ³n no existe
    Object const& at(int f, int c) const {
        return datos.at(f).at(c);
    }
    Object& at(int f, int c) {
        return datos.at(f).at(c);
    }

    int numfils() const { return datos.size(); }
    int numcols() const { return numfils() > 0 ? datos[0].size() : 0; }

    bool posCorrecta(int f, int c) const {
        return 0 <= f && f < numfils() && 0 <= c && c < numcols();
    }

private:
    std::vector<std::vector<Object>> datos;
};

template <typename Object>
inline std::ostream& operator<<(std::ostream& out, Matriz<Object> const& m) {
    for (int i = 0; i < m.numfils(); ++i) {
        for (int j = 0; j < m.numcols(); ++j) {
            out << m[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

#endif

#include <queue>
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

std::vector<int> calculaVoraz(const Matriz<int>& mat) {
    int numSupers = mat.numfils();
    int numProductos = mat.numcols();
    std::vector<int> voraz(numProductos + 1);
    int acum = 0;
    for (int k = numProductos - 1; k >= 0; k--) {
        int minimum = 1000000000;
        for (int l = 0; l < numSupers; l++) {
            minimum = min(minimum, mat[l][k]);
        }
        acum += minimum;
        voraz[k] = acum;
    }
    return voraz;
}


struct Nodo {
    //K es el objeto que queremos comprar en ese momento.
    vector<int> objetosPorSuper;
    int k;
    int coste;
    int coste_est;

    bool operator> (const Nodo& other) const {
        return coste_est > other.coste_est;
    }
};

int mejor_Compra(const Matriz<int>& mat) {
    int nSupers = mat.numfils();
    int nProductos = mat.numcols();

    std::vector<int> coste_voraz = calculaVoraz(mat);
    Nodo Y;
    Y.k = -1;
    Y.coste = 0;
    Y.coste_est = coste_voraz[0];
    Y.objetosPorSuper = vector<int>(nSupers, 0);
    priority_queue<Nodo, vector<Nodo>, greater<Nodo>> pqueue;
    pqueue.push(Y);
    int mejor_Coste = 1000000000;

    while (!pqueue.empty() && pqueue.top().coste_est < mejor_Coste) {
        Y = pqueue.top(); pqueue.pop();
        Nodo X(Y);
        Y.k++;
        //i es el super del que queremos obtener algo
        for (int i = 0; i < nSupers; i++) {
            if (Y.objetosPorSuper[i] < 3) {
                Y.objetosPorSuper[i]++;
                Y.coste = X.coste + mat[i][Y.k];
                Y.coste_est = Y.coste + coste_voraz[Y.k + 1];
                if (Y.coste_est < mejor_Coste) {
                    if (Y.k == nProductos - 1) {
                        mejor_Coste = Y.coste;
                    }
                    else {
                        pqueue.push(Y);
                    }
                }
                Y.objetosPorSuper[i]--;
            }
        }
    }
    return mejor_Coste;
}

void resuelveCaso() {

    int nSupermercados, nProductos, lec;
    std::cin >> nSupermercados >> nProductos;

    Matriz<int> productos(nSupermercados, nProductos);
    for (int k = 0; k < nSupermercados; k++) {
        for (int l = 0; l < nProductos; l++) {
            cin >> lec;
            productos[k][l] = lec;
        }
    }

    std::cout << mejor_Compra(productos) << "\n";
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
