#include"peon.h"
#include "piezaTierra.h"
#include<ETSIDI.h>


std::string Peon :: getRutaSprite() const 
{
    return bando == Bando::planta
        ? "imagenes/sprites_plantas/seta_solar.png"
        : "imagenes/sprites_zombies/zombie_normal.png";
}

void Peon :: dibujaTablero(float x, float y) const  
{
    dibujarSprite(getRutaSprite(), x, y, 1.4f, getDireccion(), 6);
}

void Peon :: dibujaArena(float x, float y) const  
{
    dibujarSprite(getRutaSprite(), x, y, 2.0f, getDireccion(), 6);
}