#ifndef SONGLIST_HPP
#define SONGLIST_HPP

#include "Nodo.hpp"
#include <string>

class SongList {
private:
    Nodo* inicio;
    Nodo* fin;

public:
    SongList();
    ~SongList();

    void insertarFinal(Cancion c);
    void mostrar();
    void leerArchivo(string nombreArchivo);
};

#endif