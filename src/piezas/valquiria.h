#pragma once
#include "piezaVuelo.h"
#include "proyectil.h"
#include <vector>

class Valquiria : public PiezaVuelo {
    double velocidadProyectil; // Proyectil rápido, menos daño. También tiene ráfaga

    int    golpesPendientes = 0;
    double timerEntreGolpes = 0.0;
    int    dirX = 0, dirY = 0; // dirección al atacar

    std::vector<Proyectil*> proyectilesPendientes;

    static constexpr double OFFSET_FRENTE = 1.5;
    static constexpr double OFFSET_PERPENDICULAR = 1.2;
    static constexpr double DELAY_ENTRE_GOLPES = 0.15;

public:
    Valquiria(Bando b, Pos pos)
        : PiezaVuelo(
            10.0,  // PV medio
            2.0,   // Daño bajo por proyectil (compensa con ráfaga)
            9.0,   // Vel. movimiento muy alta
            0.45,   // Enfriamiento ráfaga muy bajo
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

    bool esMelee() const override { return true; };
    void iniciarRafaga(int dx, int dy) override;
    void actualizarEfectos(double dt) override;
    std::vector<Proyectil*> recogerProyectiles() override;
    bool tieneRafaga() const override { return true; }

    bool tieneProyectilesPendientes() const override { return !proyectilesPendientes.empty(); }

};