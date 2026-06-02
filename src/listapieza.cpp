#include "listapieza.h"

// Destructor libera toda la memoria al cerrar el juego
listapieza::~listapieza() {
    Nodo* actual = cabeza;
    while (actual != nullptr) {
        Nodo* siguiente = actual->siguiente;
        delete actual->pieza;
        delete actual;
        actual = siguiente;
    }
}

// Añade una pieza al principio de la lista
void listapieza::agregar(Pieza* p) {
    Nodo* nuevo = new Nodo(p);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

// Recorre la lista y elimina los nodos cuya pieza no tiene vida
void listapieza::eliminarMuertas() {
    Nodo* actual = cabeza;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (!actual->pieza->estaViva()) {
            // Desconectar el nodo de la lista
            Nodo* aEliminar = actual;
            if (anterior == nullptr)
                cabeza = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;

            actual = actual->siguiente;
            delete aEliminar->pieza;
            delete aEliminar;
        }
        else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}