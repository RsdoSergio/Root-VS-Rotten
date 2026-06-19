#pragma once
#include "hechizo.h"

class hechizoTeleport : public Hechizo
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "TELEPORT"; }
};

