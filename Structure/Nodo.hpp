#ifndef NODO_HPP
#define NODO_HPP

#include "../Core/Cancion.hpp"

struct Nodo {
    Cancion song;
    Nodo* siguiente;
    Nodo* anterior;
};

#endif