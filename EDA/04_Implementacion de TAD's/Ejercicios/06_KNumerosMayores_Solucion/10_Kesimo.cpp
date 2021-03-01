// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "Set.h"



// función que resuelve el problema
Set<string> resolver(Set<string> s, int kElems) {
    Set<string> ordenado = Set<string>(kElems);
    for (int k = 0; k < kElems; k++) {
        ordenado.add(s.getMin());
    }
    return ordenado;
}

// función que resuelve el problema
Set<int> resolver(Set<int> s, int kElems) {
    Set<int> ordenado = Set<int>(kElems);
    for (int k = 0; k < kElems; k++) {
        ordenado.add(s.getMin());
    }
    return ordenado;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    char c = ' ';
    std::cin >> c;

    if (!std::cin)
        return false;

    if (c == 'P') {
        int kElems;
        std::cin >> kElems;

        Set<string> s = Set<string>(kElems);

        string aux = "";

        std::cin >> aux;
        while (aux != "FIN") {
            if (!s.isFull())s.add(aux);
            else if (s.getMin() < aux && !s.contains(aux)) {
                s.removeMin();
                s.add(aux);
            }
            std::cin >> aux;
        }

        Set<string> resultado = resolver(s, kElems);
        s.write(std::cout);
    }

    else if (c == 'N') {
        int kElems;
        std::cin >> kElems;

        Set<int> s = Set<int>(kElems);

        int aux = 0;

        std::cin >> aux;
        while (aux != -1){
            if (!s.isFull())s.add(aux);
            else if (s.getMin() < aux && !s.contains(aux)) {
                s.removeMin();
                s.add(aux);
            }
            std::cin >> aux;
        }

        Set<int> resultado = resolver(s, kElems);
        s.write(std::cout);
    }


    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}