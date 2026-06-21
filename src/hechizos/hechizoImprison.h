#pragma once
#include "hechizo.h"

class hechizoImprison : public HechizoBase
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "IMPRISON"; }
	std::string getMensajeSeleccion() const override { return "Pendiente de implementar"; }
	std::string getMensajeExito() const override { return "Pendiente de implementar"; }

};

