#ifndef REPRODUCTOR_HPP
#define REPRODUCTOR_HPP

#include "../Structure/SongList.hpp"

class Reproductor {
private:
    SongList<Cancion> registroTotal; // Todas las canciones (cargadas de music_source.txt)
    SongList<Cancion> listaReproduccion; // La cola actual

    // Variables de estado
    bool modoAleatorio;
    int modoRepeticion; // 0: Desactivado, 1: Repetir una (R1), 2: Repetir todas (RA)
    int estadoReproduccion; // 0: Detenida, 1: Reproduciendo, 2: En Pausa

public:
    // ... tus constructores y otros métodos ...

    // Los dos nuevos métodos para la Fase 3
    void cargarEstado(const std::string& archivoConfig);
    void guardarEstado(const std::string& archivoConfig);
};

#endif