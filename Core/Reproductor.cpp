#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../classes/Cancion.hpp"
#include "../data_structures/SongList.hpp"

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

void Reproductor::cargarEstado(const std::string& archivoConfig) {
    std::ifstream archivo(archivoConfig);

    // Caso de borde: Si el archivo NO existe (Primera ejecución)
    if (!archivo.is_open()) {
        std::cout << "Archivo status.cfg no encontrado. Generando estado por defecto...\n";

        // Configuramos los valores por defecto que exige el enunciado
        this->estadoReproduccion = 0; // 0: Reproducción Detenida
        this->modoAleatorio = false;
        this->modoRepeticion = 0;     // 0: Desactivado

        // Generamos el archivo inmediatamente
        guardarEstado(archivoConfig);
        return;
    }

    // Si el archivo existe, leemos línea por línea
    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string parametro;
        std::string valor;

        // Leemos la primera palabra (PARÁMETRO) y el resto de la línea (VALOR)
        ss >> parametro;
        std::getline(ss >> std::ws, valor); // Extrae el resto ignorando espacios iniciales

        // Asignamos los valores a las variables de la clase Reproductor
        if (parametro == "MODO_ALEATORIO") {
            this->modoAleatorio = (valor == "1");
        }
        else if (parametro == "MODO_REPETICION") {
            this->modoRepeticion = std::stoi(valor);
        }
        else if (parametro == "ESTADO_REPRODUCCION") {
            this->estadoReproduccion = std::stoi(valor);
        }
        else if (parametro == "COLA_PENDIENTE") {
            // Aquí puedes hacer un split por comas (similar a como leímos music_source.txt)
            // para extraer los IDs, buscar esas canciones en tu 'registroTotal'
            // y agregarlas a tu 'listaReproduccion'.

            // Ejemplo rápido si usas un stringstream con comas:
            std::stringstream ssIds(valor);
            std::string idStr;
            while (std::getline(ssIds, idStr, ',')) {
                int id = std::stoi(idStr);
                // Lógica pseudo-código:
                // Cancion c = registroTotal.buscarPorId(id);
                // listaReproduccion.agregarAlFinal(c);
            }
        }
    }

    archivo.close();
};

void Reproductor::guardarEstado(const std::string& archivoConfig) {
    // Usamos std::ofstream en modo truncar (por defecto) para sobrescribir el archivo
    std::ofstream archivo(archivoConfig);

    if (!archivo.is_open()) {
        std::cerr << "Error crítico: No se pudo guardar el archivo " << archivoConfig << "\n";
        return;
    }

    // Escribimos respetando estrictamente el formato "PARÁMETRO VALOR"
    archivo << "MODO_ALEATORIO " << (this->modoAleatorio ? "1" : "0") << "\n";
    archivo << "MODO_REPETICION " << this->modoRepeticion << "\n";
    archivo << "ESTADO_REPRODUCCION " << this->estadoReproduccion << "\n";

    // Guardamos la cola pendiente separada por comas
    archivo << "COLA_PENDIENTE ";

    if (this->listaReproduccion.estaVacia()) {
        archivo << "VACIA";
    } else {
        // Aquí deberías recorrer tu listaReproduccion actual y extraer los IDs.
        // Como implementaste la lista doblemente enlazada manualmente,
        // puedes hacer un método en SongList que retorne los IDs en formato string.

        // Pseudo-código: archivo << listaReproduccion.obtenerIdsComoString();
    }
    archivo << "\n";

    archivo.close();
};