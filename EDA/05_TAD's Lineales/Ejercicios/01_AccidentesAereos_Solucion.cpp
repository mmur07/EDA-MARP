// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>

struct fechaAccidente {
    int dia_;
    int mes_;
    int anyo_;
    int victimas_;
    fechaAccidente(int d, int m, int a, int v) { dia_ = d; mes_ = m; anyo_ = a; victimas_ = v; }
    bool operator> (const fechaAccidente& b) const{
        return victimas_ > b.victimas_;
    }

    void print() {
        std::cout << std::setfill('0') << std::setw(2) << dia_ << "/" << std::setfill('0') << std::setw(2) << mes_ << "/" << std::setfill('0') << std::setw(4) << anyo_ << "\n";
    }
};

// función que resuelve el problema
void resolver(std::stack<fechaAccidente> &stack, fechaAccidente fecha) {
    bool found = false;
    while (!found && !stack.empty()) {
        if (stack.top() > fecha) {
            found = true;
        }
        else stack.pop();
    }

    if (!found) {
        std::cout << "NO HAY\n";
        stack.push(fecha);
    }
    else {
        stack.top().print();
        stack.push(fecha);
    }
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nAccidentes = 0;
    std::cin >> nAccidentes;

    if (!std::cin) {
        return false;
    }

    std::stack<fechaAccidente> s;

    for (int k = 0; k < nAccidentes; k++) {
        int dia, mes, anyo, victimas;
        char aux;

        std::cin >> dia >> aux >> mes >> aux >> anyo >> victimas;

        fechaAccidente nFecha = fechaAccidente(dia, mes, anyo, victimas);

        resolver(s, nFecha);
        // escribir sol
    }
    std::cout << "---\n";
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