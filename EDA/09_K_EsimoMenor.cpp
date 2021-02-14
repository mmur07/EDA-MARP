// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>

using namespace std;

class Error {
private:
    string message;

public:
    Error(string m) { message = m; }
    string getMessage() { return message; }
};



class SetOfInts3 {
    // Conjuntos de enteros representados como vectores ordenados sin repeticiones
private:
    static const int intSize = 5;

    int elems[intSize];
    int size;
    int maxSize;

    void binSearch(int x, bool& found, int& pos) const {
        // Pre: los size primeros elementos de elems están ordenados
        //      size >= 0

        pos = binSearchAux(x, 0, size - 1);
        found = (pos >= 0) && (pos < size) && (elems[pos] == x);

        // Post : devuelve el mayor índice i (0 <= i <= size-1) que cumple
        //        elems[i] <= x
        //        si x es menor que todos los elementos de elems, devuelve -1
        //        found es true si x esta en elems[0..size-1]
    }
    int binSearchAux(int x, int a, int b) const {
        // Pre: elems está ordenado entre 0 .. size-1
        //      ( 0 <= a <= size ) && ( -1 <= b <= size ) && ( a <= b+1 )
        //      todos los elementos a la izquierda de 'a' son <= x
        //      todos los elementos a la derecha de 'b' son > x

            int p, m;

            if (a == b + 1)
                p = a - 1;
            else if (a <= b) {
                m = (a + b) / 2;
                if (elems[m] <= x)
                    p = binSearchAux(x, m + 1, b);
                else
                    p = binSearchAux(x, a, m - 1);
            }
            return p;
            // Post: devuelve el mayor índice i (0 <= i <= size-1) que cumple
            //       elems[i] <= x
            //       si x es menor que todos los elementos de elems, devuelve -1
        }
    void shiftRightFrom(int i) {
        for (int j = size; j > i; j--)
            elems[j] = elems[j - 1];
    }
    void shiftLeftFrom(int i) {
        for (; i < size - 1; i++)
            elems[i] = elems[i + 1];
    }

public:
    SetOfInts3(int kElems);
    bool isEmpty() const { return (size == 0); }
    bool isFull() const {
        return size == maxSize;
    }
    void add(int x) {
        bool found;
        int pos;

        binSearch(x, found, pos);
        if (!found) {
            if (isFull())
                throw Error("Cannot add: The set is full");
            else {
                shiftRightFrom(pos + 1);
                elems[pos + 1] = x;
                size++;
            }
        }
    }
    bool contains(int x) const {
        bool found;
        int pos;

        binSearch(x, found, pos);
        return found;
    }
    void remove(int x) {
        bool found;
        int pos;

        binSearch(x, found, pos);
        if (found) {
            shiftLeftFrom(pos);
            size--;
        }
    }
    void join(const SetOfInts3& set) {
        throw Error("Join operation not supported");
    }
    void intersect(const SetOfInts3& set) {
        throw Error("Intersection operation not supported");
    }
    friend istream& operator>>(istream& sIn, SetOfInts3& set) {
        int n;
        int d;
        sIn >> n;
        set.size = 0;
        if (sIn.fail()) return sIn;
        for (int i = 0; i < n; i++) {
            sIn >> d;
            set.add(d);
        }
        return sIn;
    }
    friend ostream& operator<<(ostream& sOut, SetOfInts3& set) {
        sOut << "{";
        for (int i = 0; i < set.size - 1; i++)
            sOut << set.elems[i] << ",";
        if (set.size > 0) sOut << set.elems[set.size - 1];
        sOut << "}";
        return sOut;
    }
    int getMax() {
        int max = elems[0];
        for (int k = 0; k < size; k++) {
            if (elems[k] > max) max = elems[k];
        }
        return max;
    }
    int getMin() {
        int min = elems[0];
        for (int k = 0; k < size; k++) {
            if (elems[k] < min) min = elems[k];
        }
        return min;
    }
    void removeMin() {
        remove(getMin());
    }
    void removeMax() {
        remove(getMax());
    }
    void print() {
        for (int k = 0; k < size; k++) {
            std::cout << elems[k] << " ";
        }
        std::cout << "\n";
    }
};


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