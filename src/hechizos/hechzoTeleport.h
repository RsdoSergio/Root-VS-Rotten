#pragma once
#include "hechizo.h"

class hechizoTeleport : public HechizoBase
{
public:
	bool ejecutar(Tablero& tablero, Pieza* caster, Pos objetivo) override;
	std::string getNombre() const { return "TELEPORT"; }
	std::string getMensajeSeleccion() const override { return "Pendiente de implementar"; }
	std::string getMensajeExito() const override { return "Pendiente de implementar"; }

};

