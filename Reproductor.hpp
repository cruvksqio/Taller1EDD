#ifndef REPRODUCTOR_HPP
#define REPRODUCTOR_HPP

#include "SongList.hpp"

class Reproductor {
private:
    SongList listaCanciones;

public:
    void iniciar();
    void play();
    void prev();
    void next();
    void toggleShuffle();
    void toggleRepeat();
    void seePlaylist();
    void seeSongList();
    void exit();
};

#endif