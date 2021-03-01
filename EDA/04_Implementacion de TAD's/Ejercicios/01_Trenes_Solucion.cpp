// Miguel Mur
// VJ43


#include <fstream>
#include <string>

#ifndef SETOFINTS3_H_
#define SETOFINTS3_H_

#include <iomanip>
#include <vector>
#include <iostream>

#include <string>

using namespace std;

#ifndef ERROR_H_
#define ERROR_H_

class Error {
private:
	string message;

public:
	Error(string m) { message = m; }
	string getMessage() { return message; }
};

#endif /* ERROR_H_ */


class TiemposEntrada {
	// Conjuntos de enteros representados como vectores ordenados sin repeticiones
public:
	class Hora {
	private:
		int hora_;
		int minuto_;
		int segundo_;
	public:
		Hora() : hora_(0), minuto_(0), segundo_(0) {};
		Hora(int h, int m, int s) : hora_(h), minuto_(m), segundo_(s) {}

		void print() const {
			std::cout << std::setfill('0') << std::setw(2) << hora_ << ":" << std::setfill('0') << std::setw(2) << minuto_ << ":" << std::setfill('0') << std::setw(2) << segundo_ << "\n";
		}

		bool isIncorrect() {
			return (hora_ > 23 || minuto_ > 59 || segundo_ > 59);
		}

		bool operator< (const Hora& h) const {
			if (hora_ == h.hora_) {
				if (minuto_ == h.minuto_) {
					return segundo_ < h.segundo_;
				}
				else return minuto_ < h.minuto_;
			}
			else return hora_ < h.hora_;
		}

		bool operator<= (Hora h) const {
			if (hora_ == h.hora_) {
				if (minuto_ == h.minuto_) {
					if (segundo_ == h.segundo_) return true;
					else return segundo_ < h.segundo_;
				}
				else return minuto_ < h.minuto_;
			}
			else return hora_ < h.hora_;
		}

		bool operator>= (Hora h) const {
			if (hora_ == h.hora_) {
				if (minuto_ == h.minuto_) {
					if (segundo_ == h.segundo_) return true;
					else return segundo_ > h.segundo_;
				}
				else return minuto_ > h.minuto_;
			}
			else return hora_ > h.hora_;
		}

		bool operator== (const Hora& h) const {
			return (h.hora_ == hora_ && h.minuto_ == minuto_ && h.segundo_ == segundo_);
		}
	};

	TiemposEntrada(int size) { size_ = size; }

	bool isEmpty() const { return (size_ == 0); }

	int size() { return size_; }

	void add(Hora h) {
		if (x.isIncorrect()) throw Error("Hora inválida");
		else elems.push_back(x);
	}

	void findClosestHour(const Hora& x) const {
		if (elems.size() == 1) {
			if (elems[0] >= x) elems[0].print();
			else std::cout << "NO\n";
		}

		else findClosestHourAux(x, 0, elems.size() - 1);
	}

	void findClosestHourAux(const Hora& x, int a, int b) const {
		int m;

		if (a == elems.size() - 1) std::cout << "NO\n";

		else if (a <= b) {
			m = (a + b) / 2;
			if (elems[m] < x && elems[m + 1] >= x) elems[m + 1].print();
			else if (elems[m] < x)
				findClosestHourAux(x, m + 1, b);
			else
				findClosestHourAux(x, a, m - 1);
		}
		else elems[a].print();
	}

private:
	std::vector<Hora> elems;
	int size_;
};

#endif /* SETOFINTS3_H_ */

istream& operator>>(istream& sIn, TiemposEntrada& set)
{
    int h, m, s;
    char aux;
    for (int k = 0; k < set.size(); k++) {
        std::cin >> h >> aux >> m >> aux >> s;
        set.add(TiemposEntrada::Hora(h, m, s));
    }
    return sIn;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int nTrenes = 0, nConsultas = 0;

    std::cin >> nTrenes >> nConsultas;

    if (nTrenes == 0 && nConsultas == 0)
        return false;

    TiemposEntrada salidas = TiemposEntrada(nTrenes);
    std::cin >> salidas;

    for (int k = 0; k < nConsultas; k++) {
        int h, m, s;
        char aux;
        std::cin >> h >> aux >> m >> aux >> s;
        TiemposEntrada::Hora hora = TiemposEntrada::Hora(h, m, s);
        if (hora.isIncorrect()) std::cout << "ERROR\n";
        else salidas.findClosestHour(hora);
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