
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//
//  Matriz.h
//
//  Implementación de matrices (arrays bidimensionales)
//
//  Facultad de Informática
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

    // operadores para poder utilizar notación M[i][j]
    std::vector<Object> const& operator[](int f) const {
        return datos[f];
    }
    std::vector<Object>& operator[](int f) {
        return datos[f];
    }

    // métodos que lanzan una excepción si la posición no existe
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


/*@ <answer>

 Escribe aqu� un comentario general sobre la soluci�n, explicando c�mo
 se resuelve el problema y cu�l es el coste de la soluci�n, en funci�n
 del tama�o del problema.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo
 // ================================================================
 //@ <answer>

#include <queue>

struct Nodo {
    vector<bool> trabajador;
    int k;
    double coste;
    double coste_est;
    bool operator>(Nodo const& otro) const {
        return coste_est > otro.coste_est;
    }
};

int calculo_voraz(const Matriz<int>& objetos, Nodo X) {
    int n = objetos.numcols();
    int costeAcum = 0;
    for (int i = X.k + 1; i < n; i++) {
        int min = 1000000000;
        for (int j = 0; j < n; j++) {
            if (X.trabajador[j] == false) min = std::min(min, objetos[j][i]);
        }
        costeAcum += min;
    }
    return costeAcum;
}

double min_Funcionarios(const Matriz<int>& objetos, int& coste_mejor) {
    int N = objetos.numcols();
    Nodo Y;
    Y.trabajador = vector<bool>(N, false);
    Y.k = -1;
    Y.coste = 0;
    Y.coste_est = calculo_voraz(objetos, Y);
    priority_queue<Nodo, std::vector<Nodo>, greater<Nodo>> cola;
    cola.push(Y);
    coste_mejor = 1000000000;

    while (!cola.empty() && cola.top().coste_est < coste_mejor) {
        Y = cola.top(); cola.pop();
        for (int i = 0; i < N; i++) {
            Nodo X(Y);
            ++X.k;
            if (X.trabajador[i] == false) {
                X.trabajador[i] = true;
                X.coste = Y.coste + objetos[i][X.k];
                X.coste_est = X.coste + calculo_voraz(objetos, X);
                if (X.k == N - 1) {
                    coste_mejor = X.coste;
                }
                else {
                    cola.push(X);
                }
                X.trabajador[i] = false;
            }
        }
    }
    return coste_mejor;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int N;
    std::cin >> N;
    if (N == 0)
        return false;
    Matriz<int> tareas(N, N);
    int aux;
    for (int k = 0; k < N; k++) {
        for (int l = 0; l < N; l++) {
            std::cin >> aux;
            tareas[k][l] = aux;
        }
    }
    int coste_mejor = 0;
    min_Funcionarios(tareas, coste_mejor);
    std::cout << coste_mejor << "\n";
    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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
