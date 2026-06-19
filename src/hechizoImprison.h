#pragma once
#include "hechizo.h"

class hechizoImprison : public Hechizo
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "IMPRISON"; }
};

