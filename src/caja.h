#pragma once
#include "pared.h"
#include "arena.h"

class Caja
{
    Pared izq{ {-SEMIANCHO + MARGEN, -SEMIALTO + MARGEN}, {-SEMIANCHO + MARGEN,  HUD_BASE - MARGEN} };
    Pared dcha{ { SEMIANCHO - MARGEN, -SEMIALTO + MARGEN}, { SEMIANCHO - MARGEN,  HUD_BASE - MARGEN} };
    Pared suelo{ {-SEMIANCHO + MARGEN, -SEMIALTO + MARGEN_INF}, { SEMIANCHO - MARGEN, -SEMIALTO + MARGEN_INF} };
    Pared techo{ {-SEMIANCHO + MARGEN,  HUD_BASE - MARGEN}, { SEMIANCHO - MARGEN,  HUD_BASE - MARGEN} };

public:
    void dibuja() const;
};