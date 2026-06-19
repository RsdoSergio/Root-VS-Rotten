#pragma once
#include "hechizo.h"

class hechizoHeal : public Hechizo
{
public:
    bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "HEAL"; }
};

