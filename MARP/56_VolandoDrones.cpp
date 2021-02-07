
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
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

bool resuelveCaso() {
    int nDrones, nPilas1, nPilas2;
    std::cin >> nDrones >> nPilas1 >> nPilas2;
    // leer los datos de la entrada

    if (!std::cin)  // fin de la entrada
        return false;
    
    priority_queue<long long int> pilas1, pilas2, pilas1Usadas, pilas2Usadas;
    long long int aux;
    for (int k = 0; k < nPilas1; k++) {
        std::cin >> aux;
        pilas1.push(aux);
    }
    for (int k = 0; k < nPilas2; k++) {
        std::cin >> aux;
        pilas2.push(aux);
    }

    if (pilas1.empty() || pilas2.empty() || nDrones == 0) {
        std::cout << "0\n";
        return true;
    }

    int cont = 0;
    long long int horasAcumuladas = 0;
    while (!pilas1.empty() && !pilas2.empty() || !pilas1Usadas.empty() || !pilas2Usadas.empty()) {
        cont++;
        long long int pila1 = pilas1.top();
        pilas1.pop();

        long long int pila2 = pilas2.top();
        pilas2.pop();

        if (pila1 > pila2) {
            horasAcumuladas += pila2;
            pila1 = pila1 - pila2;
            pilas1Usadas.push(pila1);
        }
        else if (pila2 > pila1) {
            horasAcumuladas += pila1;
            pila2 = pila2 - pila1;
            pilas2Usadas.push(pila2);
        }
        else horasAcumuladas += pila1; //son iguales

        if (cont >= nDrones || pilas1.empty() || pilas2.empty()) {
            std::cout << horasAcumuladas << " ";
            horasAcumuladas = 0;
            cont = 0;
            while (!pilas1Usadas.empty()) {
                pilas1.push(pilas1Usadas.top());
                pilas1Usadas.pop();
            }
            while (!pilas2Usadas.empty()) {
                pilas2.push(pilas2Usadas.top());
                pilas2Usadas.pop();
            }
        }
    }
    if (cont > 0) std::cout << horasAcumuladas;
    std::cout << "\n";
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
