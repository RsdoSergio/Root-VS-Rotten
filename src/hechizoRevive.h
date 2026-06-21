#pragma once
#include "hechizo.h"
#include <vector>

class hechizoRevive : public HechizoBase
{
    Pieza* piezaElegida = nullptr; 

public:
    bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
    std::string getNombre() const { return "REVIVE"; }

    // Devuelve la lista de eliminadas del bando del mago (para mostrar el menu)
    std::vector<Pieza*>& getCandidatas(Tablero& tablero, Pieza* caster);

    bool elegirPieza(Tablero& tablero, Pieza* caster, int indice);

    bool tienePiezaElegida() const { return piezaElegida != nullptr; }
    void resetear() { piezaElegida = nullptr; }
};