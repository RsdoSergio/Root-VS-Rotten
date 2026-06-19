#pragma once
#include "hechizo.h"

class hechizoExchange : public Hechizo
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "EXCHANGE"; }
};

