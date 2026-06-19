#pragma once
#include "hechizo.h"

class hechizoSummon : public Hechizo
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "SUMMON"; }
};

