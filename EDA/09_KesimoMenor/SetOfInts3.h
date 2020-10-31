
#ifndef SETOFINTS3_H_
#define SETOFINTS3_H_

#include "Error.h"

class SetOfInts3 {
	// Conjuntos de enteros representados como vectores ordenados sin repeticiones
	private:
		static const int intSize = 5;

		int elems[intSize];
		int size;
		int maxSize;

		void binSearch(int x,bool& found,int& pos) const;
		int binSearchAux(int x, int a, int b) const;
		void shiftRightFrom(int i);
		void shiftLeftFrom(int i);

	public:
		SetOfInts3(int kElems);
		bool isEmpty() const;
		bool isFull() const;
		void add(int x); //throws Error
		bool contains(int x) const;
		void remove(int x);
		void join(const SetOfInts3& set);
		void intersect(const SetOfInts3& set);
		friend istream& operator>>(istream& sIn,SetOfInts3& set);
		friend ostream& operator<<(ostream& sOut,SetOfInts3& set);
		int getMax();
		int getMin();
		void removeMin();
		void removeMax();
		void print();
};

#endif /* SETOFINTS3_H_ */
