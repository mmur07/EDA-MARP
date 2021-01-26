// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>

/*
  Definición de algunas excepciones de las distintas
  implementaciones de los TADs.

  Estructura de Datos y Algoritmos
  Facultad de Informática
  Universidad Complutense de Madrid

 (c) Marco Antonio Gómez Martín, 2012
*/
#ifndef __EXCEPCIONES_H
#define __EXCEPCIONES_H

#include <string>
#include <iosfwd>
/**
 Clase de la que heredan todas las excepciones, y
 que proporciona el atributo que almacena el
 mensaje de error.
 */
class ExcepcionTAD {
public:
	ExcepcionTAD() {}
	ExcepcionTAD(const std::string& msg) : _msg(msg) {}

	const std::string msg() const { return _msg; }

	friend std::ostream& operator<<(std::ostream& out, const ExcepcionTAD& e);

protected:
	std::string _msg;
};

inline std::ostream& operator<<(std::ostream& out, const ExcepcionTAD& e) {
	out << e._msg;
	return out;
}


// Macro para declarar las clases de tipo excepción
// que heredan de ExcepcionConMensaje, para ahorrar
// escribir muchas veces lo mismo...
#define DECLARA_EXCEPCION(Excepcion) \
class Excepcion : public ExcepcionTAD { \
public: \
Excepcion() {}; \
Excepcion(const std::string &msg) : ExcepcionTAD(msg) {} \
};

/**
 Excepción generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(EmptyStackException);

/**
 Excepción generada por algunas operaciones de las pilas.
 */
DECLARA_EXCEPCION(FullStackException);

/**
 Excepción generada por algunas de las operaciones de las colas.
 */
DECLARA_EXCEPCION(EmptyQueueException);

/**
 Excepción generada por algunas operaciones de las colas dobles.
 */
DECLARA_EXCEPCION(EmptyDequeException);

/**
 Excepción generada por algunas operaciones de las listas.
 */
DECLARA_EXCEPCION(EmptyListException);

/**
 Excepción generada por accesos incorrectos a las listas
 (tanto a un número de elemento incorrecto como por
 mal manejo de los iteradores).
 */
DECLARA_EXCEPCION(InvalidAccessException);

/**
 Excepción generada por algunas operaciones de los
 árboles binarios.
 */
DECLARA_EXCEPCION(EArbolVacio);

/**
 Excepción generada por algunas operaciones de los
 diccionarios y árboles de búsqueda.
 */
DECLARA_EXCEPCION(EClaveErronea);

#endif // __EXCEPCIONES_H


/**
  @file Cola.h

  Implementaci�n del TAD Cola utilizando una
  lista enlazada de nodos.

  Estructura de Datos y Algoritmos
  Facultad de Inform�tica
  Universidad Complutense de Madrid

 (c) Marco Antonio G�mez Mart�n, 2012
*/
#ifndef __LINKED_LIST_QUEUE_H
#define __LINKED_LIST_QUEUE_H

#include <iostream>

/**
 Implementaci�n del TAD Cola utilizando una lista enlazada.

 Las operaciones son:

 - EmptyQueue: -> Queue. Generadora implementada en el
   constructor sin par�metros.
 - push_back: Queue, Elem -> Queue. Generadora
 - pop_front: Queue - -> Queue. Modificadora parcial.
 - front: Queue - -> Elem. Observadora parcial.
 - empty: Queue -> Bool. Observadora.
 - size: Queue -> Entero. Observadora.

 @author Marco Antonio G�mez Mart�n
 */
template <class T>
class Queue {
public:

	/** Constructor; operacion EmptyQueue */
	Queue() : _prim(NULL), _ult(NULL), _numElems(0) {
	}

	/** Destructor; elimina la lista enlazada. */
	~Queue() {
		libera();
		_prim = _ult = NULL;
	}

	/**
	 A�ade un elemento en la parte trasera de la cola.
	 Operaci�n generadora.

	 @param elem Elemento a a�adir.
	*/
	void push_back(const T& elem) {
		Nodo* nuevo = new Nodo(elem, NULL);

		if (_ult != NULL)
			_ult->_sig = nuevo;
		_ult = nuevo;
		// Si la cola estaba vac�a, el primer elemento
		// es el que acabamos de a�adir
		if (_prim == NULL)
			_prim = nuevo;
		_numElems++;
	}

	/**
	 Elimina el primer elemento de la cola.
	 Operaci�n modificadora parcial, que falla si
	 la cola est� vac�a.

	 pop_front(Push_back(elem, EmptyQueue)) = EmptyQueue
	 pop_front(Push_back(elem, xs)) = push_back(elem, pop_front(xs)) si !empty(xs)
	 error: pop_front(EmptyQueue)
	*/
	void pop_front() {
		if (empty())
			throw EmptyQueueException("Cannot pop: Queue is empty");
		Nodo* aBorrar = _prim;
		_prim = _prim->_sig;
		delete aBorrar;
		--_numElems;
		// Si la cola se qued� vac�a, no hay
		// �ltimo
		if (_prim == NULL)
			_ult = NULL;
	}

	/**
	 Devuelve el primer elemento de la cola. Operaci�n
	 observadora parcial, que falla si la cola est� vac�a.

	 front(Push_back(elem, EmptyQueue)) = elem
	 front(Push_back(elem, xs)) = primero(xs) si !empty(xs)
	 error: front(EmptyQueue)

	 @return El primer elemento de la cola.
	 */
	const T& front() const {
		if (empty())
			throw EmptyQueueException("Cannot get front: Queue is empty");
		return _prim->_elem;
	}

