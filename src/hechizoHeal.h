#pragma once
#include "hechizo.h"

class hechizoHeal : public HechizoBase
{
public:
    virtual ~hechizoHeal() override = default;
    bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
    std::string getNombre() const override { return "HEAL"; }
};