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
        velocidadProyectil(3.0) {} // Proyectil lento

    double getVelocidadProyectil() const override { return velocidadProyectil; }

    // Antes se dibujaba como cuadrado de color (morado claro LUZ / morado oscuro OSCURIDAD);
    // ahora usa sprite, ver Djinn::getRutaSprite() en genio.cpp
    std::string getRutaSprite() const override;
    

    std::string getNombre() const override {
        return bando == Bando::planta ? "Mazorcañon" : "Gondolero";
    }
    void usarAtaqueSecundario() override {};

    Proyectil* crearProyectil(int dirX, int dirY) override;
    
};