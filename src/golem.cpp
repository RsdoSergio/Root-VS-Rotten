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

void Golem::dibujaTablero(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 1.4f, getDireccion(), 6);
}

void Golem::dibujaArena(float x, float y) const
{
    dibujarSprite(getRutaSprite(), x, y, 2.5f, getDireccion(), 6);
}