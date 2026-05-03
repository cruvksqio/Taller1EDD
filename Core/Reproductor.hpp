#ifndef REPRODUCTOR_HPP
#define REPRODUCTOR_HPP
#include <iostream>
#include <fstream>
#include <sstream>

#include "../Structure/SongList.hpp"
#include "../Clases/Cancion.hpp"

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

#endif