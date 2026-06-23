#pragma once
#include "hechizo.h"

class hechizoSummon : public HechizoBase
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "SUMMON"; }
	std::string getMensajeSeleccion() const override { return "Pendiente de implementar"; }
	std::string getMensajeExito() const override { return "Pendiente de implementar"; }

};

