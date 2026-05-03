#ifndef SONGLIST_HPP
#define SONGLIST_HPP

#include "Nodo.hpp"
#include <iostream>

template <typename T>
class SongList {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    Nodo<T>* actual; // Puntero crucial para saber qué está sonando
    int longitud;

public:
    // Constructor
    SongList() {
        cabeza = nullptr;
        cola = nullptr;
        actual = nullptr;
        longitud = 0;
    }

    // Destructor (Importante para evitar fugas de memoria)
    ~SongList() {
        vaciar();
    }

    // --- MÉTODOS DE INSERCIÓN ---

    // Agrega un elemento al final de la lista (Útil para A<num> y carga inicial)
    void agregarAlFinal(T valor) {
        Nodo<T>* nuevoNodo = new Nodo<T>(valor);

        if (cabeza == nullptr) { // Si la lista está vacía
            cabeza = nuevoNodo;
            cola = nuevoNodo;
            actual = nuevoNodo; // Si es la primera canción, la marcamos como actual
        } else {
            cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = cola;
            cola = nuevoNodo;
        }
        longitud++;
    }

    // --- MÉTODOS DE CONTROL DE REPRODUCCIÓN ---

    // Pista Siguiente (Opción E)
    bool avanzar() {
        if (actual != nullptr && actual->siguiente != nullptr) {
            actual = actual->siguiente;
            return true;
        }
        return false; // Retorna falso si no hay siguiente (fin de la lista)
    }

    // Pista Anterior (Opción Q)
    bool retroceder() {
        if (actual != nullptr && actual->anterior != nullptr) {
            actual = actual->anterior;
            return true;
        }
        return false; // Retorna falso si no hay anterior (inicio de la lista)
    }

    // Devuelve el dato del nodo actual para reproducirlo o mostrarlo
    T* obtenerActual() {
        if (actual != nullptr) {
            return &(actual->dato); // Devolvemos la dirección de memoria para poder leer o modificar la canción
        }
        return nullptr;
    }

    // --- MÉTODOS DE UTILIDAD ---

    bool estaVacia() const {
        return longitud == 0;
    }

    int obtenerLongitud() const {
        return longitud;
    }

    // Elimina todos los nodos de la lista
    void vaciar() {
        Nodo<T>* temp = cabeza;
        while (temp != nullptr) {
            Nodo<T>* siguiente = temp->siguiente;
            delete temp;
            temp = siguiente;
        }
        cabeza = nullptr;
        cola = nullptr;
        actual = nullptr;
        longitud = 0;
    }

    // Imprime la lista (Útil para depurar y para el menú de Ver Lista (A))
    void imprimirLista() const {
        if (estaVacia()) {
            std::cout << "Lista vacía\n";
            return;
        }
        Nodo<T>* temp = cabeza;
        int contador = 1;
        while (temp != nullptr) {
            std::cout << contador << ". ";
            // Asumimos que el tipo T (Cancion) tiene un método imprimirDatos()
            temp->dato.imprimirDatos();
            temp = temp->siguiente;
            contador++;
        }
    }

    // --- MÉTODO PARA SALTAR CANCIÓN (Opción S<num>) ---

    bool saltarA(int posicion) {
        // Validamos que la posición solicitada exista en la lista
        if (posicion < 1 || posicion > longitud) {
            return false;
        }

        Nodo<T>* temp = cabeza;
        // Recorremos la lista hasta llegar a la posición deseada
        for (int i = 1; i < posicion; ++i) {
            temp = temp->siguiente;
        }

        // Actualizamos el puntero 'actual' a la nueva canción
        actual = temp;
        return true;
    }

};



#endif