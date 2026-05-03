#include <iostream>
#include <fstream>
#include <sstream>
#include "SongList.hpp"

using namespace std;

SongList::SongList() {
    inicio = NULL;
    fin = NULL;
}

SongList::~SongList() {
    Nodo* aux = inicio;
    while (aux != NULL) {
        Nodo* temp = aux;
        aux = aux->siguiente;
        delete temp;
    }
}

void SongList::insertarFinal(Cancion c) {
    Nodo* nuevo = new Nodo;
    nuevo->song = c;
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;

    if (inicio == NULL) {
        inicio = fin = nuevo;
    } else {
        fin->siguiente = nuevo;
        nuevo->anterior = fin;
        fin = nuevo;
    }
}

void SongList::mostrar() {
    Nodo* aux = inicio;

    while (aux != NULL) {
        cout << aux->song.getId() << " - ";
        cout << aux->song.getNombre() << " - ";
        cout << aux->song.getArtista() << endl;

        aux = aux->siguiente;
    }
}

void SongList::leerArchivo(string nombreArchivo) {

    ifstream archivo(nombreArchivo);

    if (!archivo) {
        cout << "No se pudo abrir el archivo\n";
        return;
    }

    string linea;

    while (getline(archivo, linea)) {

        stringstream ss(linea);

        string idStr, nombre, artista, album, anioStr, duracionStr, ubicacion;

        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, artista, ',');
        getline(ss, album, ',');
        getline(ss, anioStr, ',');
        getline(ss, duracionStr, ',');
        getline(ss, ubicacion, ',');

        int id = stoi(idStr);
        int anio = stoi(anioStr);
        int duracion = stoi(duracionStr);

        Cancion c(id, nombre, artista, album, anio, duracion, ubicacion);

        insertarFinal(c);
    }

    archivo.close();
}