#pragma once
#include "hechizo.h"

class hechizoRevive : public HechizoBase
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "REVIVE"; }
};