	/**
	 Devuelve true si la cola no tiene ning�n elemento.

	 empty(EmptyQueue) = true
	 empty(Push_back(elem, p)) = false

	 @return true si la cola no tiene ning�n elemento.
	 */
	bool empty() const {
		return _prim == NULL;
	}

	/**
	 Devuelve el n�mero de elementos que hay en la
	 cola.
	 size(EmptyQueue) = 0
	 size(Push_back(elem, p)) = 1 + size(p)

	 @return N�mero de elementos.
	 */
	int size() const {
		return _numElems;
	}

	// //
	// M�TODOS DE "FONTANER�A" DE C++ QUE HACEN VERS�TIL
	// A LA CLASE
	// //

	/** Constructor copia */
	Queue(const Queue<T>& other) : _prim(NULL), _ult(NULL) {
		copia(other);
	}

	/** Operador de asignaci�n */
	Queue<T>& operator=(const Queue<T>& other) {
		if (this != &other) {
			libera();
			copia(other);
		}
		return *this;
	}

	/** Operador de comparaci�n. */
	bool operator==(const Queue<T>& rhs) const {
		if (_numElems != rhs._numElems)
			return false;
		bool iguales = true;
		Nodo* p1 = _prim;
		Nodo* p2 = rhs._prim;
		while ((p1 != NULL) && (p2 != NULL) && iguales) {
			if (p1->_elem != p2->_elem)
				iguales = false;
			else {
				p1 = p1->_sig;
				p2 = p2->_sig;
			}
		}
		return iguales;
	}

	bool operator!=(const Queue<T>& rhs) const {
		return !(*this == rhs);
	}

	/** Escribe la cola en el flujo. Se usa desde operator<< */
	void write(std::ostream& sOut) {
		Nodo* aux = _prim;
		//sOut << "{";
		while (aux != NULL) {
			sOut << aux->_elem;
			aux = aux->_sig;
			if (aux != NULL) sOut << " ";
		}
		sOut << "\n";
	}

protected:

	void libera() {
		libera(_prim);
	}

	void copia(const Queue& other) {

		if (other.empty()) {
			_prim = _ult = NULL;
			_numElems = 0;
		}
		else {
			Nodo* act = other._prim;
			Nodo* ant;
			_prim = new Nodo(act->_elem);
			ant = _prim;
			while (act->_sig != NULL) {
				act = act->_sig;
				ant->_sig = new Nodo(act->_elem);
				ant = ant->_sig;
			}
			_ult = ant;
			_numElems = other._numElems;
		}
	}

private:

	/**
	 Clase nodo que almacena internamente el elemento (de tipo T),
	 y un puntero al nodo siguiente, que podr�a ser NULL si
	 el nodo es el �ltimo de la lista enlazada.
	 */
	class Nodo {
	public:
		Nodo() : _sig(NULL) {}
		Nodo(const T& elem) : _elem(elem), _sig(NULL) {}
		Nodo(const T& elem, Nodo* sig) :
			_elem(elem), _sig(sig) {}

		T _elem;
		Nodo* _sig;
	};

	/**
	 Elimina todos los nodos de la lista enlazada cuyo
	 primer nodo se pasa como par�metro.
	 Se admite que el nodo sea NULL (no habr� nada que
	 liberar).
	 */
	static void libera(Nodo* prim) {
		while (prim != NULL) {
			Nodo* aux = prim;
			prim = prim->_sig;
			delete aux;
		}
	}

	/** Puntero al primer elemento. */
	Nodo* _prim;

	/** Puntero al �ltimo elemento. */
	Nodo* _ult;

	/** N�mero de elementos */
	int _numElems;
};

template<class T>
std::ostream& operator<<(std::ostream& sOut, Queue<T>& q) {
	q.write(sOut);
	return sOut;
}

#endif // __LINKED_LIST_QUEUE_H

void inserta_indice(Queue<int>& queue, int indice) {
	int max_val = -1;
	int size = queue.size();
	for (int k = 0; k < size; k++) {
		int front = queue.front();
		queue.pop_front();
		if (k != indice) queue.push_back(front);
		else max_val = front;
	}

	queue.push_back(max_val);
}

int encuentra_min_indice(Queue<int> &queue, int limite) {

	int max_indice = -1;
	int max_valor = -1;

	for (int k = 0; k < queue.size(); k++) {
		int front = queue.front();
		queue.pop_front();

		if (std::abs(front) > max_valor && k < limite) {
			max_valor = std::abs(front);
			max_indice = k;
		}

		queue.push_back(front);
	}

	return max_indice;
}

// función que resuelve el problema
void resolver(Queue<int> &queue) {
	for (int k = 0; k < queue.size(); k++) {
		int indiceMin = encuentra_min_indice(queue, queue.size() - k);

		inserta_indice(queue, indiceMin);
	}
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	// leer los datos de la entrada
	int nNodos = 0;
	std::cin >> nNodos;
	if (nNodos == 0)
		return false;

	Queue<int> cola;
	int aux;
	for (int k = 0; k < nNodos; k++) {
		std::cin >> aux;
		cola.push_back(aux);
	}
	//std::cout << "Original: \n";
	//cola.write(std::cout);

	resolver(cola);

	//std::cout << "Reordenada: \n";
	cola.write(std::cout);
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
