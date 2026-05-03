#ifndef NODO_HPP
#define NODO_HPP

#include "../Clases/Cancion.hpp"

struct Nodo {
    Cancion song;
    Nodo* siguiente;
    Nodo* anterior;
};

#endif