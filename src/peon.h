#pragma once
#include "piezaTierra.h"
#include<ETSIDI.h>
#include"gestorTexturas.h"

// Pieza básica: rápida pero débil. Bando LUZ = Planta, Bando OSCURIDAD = Zombi
class Peon : public PiezaTierra {
public:
    Peon(Bando b, Pos pos)
        : PiezaTierra(
            12.0,  // vida baja
            4.0,   // fuerza baja
            7.0,   // velocidad alta
            0.8,   // recarga rápida
            1, //rad de mov
            b, pos)
    {
        radioGolpe = 2.5;
        tiempoAnimAtaque = 0.3;
    };

    std::string getRutaSprite() const override;
    void dibujaTablero(float x, float y) const override;
    void dibujaArena(float x, float y) const override;

    std::string getNombre() const override 
    {
        return bando == Bando::planta ? "Seta Solar" : "Zombi";
    }
    void usarAtaqueSecundario() override {};
    
    bool puedeDiagonal() const override { return true; };

    bool esMelee()const override { return true; }

    
};