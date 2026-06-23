#pragma once
#include "hechizo.h"

class hechizoShiftTime : public HechizoBase
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "SHIFT_TIME"; }
	std::string getMensajeSeleccion() const override { return "Pendiente de implementar"; }
	std::string getMensajeExito() const override { return "Pendiente de implementar"; }

};

