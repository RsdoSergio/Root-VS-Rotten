#pragma once
#include "piezaVuelo.h"

class Valquiria : public PiezaVuelo {
    double velocidadProyectil; // Proyectil rápido, menos daño. También tiene ráfaga

public:
    Valquiria(Bando b, Pos pos)
        : PiezaVuelo(
            10.0,  // PV medio
            2.0,   // Daño bajo por proyectil (compensa con ráfaga)
            6.5,   // Vel. movimiento muy alta
            0.2,   // Enfriamiento ráfaga muy bajo
            4,//rad de mov
            b, pos),
        velocidadProyectil(8.0) 
    {
        rutaSprite = bando == Bando::planta
            ? "imagenes/sprites_plantas/rotinabo.png"
            : "imagenes/sprites_zombies/zombie_globo.png";

        rutaSpriteAtaque = bando == Bando::planta
            ? "imagenes/sprites_plantas/rotinabo_ataque.png"
            : "imagenes/sprites_zombies/zombie_globo_ataque.png";

        numFramesAtaque = 4;
    }

    double getVelocidadProyectil() const override { return velocidadProyectil; }

  
   
   
    std::string getNombre() const override {
        return bando == Bando::planta ? "Rotinabo" : "Globador";
    }
    void usarAtaqueSecundario() override {};
};