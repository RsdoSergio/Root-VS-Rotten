#pragma once
#include "hechizo.h"

class hechizoRevive : public Hechizo
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "REVIVE"; }
};

