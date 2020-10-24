// Jorge Moreno Martínez
// Miguel Mur Cortés
// Adrián Álvarez Bernabé
// Adrián de Lucas Gómez

// Comentario general sobre la solución,
// explicando cómo se resuelve el problema

#include <iostream>
#include <stdexcept>
#include <vector>
#include <queue>

class ColaMedianas {
protected:
    std::priority_queue<long int, std::vector<long int>, std::less<long int>> medianAndLess;
    std::priority_queue<long int, std::vector<long int>, std::greater<long int>> moreThanMedian;

    void reequilibra() {


        if (medianAndLess.size() > moreThanMedian.size() + 1)
        {
            moreThanMedian.push(medianAndLess.top());
            medianAndLess.pop();
        }
        else if (medianAndLess.size() < moreThanMedian.size())
        {
            medianAndLess.push(moreThanMedian.top());
            moreThanMedian.pop();
        }
    }
public:
    void insertar(int x)
    {
        if (vacia()) {
            medianAndLess.push(x);
        }
        else
        {
            if (x > mediana())
            {
                moreThanMedian.push(x);
            }
            else if (x < mediana())
            {
                medianAndLess.push(x);		//Al vector de menores
            }
            //else es igual que la mediana pero no se contempla

            reequilibra();
        }

    }
    bool vacia() const { return medianAndLess.empty() && moreThanMedian.empty(); };
    int mediana() const { return medianAndLess.top(); };
    void quitarMediana() { //O(logN)
        medianAndLess.pop();		//Sacamos la mediana
        reequilibra();
    }
};


#include <iostream>
#include <fstream>

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    long int numCasos;
    std::cin >> numCasos;
    if (!std::cin)  // fin de la entrada
        return false;
    ColaMedianas cola;


    for (int i = 0; i < numCasos; i++) {
        int caso;
        std::cin >> caso;

        if (caso != 0)
            cola.insertar(caso);		//Si no ha llamado metemos a gente a la cola

        else {
            if (cola.vacia()) std::cout << "ECSA ";		//Si no hay gente esperando pues el carnicero se aburre
            else {
                std::cout << cola.mediana() << " ";
                cola.quitarMediana();
            } 	//Si hay gente cogemos la que corresponde al mediano

        }
    }
    std::cout << "\n";

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