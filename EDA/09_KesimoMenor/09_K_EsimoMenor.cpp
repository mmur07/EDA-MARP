// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include "SetOfInts3.h"

SetOfInts3 K_Minimos(SetOfInts3 s, int kelems) {
    SetOfInts3 result = SetOfInts3(kelems);
    for (int k = 0; k < kelems; k++) {
        int min = s.getMin();
        if (!s.isEmpty()) {
            s.removeMin();
            result.add(min);
        }
    }

    return result;
}

// función que resuelve el problema
void resolver(SetOfInts3 s, int kelems) {
    SetOfInts3 result = K_Minimos(s, kelems);
    result.print();
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int kElems = -1;
    std::cin >> kElems;

    if (kElems == 0)
        return false;

    SetOfInts3 s = SetOfInts3(kElems);
    
    int aux, cont = 0;
    std::cin >> aux;
    while (aux != -1) {
        if (!s.isFull()) {
            s.add(aux); 
            cont++;
        }
        else {
            if (s.getMax() > aux && !s.contains(aux)) {
                s.removeMax();
                s.add(aux);
            }
        }
        std::cin >> aux;
    }

    resolver(s, kElems);

    // escribir sol


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