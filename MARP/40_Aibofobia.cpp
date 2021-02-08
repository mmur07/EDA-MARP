
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;

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

    // operadores para poder utilizar notaci�n M[i][j]
    std::vector<Object> const& operator[](int f) const {
        return datos[f];
    }
    std::vector<Object>& operator[](int f) {
        return datos[f];
    }

    // m�todos que lanzan una excepci�n si la posici�n no existe
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

//
//  EnterosInf.h
//
//  Implementaci�n de enteros con +infinito.
//
//  Facultad de Inform�tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef ENTEROSINF_H_
#define ENTEROSINF_H_

#include <limits>
#include <iostream>

class EntInf {
    int num;
public:
    static const int _intInf = 1000000000;

    EntInf(int n = 0) : num(n) {}

    EntInf operator+(EntInf const& b) const {
        if (num == _intInf || b.num == _intInf || num >= (_intInf - b.num))
            return _intInf;
        else return num + b.num;
    }

    bool operator==(EntInf const& b) const {
        return num == b.num;
    }

    bool operator!=(EntInf const& b) const {
        return !(*this == b);
    }

    bool operator<(EntInf const& b) const {
        if (num == _intInf) return false;
        else if (b.num == _intInf) return true;
        else return num < b.num;
    }

    bool operator>(EntInf const& b) const {
        return b < *this;
    }

    void print(std::ostream& out = std::cout) const {
        if (num == _intInf) out << "+Inf";
        else out << num;
    }
};

const EntInf Infinito(EntInf::_intInf);

inline std::ostream& operator<<(std::ostream& out, EntInf const& e) {
    e.print(out);
    return out;
}

#endif
using namespace std;
#include <istream>
#include <string>
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void reconstruir(const string& palabra, const Matriz<EntInf>& m, int i, int j, string &sol) {
    if (i > j) return;
    if (i == j) sol.push_back(palabra[i]);
    else if (palabra[i] == palabra[j]) {
        sol.push_back(palabra[i]);
        reconstruir(palabra, m, i + 1, j - 1, sol);
        sol.push_back(palabra[j]);
    }
    else if (m[i + 1][j] > m[i][j - 1]) {
        sol.push_back(palabra[j]);
        reconstruir(palabra, m, i, j - 1, sol);
        sol.push_back(palabra[j]);
    }
    else {
        sol.push_back(palabra[i]);
        reconstruir(palabra, m, i + 1, j, sol);
        sol.push_back(palabra[i]);
    }
}

EntInf aibofobia_rec(int i, int j, const string &palabra, Matriz<EntInf> &mat) {
    EntInf& res = mat[i][j];
    if (res == Infinito) {
        if (i > j) res = 0;
        else if (i == j) res = 0;
        else if (palabra[i] == palabra[j]) res = aibofobia_rec(i + 1, j - 1, palabra, mat);
        else {
            res = min(aibofobia_rec(i + 1, j, palabra, mat) + 1, aibofobia_rec(i, j - 1, palabra, mat) + 1);
        }
    }
    return res;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    string palabra;
    getline(std::cin, palabra);
    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<EntInf> m(palabra.size(), palabra.size(), Infinito);
    aibofobia_rec(0, palabra.size() - 1, palabra, m);

    //for (int k = 0; k < m.numcols(); k++) {
    //    for (int l = 0; l < m.numcols(); l++) {
    //        if (m[k][l] == Infinito) std::cout << "0 ";
    //        else std::cout << m[k][l] << " ";
    //    }
    //    std::cout << "\n";
    //}
    //std::cout << "\n";
    string solucion;
    reconstruir(palabra, m, 0, palabra.size() - 1, solucion);
    std::cout << m[0][palabra.size() - 1] << " " << solucion << "\n";

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
