#pragma once
#include "hechizo.h"

class hechizoShiftTime : public HechizoBase
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "SHIFT_TIME"; }
	std::string getMensajeSeleccion() const override { return ""; }
	std::string getMensajeExito() const override { return "El mago ha alterado el ciclo del combate"; }

};

