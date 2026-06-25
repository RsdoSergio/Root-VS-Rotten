#pragma once
#include "piezaVuelo.h"
#include "proyectilacelerado.h"

class Djinn : public PiezaVuelo {
    double velocidadProyectil; // Proyectil lento pero muy potente (one shot)

    static constexpr double VEL_MIN = 4.0;
    static constexpr double VEL_MAX = 10.0;
    static constexpr double DURACION_PROYECTIL = 5.0;

public:
    Djinn(Bando b, Pos pos)
        : PiezaVuelo(
            11.0,  // PV medio
            20.0,  // Daño muy alto
            4.0,   // Vel. movimiento alta
            3.5,   // Enfriamiento muy alto
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

    Proyectil* crearProyectil(int dirX, int dirY) override;
    void usarAtaqueSecundario() override {};
};