// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <math.h>

class Polinomio {
public:
    Polinomio() {};
    void add(int coef, int expon) {
        monomio m = monomio(coef, expon);
        if (vec.empty()) vec.push_back(m);
        else addAux(m, 0, vec.size() - 1);
    }
    long long int resolver(int val) {

        long long int result = 0;
        for (int k = 0; k < vec.size(); k++) {
            result += (vec[k].coeficiente * pow(val, vec[k].exponente));
        }
        return result;
    }

    struct monomio {
        int coeficiente;
        int exponente;

        monomio(int coef, int exp) : coeficiente(coef), exponente(exp) {};
    };
private:
    std::vector<monomio> vec;
    void addAux(monomio m, int ini, int fin) {
        if (ini >= fin || vec.size() == 1) {
            if (m.exponente > vec[ini].exponente) vec.emplace(vec.begin() + ini, m);
            else if (m.exponente < vec[ini].exponente) vec.emplace(vec.begin() + ini + 1, m);
            else vec[ini].coeficiente = vec[ini].coeficiente + m.coeficiente;
        }
        else {
            int mid = (ini + fin) / 2;

            if (vec[mid].exponente > m.exponente && vec[mid + 1].exponente < m.exponente) {
                vec.emplace(vec.begin() + mid + 1, m);
            }
            else if (vec[mid].exponente < m.exponente) addAux(m, ini, mid);
            else if (vec[mid].exponente > m.exponente) addAux(m, mid + 1, fin);
            else vec[mid].coeficiente = vec[mid].coeficiente + m.coeficiente;
        }
    }

};

// función que resuelve el problema
long long int resolver(Polinomio p, int valor) {

    return p.resolver(valor);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int elem1, elem2;

    std::cin >> elem1;
    if (!std::cin)
        return false;
    std::cin >> elem2;
    Polinomio p;
    while (elem1 != 0 || elem2 != 0) {
        p.add(elem1, elem2);
        std::cin >> elem1 >> elem2;
    }
    int nConsultas;

    std::cin >> nConsultas;

    for (int k = 0; k < nConsultas; k++) {
        int consulta;
        std::cin >> consulta;
        std::cout << resolver(p, consulta) << " ";
    }
    std::cout << "\n";
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