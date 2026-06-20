#include"peon.h"
#include "piezaTierra.h"
#include<ETSIDI.h>


std::string Peon :: getRutaSprite() const 
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/seta_solar.png"
        : "imagenes/sprites_zombies/zombie_normal.png";
}


