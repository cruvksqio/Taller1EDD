#ifndef CANCION_HPP
#define CANCION_HPP

#include <string>
using namespace std;

class Cancion {
private:
    int id;
    string nombre;
    string artista;
    string album;
    int anio;
    int duracion;
    string ubicacion;

public:
    Cancion();
    Cancion(int id, string nombre, string artista, string album, int anio, int duracion, string ubicacion);

    int getId();
    string getNombre();
    string getArtista();
    string getAlbum();
    int getAnio();
    int getDuracion();
    string getUbicacion();
};

#endif