cmake_minimum_required(VERSION 3.20)
project(Taller1EDD)

set(CMAKE_CXX_STANDARD 17)

add_executable(Taller1EDD
        main.cpp
        Clases/Cancion.cpp
        Structure/SongList.cpp
        Core/Reproductor.cpp
)