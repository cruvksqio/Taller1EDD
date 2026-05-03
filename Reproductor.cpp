#include <iostream>
#include "Reproductor.hpp"

using namespace std;

void Reproductor::iniciar() {

    listaCanciones.leerArchivo("music_source.txt");

    cout << "=== CANCIONES CARGADAS ===\n";
    listaCanciones.mostrar();
}