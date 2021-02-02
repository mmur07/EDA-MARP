// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

bool es_Solucion(const int &S, int &sumaActual) {
    return sumaActual == S;
}

bool es_Valido(int k, const int &S, const std::vector<int>& nums, std::vector<int>& solucionActual, int &sumaActual, std::vector<std::vector<bool>>& matUsados, std::vector<bool>& vecUsados) {
    //if (k > nums.size()) return false;

    if (sumaActual + nums[solucionActual[k]] > S) return false;

    if (vecUsados[solucionActual[k]] == true) return false;

    if (matUsados[nums[solucionActual[k]]][sumaActual]) return false;
    if (matUsados[sumaActual][nums[solucionActual[k]]]) return false; //Si da la primera daria la segunda. Lo dejo por seguridad.

    return true;
}

void resolver_aux(int k, const int& S, const std::vector<int>& nums, std::vector<int>& solucionActual, int &sumaActual, std::vector<std::vector<bool>>& matUsados, std::vector<bool> &vecUsados, int& numSoluciones) {
    if (es_Solucion(S, sumaActual)) {
        numSoluciones++;
    }

    else if (k < nums.size()){
        for (int l = 0; l < nums.size(); l++) {
            solucionActual[k] = l;
            if (es_Valido(k, S, nums, solucionActual, sumaActual, matUsados, vecUsados)) {
                vecUsados[l] = true;
                matUsados[sumaActual][nums[l]] = true;
                matUsados[nums[l]][sumaActual] = true;
                sumaActual += nums[l];
                resolver_aux(k + 1, S, nums, solucionActual, sumaActual, matUsados, vecUsados, numSoluciones);
                sumaActual -= nums[l];
                //matUsados[sumaActual][nums[l]] = false;
                //matUsados[nums[l]][sumaActual] = false;
                vecUsados[l] = false;
            }
            solucionActual[k] = -1;
        }
    }
}

// función que resuelve el problema
int resolver(const int &S, const std::vector<int> &nums) {
    std::vector<int> solucionActual = std::vector<int>(nums.size(), false);
    int sumaActual = 0;
    int numSoluciones = 0;
    std::vector<std::vector<bool>> matUsados(S + 1, std::vector<bool>(S + 1, false));
    std::vector<bool> vecUsados(nums.size(), false);

    resolver_aux(0, S, nums, solucionActual, sumaActual, matUsados, vecUsados, numSoluciones);

    return numSoluciones;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int S, n, aux;
    std::cin >> n;
    if (!std::cin)
        return false;
    std::cin >> S;

    std::vector<int> nums;
    for (int k = 0; k < n; k++) {
        std::cin >> aux;
        nums.push_back(aux);
    }
    std::cout << resolver(S, nums) << "\n";

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