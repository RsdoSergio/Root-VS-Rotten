#pragma once
#include "piezaVuelo.h"

class Djinn : public PiezaVuelo {
    double velocidadProyectil; // Proyectil lento pero muy potente (one shot)

public:
    Djinn(Bando b, Pos pos)
        : PiezaVuelo(
            11.0,  // PV medio
            15.0,  // Daño muy alto
            5.5,   // Vel. movimiento alta
            2.5,   // Enfriamiento muy alto
            3, //rad de mov
            b, pos),
        velocidadProyectil(3.0) 
    {
        rutaSprite = bando == Bando::planta
            ? "imagenes/sprites_plantas/mazorcanon.png"
            : "imagenes/sprites_zombies/zombie_yeti.png";

        rutaSpriteAtaque = bando == Bando::planta
            ? "imagenes/sprites_plantas/mazorcanon_ataque.png"
            : "imagenes/sprites_zombies/zombie_yeti_ataque.png";

        numFramesAtaque = 4;
    
    } // Proyectil lento

    double getVelocidadProyectil() const override { return velocidadProyectil; }

   
    

    std::string getNombre() const override {
        return bando == Bando::planta ? "Mazorcañon" : "Gondolero";
    }
    void usarAtaqueSecundario() override {};
};