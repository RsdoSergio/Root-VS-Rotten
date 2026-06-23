#pragma once
#include "piezaVuelo.h"

class Fenix : public PiezaVuelo {
    bool poderUsado = false; // Revive una vez con 15% PV, x1.5 vel y x2 daño durante 5s

    bool explosionActiva = false;
    double radioExplosionActual = 0.0;
    double radioExplosionMax = 5.0;
    double tiempoExplosion = 0.0;
    double duracionExplosion = 0.5;

    bool danoExplosionPendiente = false;    
public:
    Fenix(Bando b, Pos pos)
        : PiezaVuelo(
            14.0,  // PV medio
            8.0,   // Daño área
            6.0,   // Vel. movimiento alta
            1.0,   // Enfriamiento medio
            5, //rad de mov
            b, pos) 
    {
        rutaSpriteAtaque = bando == Bando::planta
            ? "imagenes/sprites_plantas/boca_de_dragon_ataque.png"
            : "imagenes/sprites_zombies/zombie_dragon_ataque.png";

        rutaSprite = bando == Bando::planta
            ? "imagenes/sprites_plantas/boca_de_dragon.png"
            : "imagenes/sprites_zombies/zombie_dragon.png";
    }

    bool puedeUsarPoder() const { return !poderUsado; }
    void usarPoder() { poderUsado = true; }

    // Antes se dibujaba como cuadrado de color (naranja LUZ / naranja oscuro OSCURIDAD);
    // ahora usa sprite, ver Fenix::getRutaSprite() en fenix.cpp
    std::string getRutaSprite() const override;
    

    std::string getNombre() const override {
        return bando == Bando::planta ? "Boca de Dragon" : "Zombidito Dragon";
    }
    void usarAtaqueSecundario() override {};

    bool esMelee() const override { return true; }

    void actualizarEfectos(double dt) override;

    double getRadioExplosionMax() const { return radioExplosionMax; }
    bool getDanoExplosionPendiente() const { return danoExplosionPendiente; }
    
    void resetDanoExplosion() { danoExplosionPendiente = false; }
    double consumirDanoExplosion() override;
    

    void activarExplosion() override;
    void dibujaArena(float x, float y) const override;
    void actualizarArena(double dt) override;
};
