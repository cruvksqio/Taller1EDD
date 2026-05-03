cmake_minimum_required(VERSION 4.2)
project(Taller1EDD)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller1EDD main.cpp
        Cancion.hpp
        cmake-build-debug/Cancion.cpp
        Cancion.cpp
        Cancion.cpp
        Nodo.hpp
        SongList.cpp
        SongList.hpp
        Reproductor.hpp
        Reproductor.cpp)
