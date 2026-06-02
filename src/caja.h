#pragma once
#include "pared.h"

#include"arena_constantes.h"

class Caja
{
    Pared izq{ {-SEMIANCHO + MARGEN, -SEMIALTO + MARGEN}, {-SEMIANCHO + MARGEN,  HUD_BASE - MARGEN} };
    Pared dcha{ { SEMIANCHO - MARGEN, -SEMIALTO + MARGEN}, { SEMIANCHO - MARGEN,  HUD_BASE - MARGEN} };
    Pared suelo{ {-SEMIANCHO + MARGEN, -SEMIALTO + MARGEN_INF}, { SEMIANCHO - MARGEN, -SEMIALTO + MARGEN_INF} };
    Pared techo{ {-SEMIANCHO + MARGEN,  HUD_BASE - MARGEN}, { SEMIANCHO - MARGEN,  HUD_BASE - MARGEN} };

public:
    void dibuja() const;
    double getXmin() const { return izq.getLimite1().getX(); }
    double getXMAX() const { return dcha.getLimite1().getX(); }
    double getYmin() const { return suelo.getLimite1().getY(); }
    double getYMAX() const { return techo.getLimite1().getY(); }
};
