#pragma once
#include "piezaTierra.h"
#include "proyectil.h"
#include <vector>

class Unicornio : public PiezaTierra {
    double velocidadProyectil; // Tiene proyectil además de melee

    int proyectilesRafaga = 3;
    int proyectilesRestantes = 0;
    double tiempoEntreDisparos = 0.15;
    double timerEntreDisparos = 0.0;
    int dirX = 0;
    int dirY = 0;

    std::vector<Proyectil*> proyectilesPendientes;

public:
    Unicornio(Bando b, Pos pos)
        : PiezaTierra(
            18.0,  // PV medio-alto
            6.0,   // Daño medio
            7.5,   // Vel. movimiento muy alta
            0.5,   // Enfriamiento bajo
            4, //rad de mov
            b, pos),
        velocidadProyectil(9.0) {} // Proyectil medio

    double getVelocidadProyectil() const override { return velocidadProyectil; }
    std::string getRutaSprite() const override;
    


    std::string getNombre() const override {
        return bando == Bando::planta ? "Rabano Casillero" : "Zombidito Momia";
    }
    void usarAtaqueSecundario() override {};

    void iniciarRafaga(int dx, int dy) override;
    void actualizarEfectos(double dt) override;
    std::vector<Proyectil*> recogerProyectiles() override;
    bool tieneProyectilesPendientes() const override { return !proyectilesPendientes.empty(); }
    bool bloqueaMovimientoAlAtacar() const override { return false; }
    bool enRafaga() const { return proyectilesRestantes > 0; }
    bool tieneRafaga() const override { return true; }

    int getFrame(DirMovimiento dir, AccionPieza accion) const override
    {
        if (enRafaga()) return 5; // frame de ataque
        return Pieza::getFrame(dir, accion);
    }
};