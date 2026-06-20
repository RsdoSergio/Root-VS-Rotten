#include"golem.h"
#include"piezatierra.h"
#include<ETSIDI.h>
#include"gestorTexturas.h"


std::string Golem::getRutaSprite() const
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/bonk_choi.png"
        : "imagenes/sprites_zombies/zombie_yeti.png";
}

