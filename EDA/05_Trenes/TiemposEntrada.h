
#ifndef SETOFINTS3_H_
#define SETOFINTS3_H_

#include "Error.h"
#include <iomanip>
#include <vector>
#include <iostream>

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

			void print() const{
				std::cout << std::setfill('0') << std::setw(2) <<  hora_ << ":" << std::setfill('0') << std::setw(2) << minuto_ << ":" << std::setfill('0') << std::setw(2) << segundo_ << "\n";
			}

			bool isIncorrect() {
				return (hora_ > 23 || minuto_ > 59 || segundo_ > 59);
			}

			bool operator< (const Hora &h) const{
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

			bool operator== (const Hora &h) const {
				return (h.hora_ == hora_ && h.minuto_ == minuto_ && h.segundo_ == segundo_);
			}
	};

	TiemposEntrada(int size);
	bool isEmpty() const;
	int size() { return size_; }
	void add(Hora h); //throws Error
	void findClosestHour(const Hora& x) const;
	void findClosestHourAux(const Hora& x, int a, int b) const;

private:
	std::vector<Hora> elems;
	int size_;
};

#endif /* SETOFINTS3_H_ */
