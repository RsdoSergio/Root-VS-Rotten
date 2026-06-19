#pragma once
#include "hechizo.h"

class hechizoExchange : public HechizoBase	
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "EXCHANGE"; }
};

