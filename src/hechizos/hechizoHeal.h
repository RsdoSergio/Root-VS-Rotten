#pragma once
#include "hechizo.h"

class hechizoHeal : public HechizoBase
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "IMPRISON"; }
	std::string getMensajeSeleccion() const override { return "Selecciona la pieza enemiga a aprisionar"; }
	std::string getMensajeExito() const override { return "El mago ha aprisionado a un enemigo"; }
};