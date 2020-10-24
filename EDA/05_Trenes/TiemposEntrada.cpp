#include <iostream>
using namespace std;

#include "Error.h"
#include "TiemposEntrada.h"

// Constructors

TiemposEntrada::TiemposEntrada(int size) {
	size_ = size;
}

// Public methods

bool TiemposEntrada::isEmpty() const {
	return (size_ == 0);
}

void TiemposEntrada::add(Hora x) { //throws Error
	if (x.isIncorrect()) throw Error("Hora inválida");
	else elems.push_back(x);
}

void TiemposEntrada::findClosestHour(const Hora& x) const
{
	if (elems.size() == 1) {
		if (elems[0] >= x) elems[0].print();
		else std::cout << "NO\n";
	}

	else findClosestHourAux(x, 0, elems.size() - 1);
}

void TiemposEntrada::findClosestHourAux(const Hora& x, int a, int b) const
{
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