
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
 //
 //  Matriz.h
 //
 //  Implementaci�n de matrices (arrays bidimensionales)
 //
 //  Facultad de Inform�tica
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

#include <vector>
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void resolver(const int& potMin, const int& potMax, const vector<int>& potenciaBombillas, const vector<int>& precioBombillas) {

    int n = potenciaBombillas.size();
    Matriz<EntInf>m(n + 1, potMax + 1, Infinito);
    m[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        m[i][0] = 0;
        for (int j = 1; j <= potMax; j++) {
            if (potenciaBombillas[i - 1] > j) m[i][j] = m[i - 1][j];
            else {
                m[i][j] = min(m[i - 1][j], m[i][j - potenciaBombillas[i - 1]] + precioBombillas[i - 1]);
            }
        }
    }

    EntInf mejorPrecio = Infinito;
    int pos;
    for (int k = potMin; k <= potMax; k++) {
        if (m[n][k] < mejorPrecio) {
            mejorPrecio = m[n][k];
            pos = k;
        }
    }

    //for (int i = 1; i <= n; i++) {
    //    std::cout << "Precio - " << precioBombillas[i - 1] << ", Potencia - " << potenciaBombillas[i - 1] << ": ";
    //    for (int j = 1; j <= potMax; j++) {
    //        if (m[i][j] == Infinito) std::cout << 0 << " ";
    //        else std::cout << m[i][j] << " ";
    //    }
    //    std::cout << "\n";
    //}

    int potenciaRequerida = 0;
    if (mejorPrecio != Infinito) {
        int i = n, j = pos;
        while (j > 0) {
            if (potenciaBombillas[i - 1] <= j && m[i][j - potenciaBombillas[i - 1]] < m[i - 1][j]) {
                potenciaRequerida += potenciaBombillas[i - 1];
                j -= potenciaBombillas[i - 1];
            }
            else i--;
        }
        std::cout << mejorPrecio << " " << potenciaRequerida << "\n";
    }
    else {
        std::cout << "IMPOSIBLE\n";
    }
}

bool resuelveCaso() {

    int nTipos, potMax, potMin;
    std::cin >> nTipos >> potMax >> potMin;
    if (!std::cin)  // fin de la entrada
        return false;

    int newPot, newPrecio;
    vector<int> potenciaBombillas, precioBombillas;
    for (int k = 0; k < nTipos; k++) {
        std::cin >> newPot;
        potenciaBombillas.push_back(newPot);
    }
    for (int k = 0; k < nTipos; k++) {
        std::cin >> newPrecio;
        precioBombillas.push_back(newPrecio);
    }
    // resolver el caso posiblemente llamando a otras funciones
    resolver(potMin, potMax, potenciaBombillas, precioBombillas);

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
