#include <iostream>
#include <fstream>
#include <sstream>
#include "../Clases/Cancion.hpp"
#include "../Structure/SongList.hpp"

// Función para cargar las canciones desde el archivo de texto
void cargarCanciones(const std::string& nombreArchivo, SongList<Cancion>& listaRegistro) {
    std::ifstream archivo(nombreArchivo);
    std::string linea;

    if (!archivo.is_open()) {
        std::cerr << "Advertencia: No se pudo abrir el archivo " << nombreArchivo << ".\n";
        // El enunciado dice que si no está el archivo, no se pueden cargar canciones[cite: 1].
        return;
    }

    // Leemos línea por línea
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string dato;

        // Variables temporales para construir la Cancion
        int id, anio, duracion;
        std::string nombre, artista, album, ruta;

        try {
            // Extraemos separando por comas
            std::getline(ss, dato, ','); id = std::stoi(dato);

            std::getline(ss, nombre, ',');
            // Limpiamos el espacio en blanco inicial si lo hay
            if (!nombre.empty() && nombre[0] == ' ') nombre.erase(0, 1);

            std::getline(ss, artista, ',');
            if (!artista.empty() && artista[0] == ' ') artista.erase(0, 1);

            std::getline(ss, album, ',');
            if (!album.empty() && album[0] == ' ') album.erase(0, 1);

            std::getline(ss, dato, ','); anio = std::stoi(dato);
            std::getline(ss, dato, ','); duracion = std::stoi(dato);

            std::getline(ss, ruta, ',');
            if (!ruta.empty() && ruta[0] == ' ') ruta.erase(0, 1);

            // Instanciamos la canción y la agregamos a nuestra lista enlazada
            Cancion nuevaCancion(id, nombre, artista, album, anio, duracion, ruta);
            listaRegistro.agregarAlFinal(nuevaCancion);

        } catch (const std::exception& e) {
            std::cerr << "Error al procesar una línea del archivo: " << e.what() << '\n';
            // Continuamos con la siguiente línea en caso de error de formato
            continue;
        }
    }

    archivo.close();
};