#pragma once
#include "hechizo.h"

class hechizoTransform : public HechizoBase
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "TRANSFORM"; }
	std::string getMensajeSeleccion() const override { return ""; }
	std::string getMensajeExito() const override { return "El mago desborda de poder"; }

};

