// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <set>
#include <math.h>


// función que resuelve el problema
void resolver(std::set<int> s, int iniNum) {
    bool feliz = true;
    std::cout << iniNum << " ";
    s.insert(iniNum);
    while (iniNum != 1 && feliz) {
        int aux, result = 0;
        while (iniNum != 0) {
            aux = iniNum % 10;
            result += pow(aux, 2);
            iniNum /= 10;
        }
        iniNum = result;
        std::cout << result << " ";
        if (s.find(result) != s.end()) feliz = false;
        else s.insert(result);
    }
    std::cout << feliz << " " << "\n";
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num = 0;
    std::cin >> num;
    if (!std::cin)
        return false;
    std::set<int> s;

    resolver(s, num);

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